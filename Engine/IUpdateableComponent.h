#pragma once

class IUpdateableComponent
{
public:
	virtual void Update(float deltaTime) = 0;
};