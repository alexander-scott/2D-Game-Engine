#pragma once

#include "ISystemMessage.h"

struct Vec2;

class DrawSpriteMessage : public ISystemMessage
{
public:
	DrawSpriteMessage(std::string name, Vec2 pos, RECT* rect, float rot, float scale, Vec2 offset) : ISystemMessage(SystemMessageType::eGraphicsDrawSprite)
	{ 
		Name = name;
		Pos = pos;
		Rect = rect;
		Rot = rot;
		Scale = scale;
		Offset = offset;
	}

	std::string Name;
	Vec2 Pos;
	RECT* Rect;
	float Rot;
	float Scale;
	Vec2 Offset;
};