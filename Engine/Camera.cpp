#include "Camera.h"





Camera::Camera(float xOffset, float yOffset)
{
	_xOffset = xOffset;
	_yOffset = yOffset;
}

Camera::~Camera()
{
}

void Camera::MovePosition(float xMov, float yMov)
{
	_xOffset += xMov;
	_yOffset += yMov;
}

void Camera::SetXOffset(float xOffset)
{
	_xOffset = xOffset;
}

void Camera::SetYOffset(float yOffset)
{
	_yOffset = yOffset;
}

float Camera::GetXOffset()
{
	return _xOffset;
}

float Camera::GetYOffset()
{
	return _yOffset;
}

