#include "TestGraphics.h"

#include "MainWindow.h"
#include "DXErr.h"
#include <assert.h>
#include <string>
#include <array>

namespace FramebufferShaders
{
	#include "FramebufferPS.shh"
	#include "FramebufferVS.shh"
}

#pragma comment( lib,"d3d11.lib" )

#define GFX_EXCEPTION( hr,note ) TestGraphics::Exception( hr,note,_CRT_WIDE(__FILE__),__LINE__ )

using Microsoft::WRL::ComPtr;

TestGraphics::TestGraphics(std::shared_ptr<SystemMessageDispatcher> dispatcher)
	: IGraphics(dispatcher)
{
}

void TestGraphics::Initalise(HWNDKey& key)
{
	assert(key.hWnd != nullptr);

	// Create device and swap chain
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = 1;
	sd.BufferDesc.Width = SCREEN_WIDTH;
	sd.BufferDesc.Height = SCREEN_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 1;
	sd.BufferDesc.RefreshRate.Denominator = 60;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = key.hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	HRESULT				hr;
	UINT				createFlags = 0u;
#ifdef USE_D3D_DEBUG_LAYER
#ifdef _DEBUG
	createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
#endif

	// Create device buffers
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&_swapChain,
		&_device,
		nullptr,
		&_immediateContext)))
	{
		throw GFX_EXCEPTION(hr, L"Creating device and swap chain");
	}

	// Get handle to backbuffer
	ComPtr<ID3D11Resource> pBackBuffer;
	if (FAILED(hr = _swapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		(LPVOID*)&pBackBuffer)))
	{
		throw GFX_EXCEPTION(hr, L"Getting back buffer");
	}

	// Create a view on backbuffer that we can render to
	if (FAILED(hr = _device->CreateRenderTargetView(
		pBackBuffer.Get(),
		nullptr,
		&_renderTargetView)))
	{
		throw GFX_EXCEPTION(hr, L"Creating render target view on backbuffer");
	}

	// set backbuffer as the render target using created view
	_immediateContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);

	// set viewport dimensions
	D3D11_VIEWPORT vp;
	vp.Width = float(SCREEN_WIDTH);
	vp.Height = float(SCREEN_HEIGHT);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	_immediateContext->RSSetViewports(1, &vp);

	// Create texture for cpu render target
	D3D11_TEXTURE2D_DESC sysTexDesc;
	sysTexDesc.Width = SCREEN_WIDTH;
	sysTexDesc.Height = SCREEN_HEIGHT;
	sysTexDesc.MipLevels = 1;
	sysTexDesc.ArraySize = 1;
	sysTexDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sysTexDesc.SampleDesc.Count = 1;
	sysTexDesc.SampleDesc.Quality = 0;
	sysTexDesc.Usage = D3D11_USAGE_DYNAMIC;
	sysTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	sysTexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	sysTexDesc.MiscFlags = 0;

	// create the texture
	if (FAILED(hr = _device->CreateTexture2D(&sysTexDesc, nullptr, &_sysBufferTexture)))
	{
		throw GFX_EXCEPTION(hr, L"Creating sysbuffer texture");
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = sysTexDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	// create the resource view on the texture
	if (FAILED(hr = _device->CreateShaderResourceView(_sysBufferTexture.Get(),
		&srvDesc, &_sysBufferTextureView)))
	{
		throw GFX_EXCEPTION(hr, L"Creating view on sysBuffer texture");
	}

	// Create pixel shader for framebuffer
	if (FAILED(hr = _device->CreatePixelShader(
		FramebufferShaders::FramebufferPSBytecode,
		sizeof(FramebufferShaders::FramebufferPSBytecode),
		nullptr,
		&_pixelShader)))
	{
		throw GFX_EXCEPTION(hr, L"Creating pixel shader");
	}

	// Create vertex shader for framebuffer
	if (FAILED(hr = _device->CreateVertexShader(
		FramebufferShaders::FramebufferVSBytecode,
		sizeof(FramebufferShaders::FramebufferVSBytecode),
		nullptr,
		&_vertexShader)))
	{
		throw GFX_EXCEPTION(hr, L"Creating vertex shader");
	}

	// Create and fill vertex buffer with quad for rendering frame
	const FSQVertex vertices[] =
	{
		{ -1.0f,1.0f,0.5f,0.0f,0.0f },
		{ 1.0f,1.0f,0.5f,1.0f,0.0f },
		{ 1.0f,-1.0f,0.5f,1.0f,1.0f },
		{ -1.0f,1.0f,0.5f,0.0f,0.0f },
		{ 1.0f,-1.0f,0.5f,1.0f,1.0f },
		{ -1.0f,-1.0f,0.5f,0.0f,1.0f },
	};
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(FSQVertex) * 6;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0u;
	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices;
	if (FAILED(hr = _device->CreateBuffer(&bd, &initData, &_vertexBuffer)))
	{
		throw GFX_EXCEPTION(hr, L"Creating vertex buffer");
	}

	// Create input layout for fullscreen quad
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};

	if (FAILED(hr = _device->CreateInputLayout(ied, 2,
		FramebufferShaders::FramebufferVSBytecode,
		sizeof(FramebufferShaders::FramebufferVSBytecode),
		&_inputLayout)))
	{
		throw GFX_EXCEPTION(hr, L"Creating input layout");
	}

	// Create sampler state for fullscreen textured quad
	D3D11_SAMPLER_DESC sampDesc = {};
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	if (FAILED(hr = _device->CreateSamplerState(&sampDesc, &_samplerState)))
	{
		throw GFX_EXCEPTION(hr, L"Creating sampler state");
	}

	std::string fontFile = "..\\..\\..\\..\\Resources\\fonts\\italic.spritefont";
	std::wstring widestr = std::wstring(fontFile.begin(), fontFile.end());
	const wchar_t* szFile = widestr.c_str();
	_fonts.reset(new SpriteFont(_device.Get(), szFile));

	_sprites.reset(new SpriteBatch(_immediateContext.Get()));
	_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(_immediateContext.Get());
}

