#pragma once

#include "IGraphics.h"
#include "Consts.h"
#include "DirectXMath.h"
#include <vector>
#include <d3dcommon.h>
#include "d3d11.h"

using namespace DirectX;
class HWNDKey;

class TestGraphics : public IGraphics
{
public:
	TestGraphics(std::shared_ptr<SystemMessageDispatcher> dispatcher) 
		: IGraphics(dispatcher) { }
	TestGraphics(std::shared_ptr<SystemMessageDispatcher> dispatcher, HWNDKey &key);

	//TestGraphics(HWNDKey &key);
	~TestGraphics();

	virtual void Initalise(class HWNDKey& key) override;
protected:
	virtual void Destroy() override;

	virtual void EndFrame() override;
	virtual void BeginFrame() override;

	virtual void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot, float scale, Vec2 offset) override;

	virtual void DrawText2D(std::string text, Vec2 pos, float rot, float* rgb, float scale, Vec2 offset) override;

	virtual void DrawLine(Vec2 v1, Vec2 v2) override;


	void DrawBackground();

	ID3D11Device*			_d3dDevice = nullptr;
	ID3D11DeviceContext*	_immediateContext = nullptr;
	IDXGISwapChain*			_swapChain = nullptr;
	D3D_DRIVER_TYPE			_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL		_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Texture2D*		_backBuffer = nullptr;
	ID3D11RenderTargetView*	_renderTargetView = nullptr;
	ID3D11Texture2D*		_depthStencil = nullptr;
	ID3D11DepthStencilView*	_depthStencilView = nullptr;
};