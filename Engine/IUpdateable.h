#pragma once

class IUpdateable
{
public:
	virtual void Update(float deltaTime) = 0;
};