void TestGraphics::DrawComponent(IDrawableComponent * component)
{
	switch (component->Type)
	{
		case DrawableComponentType::eTestDrawingType:
			break;

		// Below is an example of what an implementation might look like
		/*case DrawableComponentType::eSprite:
			SpriteRendererComponent* drawComponent = dynamic_cast<SpriteRendererComponent*>(component);
			DrawSprite(drawComponent.Name, drawComponent.Pos, drawComponent.Rect, drawComponent.Rot, drawComponent.Scale, drawComponent.Offset);
			break;*/
	}
}

void TestGraphics::DrawSprite(std::string name, Vec2 pos, RECT * rect, float rot, float scale, Vec2 offset)
{
}

void TestGraphics::DrawLine(Vec2 v1, Vec2 v2)
{
}

void TestGraphics::DrawText(std::string text, Vec2 pos, float rot, float* rgb, float scale, Vec2 offset)
{
}

void TestGraphics::Destroy()
{
	// Clear the state of the device context before destruction
	if (_immediateContext) _immediateContext->ClearState();
}

void TestGraphics::BeginFrame()
{
	// Clear render target view
	_immediateContext->ClearRenderTargetView(_renderTargetView.Get(), Colors::MidnightBlue);
	_sprites->Begin(SpriteSortMode_Deferred);
	_primitiveBatch->Begin();
}

void TestGraphics::EndFrame()
{
	HRESULT hr;

	// Render offscreen scene texture to back buffer
	_immediateContext->IASetInputLayout(_inputLayout.Get());
	_immediateContext->VSSetShader(_vertexShader.Get(), nullptr, 0u);
	_immediateContext->PSSetShader(_pixelShader.Get(), nullptr, 0u);
	_immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	const UINT stride = sizeof(FSQVertex);
	const UINT offset = 0u;
	_immediateContext->IASetVertexBuffers(0u, 1u, _vertexBuffer.GetAddressOf(), &stride, &offset);
	_immediateContext->PSSetShaderResources(0u, 1u, _sysBufferTextureView.GetAddressOf());
	_immediateContext->PSSetSamplers(0u, 1u, _samplerState.GetAddressOf());
	_immediateContext->Draw(6u, 0u);

	_sprites->End();
	_primitiveBatch->End();

	// Flip back/front buffers
	if (FAILED(hr = _swapChain->Present(1u, 0u)))
	{
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
		{
			throw GFX_EXCEPTION(_device->GetDeviceRemovedReason(), L"Presenting back buffer [device removed]");
		}
		else
		{
			throw GFX_EXCEPTION(hr, L"Presenting back buffer");
		}
	}
}

// TestGraphics Exception
TestGraphics::Exception::Exception(HRESULT hr, const std::wstring& note, const wchar_t* file, unsigned int line)
	:
	CustomException(file, line, note),
	hr(hr)
{}

std::wstring TestGraphics::Exception::GetFullMessage() const
{
	const std::wstring empty = L"";
	const std::wstring errorName = GetErrorName();
	const std::wstring errorDesc = GetErrorDescription();
	const std::wstring& note = GetNote();
	const std::wstring location = GetLocation();
	return    (!errorName.empty() ? std::wstring(L"Error: ") + errorName + L"\n"
		: empty)
		+ (!errorDesc.empty() ? std::wstring(L"Description: ") + errorDesc + L"\n"
			: empty)
		+ (!note.empty() ? std::wstring(L"Note: ") + note + L"\n"
			: empty)
		+ (!location.empty() ? std::wstring(L"Location: ") + location
			: empty);
}

std::wstring TestGraphics::Exception::GetErrorName() const
{
	return DXGetErrorString(hr);
}

std::wstring TestGraphics::Exception::GetErrorDescription() const
{
	std::array<wchar_t, 512> wideDescription;
	DXGetErrorDescription(hr, wideDescription.data(), wideDescription.size());
	return wideDescription.data();
}

std::wstring TestGraphics::Exception::GetExceptionType() const
{
	return L"TestGraphics Exception";
}