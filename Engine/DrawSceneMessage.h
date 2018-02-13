#pragma once

#include "ISystemMessage.h"

class DrawSceneMessage : public ISystemMessage
{
public:
	DrawSceneMessage() : ISystemMessage(SystemMessageType::eGraphicsDrawScene) { }

	void AddSpriteData(SpriteData spriteData)
	{
		_spriteData.push_back(spriteData);
	}

	void AddTextData(TextData textData)
	{
		_textData.push_back(textData);
	}

	std::vector<SpriteData>& GetSpriteData() { return _spriteData; }
	std::vector<TextData>& GetTextData() { return _textData; }

private:
	std::vector<SpriteData>		_spriteData;
	std::vector<TextData>		_textData;
};