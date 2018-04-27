#include "PCarComponent.h"

#include "InputHandlerToGameObjectMessage.h"
#include "AddForceMessage.h"
#include "SetVelocityMessage.h"
#include "CollisionMessage.h"



PCarComponent::PCarComponent() : IComponent("PCarComponent")
{
	_leftPressed = false;
	_rightPressed = false;
	_throttlePressed = false;
	_brakePressed = false;
	_leftStickAnalog = 0;
}


PCarComponent::~PCarComponent()
{
}

void PCarComponent::Update(float deltaTime)
{
	float standardForce = 1.0f;
	float standardRotation = 0.01f;
	float power = 0.0f;
	Vec2 velocity = Vec2(0.0f, 0.0f);

	//analog controls have priority to digital controls (buttons) if both are operated at the same time

	if (_leftStickAnalog < 0)
		_transform->SetWorldRotation( (_transform->GetWorldRotation() + (_leftStickAnalog * standardRotation) ));
	else if (_leftPressed)
		_transform->SetWorldRotation((_transform->GetWorldRotation() - standardRotation));

	if (_leftStickAnalog > 0)
		_transform->SetWorldRotation( (_transform->GetWorldRotation() + (_leftStickAnalog * standardRotation) ));
	else if (_rightPressed)
		_transform->SetWorldRotation((_transform->GetWorldRotation() + standardRotation));

	if (_throttleAnalog > 0)
		power = _throttleAnalog * standardForce;
	else if (_throttlePressed)
		power = standardForce;

	if (_brakePressed)
		power = 0;

	SetVelocityMessage velocityMessage(velocity);

	velocity.x += cos(_transform->GetWorldRotation()) * power;
	velocity.y += sin(_transform->GetWorldRotation()) * power;

	_transform->SetWorldPosition(Vec2(_transform->GetWorldPosition().x + velocity.x, _transform->GetWorldPosition().y + velocity.y));

}

void PCarComponent::RecieveMessage(IComponentMessage & message)
{
	switch (message.MessageType)
	{
		case ComponentMessageType::eInputHandlerToGameObjectMessage:
		{
			InputHandlerToGameObjectMessage& msg = static_cast<InputHandlerToGameObjectMessage&>(message);
			if (msg.MessageType == eAnalogTriggerMessage)
			{
				ProcessCommandTrigger(msg.MessageType, msg.Command, msg.Range);
			}
			else if (msg.MessageType == eAnalogStickAxisXMessage || msg.MessageType == eAnalogStickAxisYMessage)
			{
				ProcessCommandStick(msg.MessageType, msg.Command, msg.Range);
			}
			else
			{
				ProcessCommandButton(msg.MessageType, msg.Command, msg.Range);
			}
			break;
		}
	}
}

void PCarComponent::ProcessCommandTrigger(InputGenericStateMessageType type, sCommand command, float range)
{
	switch (command._ID)
	{
	case 6: // THROTTLE
	{
		_throttleAnalog = range;
		break;
	}
	case 7: // BRAKE
	{
		_brakeAnalog = range;
		break;
	}
	default:
		_throttleAnalog = 0.0f;
		_brakeAnalog = 0.0f;
		break;
	}
}

void PCarComponent::ProcessCommandStick(InputGenericStateMessageType type, sCommand command, float range)
{
	switch (command._ID)
	{
	case 3: // LEFT
	{
		if(type == eAnalogStickAxisXMessage)
			_leftStickAnalog = range;
		break;
	}
	case 4: // RIGHT
	{
		if (type == eAnalogStickAxisXMessage)
			_leftStickAnalog = range;
		break;
	}
	}
}

void PCarComponent::ProcessCommandButton(InputGenericStateMessageType type, sCommand command, float range)
{
	bool setValue;

	if (type == InputGenericStateMessageType::eKeyPressed)
	{
		setValue = true;
	}
	else
	{
		setValue = false;
	}

	switch (command._ID)
	{
		case 3: // LEFT
		{
			_leftPressed = setValue;
			break;
		}
		case 4: // RIGHT
		{
			_rightPressed = setValue;
			break;
		}
		case 6: // THROTTLE
		{
			_throttlePressed = setValue;
			break;
		}
		case 7: // BRAKE
		{
			_brakePressed = setValue;
			break;
		}
	}
}
