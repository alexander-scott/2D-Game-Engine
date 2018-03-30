#include "DxGraphics.h"

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

#define GFX_EXCEPTION( hr,note ) DxGraphics::Exception( hr,note,_CRT_WIDE(__FILE__),__LINE__ )

using Microsoft::WRL::ComPtr;

DxGraphics::DxGraphics(std::shared_ptr<SystemMessageDispatcher> dispatcher)
	: IGraphics(dispatcher)
{
	
}

void DxGraphics::Initalise(HWNDKey& key)
{
	//todo:delete
	this->_animation.LoadXml("toChange");

		
	//end todo
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

	std::string fontFile = "..\\Resources\\fonts\\italic.spritefont";
	std::wstring widestr = std::wstring(fontFile.begin(), fontFile.end());	

	_sprites.reset(new SpriteBatch(_immediateContext.Get()));
	_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(_immediateContext.Get());

	//Create font 
	_fonts.reset(new SpriteFont(_device.Get(), L"..\\Resources\\fonts\\italic.spritefont"));
}

void DxGraphics::DrawComponent(IDrawableComponent * component)
{
	switch (component->Type)
	{
		case DrawableComponentType::eTestDrawingType: 
		{
			break;
		}

		case DrawableComponentType::eText:
		{
			TextRendererComponent * textComponent = dynamic_cast<TextRendererComponent*>(component);
			DrawText(textComponent->GetText(), textComponent->GetPosition(), textComponent->GetRotation(),
				textComponent->GetRbg3(), textComponent->GetScale(), textComponent->GetOffset());
			break;
		}
		case DrawableComponentType::eSprite: 
		{
			SpriteRendererComponent * drawComponent = dynamic_cast<SpriteRendererComponent*>(component);
			DrawSprite(drawComponent->GetName(), drawComponent->GetPosition(), drawComponent->GetRect(),
				drawComponent->GetRotation(), drawComponent->GetScale(), drawComponent->GetOffset());
			break;
		}
		default:
			break;
	}
}

void DxGraphics::DrawSprite(std::string name, Vec2 pos, RECT * rect, float rot, float scale, Vec2 offset)
{
	ID3D11ShaderResourceView* text = nullptr;
	
	if (GetTexture(name)==nullptr) { //Texture has not been loaded yet
		if (FAILED(LoadTexture(name)))
			MessageBox(0, L"Problem loading texture", 0, 0);
	}
	if (GetTexture(name) != nullptr) { //texture successfully loaded and now we retrieve it
		text = GetTexture(name);
	}
		//offset has been set manually in the scene object (xml file). For the test sprite used here it is set on the center
		//ie : x = rect.width/2 = 54 / 2 = 27
		//y = rect.height/2 = 45 / 2 = 22.5
		//wouldn't it be better to calculate the offset in code? else we'd have to do it for each sprite we want to draw 

	_sprites->Draw(text, XMFLOAT2(pos.x, pos.y), rect, Colors::White, rot, XMFLOAT2(offset.x, offset.y), scale); //todo : change offset

}

void DxGraphics::DrawLine(Vec2 v1, Vec2 v2)
{
		
}

HRESULT DxGraphics::LoadTexture(std::string path)
{
	//converting name into adress of texture file
	/*std::wstring wstrName = std::wstring(path.begin(), path.end());
	const wchar_t *textureToDraw = wstrName.c_str();
	ID3D11ShaderResourceView* text = nullptr;

	HRESULT hr = CreateDDSTextureFromFile(_device.Get(), textureToDraw, nullptr, &text);
	if (FAILED(hr)) {
		MessageBox(0, L"Problem loading texture", 0, 0);
		return hr;
	}
	
	_textures[path] = text;

	return S_OK;*/
	return TextureManager::GetInstance()->LoadTexture(*this, path);
}


