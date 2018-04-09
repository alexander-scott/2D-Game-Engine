/*#pragma once
#include "Consts.h"
#include <d3d11.h>
#include "DirectXTK\Inc\SpriteBatch.h"
#include "DirectXTK\Inc\DDSTextureLoader.h"
//follows the singleton pattern
//class DxGraphics;

class TextureManager
{
public:
	//static std::map<std::string, ID3D11ShaderResourceView*> _texturesMap;
	//static std::map<std::string name, std::string path> _namePath;
	static TextureManager* GetInstance();
	
	//HRESULT RetrieveTexture(std::map<std::string, ID3D11ShaderResourceView*> textures, std::string name, ID3D11ShaderResourceView* textureOut);
	ID3D11ShaderResourceView * GetTexture(DxGraphics &dxGraphics, std::string path);
	HRESULT LoadTexture(DxGraphics &dxGraphics, std::string path);

private:
	TextureManager();
	~TextureManager();
	static TextureManager* _instance;
};

*/