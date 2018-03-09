#pragma once

#include "IComponent.h"
#include "IMessageableComponent.h"

class RigidBodyComponent : public IComponent, public IMessageableComponent
{
public:
	RigidBodyComponent(float staticF, float dynamicF, float rest);
	~RigidBodyComponent();

	virtual void RecieveMessage(IComponentMessage& message) override;

	void ApplyForce(const Vec2& f);
	void ApplyImpulse(const Vec2& impulse, const Vec2& contactVector);

	void SetStatic();
	void LockRotation() { _rotationLocked = true; }

#pragma region Getters and Setters

	Mat2 GetOrientationMatrix() { return _orientationMatrix; }
	void SetOrientationMatrix(Mat2 mat) { _orientationMatrix = mat; }

	Vec2 GetVelocity() { return _velocity; }
	void SetVelocity(Vec2 vel) { _velocity = vel; }

	float GetAngularVelocity() { return _angularVelocity; }
	void SetAngularVelocity(float vel) { _angularVelocity = vel; }

	float GetTorque() { return _torque; }
	void SetTorque(float torq) { _torque = torq; }

	Vec2 GetForce() { return _force; }
	void SetForce(Vec2 forc) { _force = forc; }

	float GetIntertia() { return _intertia; }
	void SetIntertia(float intert) { _intertia = intert; }

	float GetInverseIntertia() { return _inverseInertia; }
	void SetInverseIntertia(float intert) { _inverseInertia = intert; }

	float GetMass() { return _mass; }
	void SetMass(float m) { _mass = m; }

	float GetInverseMass() { return _inverseMass; }
	void SetInverseMass(float im) { _inverseMass = im; }

	float GetStaticFriction() { return _staticFriction; }
	void SetStaticFriction(float frict) { _staticFriction = frict; }

	float GetDynamicFriction() { return _dynamicFriction; }
	void SetDynamicFriction(float frict) { _dynamicFriction = frict; }

	float GetRestitution() { return _restitution; }
	void SetRestitution(float rest) { _restitution = rest; }

	bool RotationLocked() {	return _rotationLocked;	}

#pragma endregion

private:
	Vec2				_velocity;

	float				_angularVelocity;
	float				_torque;

	Vec2				_force;

	Mat2				_orientationMatrix;

	float				_intertia;  // moment of inertia
	float				_inverseInertia; // inverse inertia
	float				_mass;  // _mass
	float				_inverseMass; // inverse masee

	float				_staticFriction;
	float				_dynamicFriction;
	float				_restitution;

	bool				_rotationLocked;
};

