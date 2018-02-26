#include "TestGraphics.h"

#include <DirectXMath.h>
#pragma comment(lib, "d3d11.lib")
#define GFX_EXCEPTION( hr,note ) TestGraphics::Exception( hr,note,_CRT_WIDE(__FILE__),__LINE__ )

class HWNDKey
{
public:
	HWNDKey(const HWNDKey&) = delete;
	HWNDKey& operator=(HWNDKey&) = delete;
	HWNDKey() = default;
	HWND hWnd = nullptr;
};

TestGraphics::TestGraphics(std::shared_ptr<SystemMessageDispatcher> dispatcher, HWNDKey & key) : IGraphics(dispatcher)
{
	//assert(key.hWnd != nullptr);
	HWND hWnd = key.hWnd;

}

TestGraphics::~TestGraphics()
{
	Destroy();
}

void TestGraphics::Initalise(HWNDKey & key)
{
	//TODO : make testgraphic friend with main window + use key
	//Initialization of the Dxdevice
		//nb : SCREEN_WIDTH & SCREEN_HEIGHT : dimensions of the window
	assert(key.hWnd != nullptr);
	
	HWND hWnd = key.hWnd;
	
	RECT rc;
	GetClientRect(hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	HRESULT hr;


	//Device flag, driver types & feature levels

	UINT createDeviceFlags = 0;
	#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif


	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);


	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);


	//Creation of the swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width; 
	swapChainDesc.BufferDesc.Height = height; 
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = key.hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++) {
		_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(nullptr, _driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &swapChainDesc, &_swapChain, &_d3dDevice, &_featureLevel, &_immediateContext);
		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr)){
		throw GFX_EXCEPTION(hr, L"Creating device & swap chain - TestGraphics - Initialise");
		}

	//Creation of the render target view
	//ID3D11Texture2D *backBuffer = nullptr;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&_backBuffer);
	if (FAILED(hr))
		throw GFX_EXCEPTION(hr, L"Problem creating backbuffer, TestGraphics.cpp");
		
	hr = _d3dDevice->CreateRenderTargetView(_backBuffer, nullptr, &_renderTargetView);
	//_backBuffer->Release();
	if (FAILED(hr))
		throw GFX_EXCEPTION(hr, L"Problem rendering target view, TestGraphics.cpp");
	
	//Creation of the depth stencil structure
	D3D11_TEXTURE2D_DESC depthStencilStructDesc;
	ZeroMemory(&depthStencilStructDesc, sizeof(depthStencilStructDesc));
	depthStencilStructDesc.Width = width; //TODO : Uncomment when hWnd retrieved
	depthStencilStructDesc.Height = height; //TODO : Uncomment when hWnd retrieved
	depthStencilStructDesc.MipLevels = 1;
	depthStencilStructDesc.ArraySize = 1;
	depthStencilStructDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilStructDesc.SampleDesc.Count = 1;
	depthStencilStructDesc.SampleDesc.Quality = 0;
	depthStencilStructDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilStructDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilStructDesc.CPUAccessFlags = 0;
	depthStencilStructDesc.MiscFlags = 0;
	hr = _d3dDevice->CreateTexture2D(&depthStencilStructDesc, nullptr, &_depthStencil);

	if (FAILED(hr))
		throw GFX_EXCEPTION(hr, L"Error creating depth stencil structure - TestGraphics.cpp");
	
	//Creation of the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = depthStencilViewDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	hr = _d3dDevice->CreateDepthStencilView(_depthStencil, &depthStencilViewDesc, &_depthStencilView);

	if (FAILED(hr))
		throw GFX_EXCEPTION(hr, L"Failed creating the depth stencil view, TestGraphics.cpp");

	//Binding the targets & depth stencil view/buffer to the output merger stage
	try {
		_immediateContext->OMGetRenderTargets(1, &_renderTargetView, &_depthStencilView);
	}
	catch (Exception e) {
		std::wstring er = e.GetErrorDescription(); //doesn't go here
	}
	
	//Setting up the viewport (Change if you want several in your game)
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)width;  // = SCREEN_WIDTH from Consts.h but can be changed if desired
	viewport.Height = (FLOAT)height; 
	viewport.MaxDepth = 1.0f;
	viewport.MinDepth = 0.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	_immediateContext->RSSetViewports(1, &viewport);
	

}

void TestGraphics::Destroy()
{
	if (_immediateContext) _immediateContext->ClearState();
	if (_depthStencilView) _depthStencilView->Release();
	if (_depthStencil) _depthStencil->Release();
	if (_renderTargetView) _renderTargetView->Release();
	if (_swapChain) _swapChain->Release();
	if (_immediateContext) _immediateContext->Release();
	if (_d3dDevice) _d3dDevice->Release();

}

void TestGraphics::EndFrame()
{
}

void TestGraphics::BeginFrame()
{
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

void TestGraphics::DrawText2D(std::string text, Vec2 pos, float rot, float * rgb, float scale, Vec2 offset)
{
}

void TestGraphics::DrawLine(Vec2 v1, Vec2 v2)
{
}

void TestGraphics::DrawBackground()
{
	//just testing if drawing a color could work. 
	//Error : renderTargetView = nullptr, didn't find why yet :/
	//(problem starts in Initialise : createdepthstencilview lets depthStencilView null but shouldn't 
	XMVECTORF32 couleur = { 0.90f, 0.8f, 0.95f, 1.000000000f };
	_immediateContext->ClearRenderTargetView(_renderTargetView, couleur);

}

TestGraphics::Exception::Exception(HRESULT hr, const std::wstring& note, const wchar_t* file, unsigned int line)
	:
	CustomException(file, line, note),
	hr(hr)
{ }

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
	return L"Graphics Error name";
}

std::wstring TestGraphics::Exception::GetErrorDescription() const
{
	return L"Graphics Error Description";
}

std::wstring TestGraphics::Exception::GetExceptionType() const
{
	return L"Graphics Exception";
}