#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Camera 
{
public:
	Camera(float xOffset, float yOffset);
	~Camera();

	void MovePosition(float xMov, float yMov);

	void SetXOffset(float xOffset);
	void SetYOffset(float yOffset);
	float GetXOffset();
	float GetYOffset();

private:
	float _xOffset;
	float _yOffset;

};
