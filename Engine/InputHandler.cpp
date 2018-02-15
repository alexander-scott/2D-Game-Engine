#include "InputHandler.h"

InputHandler::InputHandler(std::shared_ptr<SystemMessageDispatcher> dispatcher)
	:ISystem(SystemType::eInputHandler, dispatcher){ }

void InputHandler::InitaliseListeners()
{
	SubscribeToMessageType(SystemMessageType::eInputKeyboardMessage);
	SubscribeToMessageType(SystemMessageType::eInputMouseMessage);
}

void InputHandler::RecieveMessage(ISystemMessage & message)
{
	if (message.Type == SystemMessageType::eInputKeyboardMessage)
	{
		//TODO: Write code to handle keyboard messages
	}
	if (message.Type == SystemMessageType::eInputMouseMessage)
	{
		//TODO: Write code to handle mouse messages
	}
}
