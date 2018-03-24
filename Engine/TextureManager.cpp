//#include "TextureManager.h"
//
//
//
//TextureManager::TextureManager()
//{
//}
//
//
//TextureManager::~TextureManager()
//{
//}
//
//HRESULT TextureManager::RetrieveTexture(std::string name, ID3D11ShaderResourceView * textureOut)
//{
//	return E_NOTIMPL;
//}
//
//HRESULT TextureManager::LoadTexture(std::string path)
//{
//	
//	//converting name into adress of texture file
//	std::wstring wstrName = std::wstring(path.begin(), path.end());
//	const wchar_t *textureToDraw = wstrName.c_str();
//	ID3D11ShaderResourceView* text = nullptr;
//		
//	/*HRESULT hr = CreateDDSTextureFromFile(_device.Get(), textureToDraw, nullptr, &text); //TODO : CreateDDSTextureFromFile
//	if (FAILED(hr)) {
//		MessageBox(0, L"Problem loading texture", 0, 0);
//		return hr;
//	}
//
//	_textures[path] = text;
//
//	return S_OK;*/
//}
//
//ID3D11ShaderResourceView * TextureManager::GetTexture(std::string path)
//{
//
//	/*::map<std::string, ID3D11ShaderResourceView*>::iterator it = _textures.find(path);
//	if (it != _textures.end()) { //texture found
//		return it->second;
//	}
//	else
//		return nullptr; //Texture not found/loaded yet 
//		*/
//}
//
