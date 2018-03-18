#pragma once
#include "Consts.h"
#include <d3d11.h>
#include "DirectXTK\Inc\SpriteBatch.h"
#include "DirectXTK\Inc\DDSTextureLoader.h"

class TextureManager
{
public:
	static std::map<std::string, ID3D11ShaderResourceView*> _texturesMap;
	//static std::map<std::string name, std::string path> _namePath;
	
	TextureManager();
	~TextureManager();
	
	HRESULT RetrieveTexture(std::string name, ID3D11ShaderResourceView* textureOut);
	HRESULT LoadTexture(std::string path);

};

