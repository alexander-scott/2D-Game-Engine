#include "RigidBodyComponent.h"

#include "AddForceMessage.h"

RigidBodyComponent::RigidBodyComponent(float staticF, float dynamicF, float rest, float density)
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
	_density = density;

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
		AddForceMessage& addForceMsg = static_cast<AddForceMessage &> (message);
		ApplyForce(addForceMsg.Direction, addForceMsg.Power);
		break;
	}
}

void RigidBodyComponent::ApplyForce(const Vec2& f, float power)
{
	_force += (f * power);
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

	_isStatic = true;
}

#pragma region Editor Functions

int RigidBodyComponent::GetEditorFieldCount()
{
	return 4;
}

InspectorField* RigidBodyComponent::GetEditorFields()
{
	auto inspectorFields = new InspectorField[GetEditorFieldCount()];

	inspectorFields[0].FieldName = "StaticFriction";
	inspectorFields[0].FieldType = (int)EditorFieldTypes::eFloat;
	char* staticFValue = new char[to_string(GetStaticFriction()).length() + 1];
	strcpy_s(staticFValue, to_string(GetStaticFriction()).length() + 1, to_string(GetStaticFriction()).c_str());
	inspectorFields[0].FieldValue = staticFValue;

	inspectorFields[1].FieldName = "DynamicFriction";
	inspectorFields[1].FieldType = (int)EditorFieldTypes::eFloat;
	char* dynamicFValue = new char[to_string(GetDynamicFriction()).length() + 1];
	strcpy_s(dynamicFValue, to_string(GetDynamicFriction()).length() + 1, to_string(GetDynamicFriction()).c_str());
	inspectorFields[1].FieldValue = dynamicFValue;

	inspectorFields[2].FieldName = "Restitution";
	inspectorFields[2].FieldType = (int)EditorFieldTypes::eFloat;
	char* restValue = new char[to_string(GetRestitution()).length() + 1];
	strcpy_s(restValue, to_string(GetRestitution()).length() + 1, to_string(GetRestitution()).c_str());
	inspectorFields[2].FieldValue = restValue;

	inspectorFields[3].FieldName = "Density";
	inspectorFields[3].FieldType = (int)EditorFieldTypes::eFloat;
	char* densityValue = new char[to_string(GetDensity()).length() + 1];
	strcpy_s(densityValue, to_string(GetDensity()).length() + 1, to_string(GetDensity()).c_str());
	inspectorFields[3].FieldValue = densityValue;

	/*inspectorFields[4].FieldName = "Static";
	inspectorFields[4].FieldType = (int)EditorFieldTypes::eInteger;
	char* staticValue = new char[to_string(IsStatic()).length() + 1];
	strcpy_s(staticValue, to_string(IsStatic()).length() + 1, to_string(IsStatic()).c_str());
	inspectorFields[4].FieldValue = staticValue;

	inspectorFields[5].FieldName = "RotationLocked";
	inspectorFields[5].FieldType = (int)EditorFieldTypes::eInteger;
	char* rotLockedValue = new char[to_string(RotationLocked()).length() + 1];
	strcpy_s(rotLockedValue, to_string(RotationLocked()).length() + 1, to_string(RotationLocked()).c_str());
	inspectorFields[5].FieldValue = rotLockedValue;
*/
	return inspectorFields;
}

void RigidBodyComponent::SetEditorFieldValue(int fieldIndex, const char* value)
{
	switch (fieldIndex)
	{
		case 0:
		{
			SetStaticFriction((float)atof(value));
			break;
		}
		case 1:
		{
			SetDynamicFriction((float)atof(value));
			break;
		}
		case 2:
		{
			SetRestitution((float)atof(value));
			break;
		}
		case 3:
		{
			SetDensity((float)atof(value));
			break;
		}
	}
}

#pragma endregion