ID3D11ShaderResourceView * DxGraphics::GetTexture(std::string path)
{

	/*std::map<std::string, ID3D11ShaderResourceView*>::iterator it = _textures.find(path);
	if (it != _textures.end()) { //texture found
		return it->second;
	}
	else
		return nullptr; //Texture not found/loaded yet */
	return TextureManager::GetInstance()->GetTexture(*this, path);
}


void DxGraphics::DrawText(std::string text, Vec2 pos, float rot, float4* rgb3, float scale, Vec2 offset)
{
	//TODO : apply rotation, scale, use offset on pos, use rgb chosen.
	std::wstring wstrText = std::wstring(text.begin(), text.end());
	const wchar_t *txtToDraw = wstrText.c_str();

	XMVECTORF32 textColor = { { { rgb3->x , rgb3->y, rgb3->z, rgb3->w} } };
	
	XMVECTOR textRect = _fonts->MeasureString(txtToDraw);
	float widthText = textRect.m128_f32[0];
	float heightText = textRect.m128_f32[1];
	
	_fonts->DrawString(_sprites.get(), txtToDraw, XMFLOAT2(pos.x, pos.y), textColor, rot, XMFLOAT2(offset.x, offset.y), scale); //offset is set at 0.0f, 0.0f in the xml file so far
	//_fonts->DrawString(_sprites.get(), txtToDraw, XMFLOAT2(pos.x, pos.y), textColor, 0.3f, XMFLOAT2(widthText/2, heightText/2), scale); //here we calculate the offset so that it is at the center of the text rect. doesn't seem to be exactlyat the center though...
	
}

void DxGraphics::Destroy()
{
	// Clear the state of the device context before destruction
	if (_immediateContext) _immediateContext->ClearState();
}

void DxGraphics::BeginFrame()
{
	// Clear render target view
	_immediateContext->ClearRenderTargetView(_renderTargetView.Get(), Colors::LightPink);
	_sprites->Begin(SpriteSortMode_Deferred);
	_primitiveBatch->Begin();

}

void DxGraphics::EndFrame()
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
DxGraphics::Exception::Exception(HRESULT hr, const std::wstring& note, const wchar_t* file, unsigned int line)
	:
	CustomException(file, line, note),
	hr(hr)
{}

std::wstring DxGraphics::Exception::GetFullMessage() const
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

std::wstring DxGraphics::Exception::GetErrorName() const
{
	return DXGetErrorString(hr);
}

std::wstring DxGraphics::Exception::GetErrorDescription() const
{
	std::array<wchar_t, 512> wideDescription;
	DXGetErrorDescription(hr, wideDescription.data(), wideDescription.size());
	return wideDescription.data();
}

std::wstring DxGraphics::Exception::GetExceptionType() const
{
	return L"TestGraphics Exception";
}


TextureManager* TextureManager::_instance = 0;

TextureManager::TextureManager() {

}

TextureManager* TextureManager::GetInstance() {

	if (_instance == 0) {
		_instance = new TextureManager();
	}

	return _instance;
}

ID3D11ShaderResourceView * TextureManager::GetTexture(DxGraphics &dxGraphics, std::string path)
{
	std::map<std::string, ID3D11ShaderResourceView*>::iterator it = dxGraphics._textures.find(path);
	if (it != dxGraphics._textures.end()) { //texture found
		return it->second;
	}
	else
		return nullptr; //Texture not found/loaded yet 
}

HRESULT TextureManager::LoadTexture(DxGraphics &dxGraphics, std::string path)
{
	//converting name into adress of texture file
	std::wstring wstrName = std::wstring(path.begin(), path.end());
	const wchar_t *textureToDraw = wstrName.c_str();
	ID3D11ShaderResourceView* text = nullptr;

	HRESULT hr = CreateDDSTextureFromFile(dxGraphics._device.Get(), textureToDraw, nullptr, &text);
	if (FAILED(hr)) {
		MessageBox(0, L"Problem loading texture", 0, 0);
		return hr;
	}

	dxGraphics._textures[path] = text;

	return S_OK;
}

