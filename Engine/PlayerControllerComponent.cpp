#include "PlayerControllerComponent.h"

#include "InputHandlerToGameObjectMessage.h"

PlayerControllerComponent::PlayerControllerComponent() : IComponent("PlayerControllerComponent")
{
}


PlayerControllerComponent::~PlayerControllerComponent()
{
}

void PlayerControllerComponent::RecieveMessage(IComponentMessage & message)
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

void PlayerControllerComponent::ProcessCommand(sCommand command, float range)
{
	/*
	<Command key="A" name="move_left" ID="3"/>
	<Command key="D" name="move_right" ID="4"/>
	<Command key="S" name="move_down" ID="2"/>
	<Command key="W" name="move_up" ID="1"/>
	*/
	switch (command._ID)
	{
		case 1: // UP
		{
			float f = 0;
			break;
		}
		case 2: // DOWN
		{
			float f = 0;
			break;
		}
		case 3: // LEFT
		{
			float f = 0;
			break;
		}
		case 4: // RIGHT
		{
			float f = 0;
			break;
		}
	}
}
