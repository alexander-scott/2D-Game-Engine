#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Camera
{
public:
	Camera();
	~Camera();

private:
	//Position+Orientation variables (work on left handed orientation)
	XMFLOAT3 _position;
	XMFLOAT3 _rightAxis; //x axis
	XMFLOAT3 _upAxis; // y axis
	XMFLOAT3 _lookAxis; //z axis

	//View & projection matrices
	XMFLOAT4X4 _viewMatrix;
	XMFLOAT4X4 _projMatrix;

	//Frustum
	float _nearPlane;
	float _farPlane;
	float _fieldOfView;
	float _aspectRatio;
	float _nearWndHeight;
	float _farWndHeight;


public:
	//getters
		XMFLOAT3 GetPosition() const;
		XMFLOAT3 GetRightAxis() const;
		XMFLOAT3 GetUpAxis() const;
		XMFLOAT3 GetLookAxis() const;

		XMVECTOR GetPositionVec() const;
		XMVECTOR GetRightAxisVec() const;
		XMVECTOR GetUpAxisVec() const;
		XMVECTOR GetLookAxisVec() const;

		float GetNearPlane() const;
		float GetFarPlane() const;
		float GetFoV() const;
		float GetAspectRatio() const;
		float GetNearWndHeight() const;
		float GetFarWndHeight() const;


	//setters
		//set position
		void SetPosition(const XMFLOAT3 & position);
		void SetPosition(float x, float y, float z);

		//frustum
		void SetFrustum(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);

		//set moves
		void Walk(float distance);
		void RotateYAxis(float angle);
		void Pitch(float angle);

		void UpdateViewMatrix();

		//set camera space
		void SetCameraSpace(const XMFLOAT3 & position, const XMFLOAT3 & lookAxis, const XMFLOAT3 & upAxis);
		void SetCameraSpace(FXMVECTOR position, FXMVECTOR lookAxis, FXMVECTOR upAxis);
			
};

