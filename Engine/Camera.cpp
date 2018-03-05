#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

XMFLOAT3 Camera::GetPosition() const
{
	return _position;
}

XMFLOAT3 Camera::GetRightAxis() const
{
	return _rightAxis;
}

XMFLOAT3 Camera::GetUpAxis() const
{
	return _upAxis;
}

XMFLOAT3 Camera::GetLookAxis() const
{
	return _lookAxis;
}

XMVECTOR Camera::GetPositionVec() const
{
	return XMLoadFloat3(&_position);
}

XMVECTOR Camera::GetRightAxisVec() const
{
	return XMLoadFloat3(&_rightAxis);
}

XMVECTOR Camera::GetUpAxisVec() const
{
	return XMLoadFloat3(&_upAxis);
}

XMVECTOR Camera::GetLookAxisVec() const
{
	return XMLoadFloat3(&_lookAxis);
}

float Camera::GetNearPlane() const
{
	return _nearPlane;
}

float Camera::GetFarPlane() const
{
	return _farPlane;
}

float Camera::GetFoV() const
{
	return _fieldOfView;
}

float Camera::GetAspectRatio() const
{
	return _aspectRatio;
}

float Camera::GetNearWndHeight() const
{
	return _nearWndHeight;
}

float Camera::GetFarWndHeight() const
{
	return _farWndHeight;
}

void Camera::SetPosition(const XMFLOAT3 & position)
{
	_position = position;
}

void Camera::SetPosition(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

void Camera::SetFrustum(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	_fieldOfView = fieldOfView;
	_aspectRatio = aspectRatio;
	_nearPlane = nearPlane;
	_farPlane = farPlane;
}

void Camera::Walk(float distance)
{
	//changing the position according to the distance 
	XMVECTOR dist = XMVectorReplicate(distance);
	XMVECTOR look = XMLoadFloat3(&_lookAxis);
	XMVECTOR pos = XMLoadFloat3(&_position);

	XMStoreFloat3(&_position, XMVectorMultiplyAdd(dist, look, pos));
}

void Camera::RotateYAxis(float angle)
{
	//rotation around the y axis by angle "angle"
	XMMATRIX rotationY = XMMatrixRotationY(angle);
	
	XMVECTOR rightAxisVec = XMLoadFloat3(&_rightAxis);
	XMVECTOR lookAxisVec = XMLoadFloat3(&_lookAxis);
	XMVECTOR upAxisVec = XMLoadFloat3(&_upAxis);
	
	XMStoreFloat3(&_lookAxis, XMVector3TransformNormal(lookAxisVec, rotationY));
	XMStoreFloat3(&_rightAxis, XMVector3TransformNormal(rightAxisVec, rotationY));
	XMStoreFloat3(&_upAxis, XMVector3TransformNormal(upAxisVec, rotationY));

}

void Camera::Pitch(float angle)
{
	//rotation around x axis
	XMVECTOR rightAxisVec = XMLoadFloat3(&_rightAxis);
	XMVECTOR upAxisVec = XMLoadFloat3(&_upAxis);
	XMVECTOR lookAxisVec = XMLoadFloat3(&_lookAxis);

	XMMATRIX rotationX = XMMatrixRotationAxis(rightAxisVec, angle);

	XMStoreFloat3(&_lookAxis, XMVector3TransformNormal(lookAxisVec, rotationX));
	XMStoreFloat3(&_upAxis, XMVector3TransformNormal(upAxisVec, rotationX));
}

void Camera::UpdateViewMatrix()
{
	//TODO

}

void Camera::SetCameraSpace(const XMFLOAT3 & position, const XMFLOAT3 & lookAxis, const XMFLOAT3 & upAxis)
{
	_position = position;
	_lookAxis = lookAxis;
	_upAxis = upAxis;
}

void Camera::SetCameraSpace(FXMVECTOR position, FXMVECTOR lookAxis, FXMVECTOR upAxis)
{
	XMStoreFloat3(&_position, position);
	XMStoreFloat3(&_lookAxis, lookAxis);
	XMStoreFloat3(&_upAxis, upAxis);

	
}
