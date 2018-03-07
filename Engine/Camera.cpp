#include "Camera.h"



Camera::Camera()
{
}

Camera::Camera(XMFLOAT3 position, XMFLOAT3 rightAxis, XMFLOAT3 upAxis, XMFLOAT3 lookAxis, float nearPlane, float farPlane, float fieldOfView, float aspectRatio)
{
	_position = position;
	_rightAxis = rightAxis;
	_upAxis = upAxis;
	_lookAxis = lookAxis;
	_nearPlane = nearPlane;
	_farPlane = farPlane;
	_fieldOfView = fieldOfView;
	_aspectRatio = aspectRatio;
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

void Camera::RotateX(float angle)
{
	//rotation around x axis
	XMVECTOR rightAxisVec = XMLoadFloat3(&_rightAxis);
	XMVECTOR upAxisVec = XMLoadFloat3(&_upAxis);
	XMVECTOR lookAxisVec = XMLoadFloat3(&_lookAxis);

	XMMATRIX rotationX = XMMatrixRotationAxis(rightAxisVec, angle);

	XMStoreFloat3(&_lookAxis, XMVector3TransformNormal(lookAxisVec, rotationX));
	XMStoreFloat3(&_upAxis, XMVector3TransformNormal(upAxisVec, rotationX));
}

void Camera::RotateY(float angle)
{
	XMMATRIX rotation = XMMatrixRotationY(angle);

	//calculates new axis "values"
	XMVECTOR rightNormal = XMVector3TransformNormal(XMLoadFloat3(&_rightAxis), rotation); //transforms 3D normal by rotation (y) axis
	XMVECTOR lookNormal = XMVector3TransformNormal(XMLoadFloat3(&_lookAxis), rotation);
	XMVECTOR upNormal = XMVector3TransformNormal(XMLoadFloat3(&_upAxis), rotation);

	//gives the new values to the axis 
	XMStoreFloat3(&_rightAxis, rightNormal);
	XMStoreFloat3(&_lookAxis, lookNormal);
	XMStoreFloat3(&_upAxis, upNormal);
}

void Camera::TranslateX(float distance)
{
	XMVECTOR dist = XMVectorReplicate(distance); //convert distance into a vec
	XMVECTOR right = XMLoadFloat3(&_rightAxis);
	XMVECTOR pos = XMLoadFloat3(&_position);

	XMVECTOR newPos = XMVectorMultiplyAdd(pos, right, dist); //(pos+right)*dist
	XMStoreFloat3(&_position, newPos);
}

void Camera::TranslateZ(float distance) //walk along look axis
{
	XMVECTOR dist = XMVectorReplicate(distance); //convert distance into a vec
	XMVECTOR look = XMLoadFloat3(&_lookAxis);
	XMVECTOR pos = XMLoadFloat3(&_position);

	XMVECTOR newPos = XMVectorMultiplyAdd(pos, look, dist); //(pos+look)*dist
	XMStoreFloat3(&_position, newPos);
}

void Camera::UpdateViewMatrix()
{
	//loading position + axis into XMVectors
	XMVECTOR position = XMLoadFloat3(&_position);
	XMVECTOR rightVec = XMLoadFloat3(&_rightAxis);
	XMVECTOR upVec = XMLoadFloat3(&_upAxis);
	XMVECTOR lookVec = XMLoadFloat3(&_lookAxis);

	//normalization and correction of the vectors defining the camera space
	lookVec = XMVector3Normalize(lookVec);

	upVec = XMVector3Cross(lookVec, rightVec);//correction of the upVector
	upVec = XMVector3Normalize(upVec); //normalization

	//now that lookVec and upVec are normalized & "corrected"
	//we can just do the cross product of the two to get rightVec
	//nb : we chose left handed coordinates // x = y X z // right = up X look
	rightVec = XMVector3Cross(upVec, lookVec);


	//float dotProdPosLook = XMVector3Dot(position, lookVec);
	//view matrix : 
	//ux  , vx  , wx  , 0
	//uy  , vy  , wy  , 0 
	//uz  , vz  , wz  , 0
	//-Q.u, -Q.v, -Q.w, 1 
	//with : u = right // v = up // w = look

	float x = XMVectorGetX(XMVector3Dot(position, rightVec));
	float y = XMVectorGetX(XMVector3Dot(position, upVec));
	float z = XMVectorGetX(XMVector3Dot(position, lookVec));

	XMStoreFloat3(&_rightAxis, rightVec);
	XMStoreFloat3(&_lookAxis, lookVec);
	XMStoreFloat3(&_upAxis, upVec);

	//now filling the view matrix with updated values
	_viewMatrix(0, 0) = _rightAxis.x;
	_viewMatrix(0, 1) = _upAxis.x;
	_viewMatrix(0, 2) = _lookAxis.x;
	_viewMatrix(0, 3) = 0.0f;

	_viewMatrix(1, 0) = _rightAxis.y;
	_viewMatrix(1, 1) = _upAxis.y;
	_viewMatrix(1, 2) = _lookAxis.y;
	_viewMatrix(1, 3) = 0.0f;

	_viewMatrix(2, 0) = _rightAxis.z;
	_viewMatrix(2, 1) = _upAxis.z;
	_viewMatrix(2, 2) = _lookAxis.z;
	_viewMatrix(2, 3) = 0.0f;

	_viewMatrix(3, 0) = -x;
	_viewMatrix(3, 1) = -y;
	_viewMatrix(3, 2) = -z;
	_viewMatrix(3, 3) = 1.0f;

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

void Camera::UpdateProjectionMatrix(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	_fieldOfView = fieldOfView;
	_aspectRatio = aspectRatio;
	_nearPlane = nearPlane;
	_farPlane = farPlane;

	_nearWndHeight = 2.0f * _nearPlane * tanf(0.5f * _fieldOfView);
	_farWndHeight = 2.0f * _farPlane * tanf(0.5f * _fieldOfView);

	XMMATRIX newProjMatrix = XMMatrixPerspectiveFovLH(_fieldOfView, _aspectRatio, _nearPlane, _farPlane);

	//set the projMatrix as the newProjMatrix
	XMStoreFloat4x4(&_projMatrix, newProjMatrix);
	
}
