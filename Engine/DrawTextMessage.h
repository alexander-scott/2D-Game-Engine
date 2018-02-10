#pragma once

#include "ISystemMessage.h"

class DrawTextMessage : public ISystemMessage
{
public:
	DrawTextMessage(std::string text, Vec2 pos, float rot, float* rgbColours, float scale, Vec2 offset) 
		: ISystemMessage(SystemMessageType::eGraphicsDrawText) 
	{ 
		Text = text;
		Pos = pos;
		Rot = rot;
		RgbColours = rgbColours;
		Scale = scale;
		Offset = offset;
	}

	std::string		Text;
	Vec2			Pos;
	float			Rot;
	float*			RgbColours;
	float			Scale; 
	Vec2			Offset;
};