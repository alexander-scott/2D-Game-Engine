#include "AlexControllerComponent.h"

#include "InputHandlerToGameObjectMessage.h"
#include "AddForceMessage.h"

AlexControllerComponent::AlexControllerComponent() : IComponent("AlexControllerComponent")
{
}


AlexControllerComponent::~AlexControllerComponent()
{
}

void AlexControllerComponent::RecieveMessage(IComponentMessage & message)
{
	switch (message.MessageType)
	{
		case ComponentMessageType::eInputHandlerToGameObjectMessage:
		{
			InputHandlerToGameObjectMessage& msg = static_cast<InputHandlerToGameObjectMessage&>(message);
			ProcessCommand(msg.Command, msg.Range);
			break;
		}
	}
}

void AlexControllerComponent::ProcessCommand(sCommand command, float range)
{
	/*
	<Command key="A" name="move_left" ID="3"/>
	<Command key="D" name="move_right" ID="4"/>
	<Command key="S" name="move_down" ID="2"/>
	<Command key="W" name="move_up" ID="1"/>
	*/

	Vec2 force = Vec2(0.0f, 0.0f);

	switch (command._ID)
	{
		case 1: // UP
		{
			break;
		}
		case 2: // DOWN
		{
			break;
		}
		case 3: // LEFT
		{
			force.x -= 1;
			break;
		}
		case 4: // RIGHT
		{
			force.x += 1;
			break;
		}
	}

	if (force.x != 0 || force.y != 0)
	{
		AddForceMessage addForceMsg(force, 100000000);
		_rigidbody->RecieveMessage(addForceMsg);
	}
}
