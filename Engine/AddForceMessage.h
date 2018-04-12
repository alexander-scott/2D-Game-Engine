#pragma once

#include "IComponentMessage.h"

struct Vec2;

class AddForceMessage : public IComponentMessage
{
public:
	AddForceMessage(Vec2 dir, float power) : IComponentMessage(ComponentMessageType::eAddForce)
	{
		Direction = dir;
		Power = power;
	}

	Vec2				Direction;
	float				Power;
};
