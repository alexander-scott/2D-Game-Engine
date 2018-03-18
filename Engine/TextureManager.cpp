#include "TextureManager.h"



TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

HRESULT TextureManager::RetrieveTexture(std::string name, ID3D11ShaderResourceView * textureOut)
{
	return E_NOTIMPL;
}

HRESULT TextureManager::LoadTexture(std::string path)
{
	/*std::wstring wstrName = std::wstring(path.begin(), path.end());
	const wchar_t *textureToDraw = wstrName.c_str();

	ID3D11ShaderResourceView* text = nullptr;
	//	HRESULT hr = CreateDDSTextureFromFile(_device.Get(), textureToDraw, nullptr, &_sysBufferTextureView);
	HRESULT hr = CreateDDSTextureFromFile(_device.Get(), textureToDraw, nullptr, &text);
	if (FAILED(hr)) {
		MessageBox(0, L"Nope", 0, 0);
	}
	*/
	return E_NOTIMPL;
}
