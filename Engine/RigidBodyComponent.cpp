#include "RigidBodyComponent.h"


RigidBodyComponent::RigidBodyComponent(float staticF, float dynamicF, float rest)
	: IComponent("RigidbodyComponent")
{
	_velocity.Set(0, 0);
	_angularVelocity = 0;
	_torque = 0;
	_force.Set(0, 0);
	_orientationMatrix = 0;
	_staticFriction = staticF;
	_dynamicFriction = dynamicF;
	_restitution = rest;

	_rotationLocked = false;
}

RigidBodyComponent::~RigidBodyComponent()
{
}

void RigidBodyComponent::RecieveMessage(IComponentMessage & message)
{
	switch (message.MessageType)
	{
	case ComponentMessageType::eAddForce:
		/*AddForceMessage& addForceMsg = static_cast<AddForceMessage &> (message);
		ApplyForce(addForceMsg.Force);*/
		break;
	}
}

void RigidBodyComponent::ApplyForce(const Vec2& f)
{
	_force += (f * 1000000);
}

void RigidBodyComponent::ApplyImpulse(const Vec2 & impulse, const Vec2 & contactVector)
{
	_velocity += _inverseMass * impulse;
	_angularVelocity += _inverseInertia * Cross(contactVector, impulse);
}

void RigidBodyComponent::SetStatic()
{
	_intertia = 0.0f;
	_inverseInertia = 0.0f;
	_mass = 0.0f;
	_inverseMass = 0.0f;
}
