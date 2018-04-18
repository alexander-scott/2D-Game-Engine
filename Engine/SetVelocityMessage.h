#pragma once

#include "IComponentMessage.h"

struct Vec2;

class SetVelocityMessage : public IComponentMessage
{
public:
	SetVelocityMessage(Vec2 velocity) : IComponentMessage(ComponentMessageType::eSetVelocityMessage)
	{
		Velocity = velocity;
	}

	Vec2				Velocity;
};
