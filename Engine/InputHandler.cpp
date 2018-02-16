#include "InputHandler.h"

#include "InputKeyboardMessage.h"
#include "InputMouseMessage.h"

InputHandler::InputHandler(std::shared_ptr<SystemMessageDispatcher> dispatcher)
	:ISystem(SystemType::eInputHandler, dispatcher){ }

void InputHandler::InitaliseListeners()
{
	SubscribeToMessageType(SystemMessageType::eInputKeyboardMessage);
	SubscribeToMessageType(SystemMessageType::eInputMouseMessage);

	MoveUpCommand* move_up = new MoveUpCommand();
	_keyboardCommands['Z'] = move_up;
}

void InputHandler::RecieveMessage(ISystemMessage & message)
{
	if (message.Type == SystemMessageType::eInputKeyboardMessage)
	{
		//TODO: Write code to handle keyboard messages
		InputKeyboardMessage& msg = static_cast<InputKeyboardMessage&>(message);
		if (_keyboardCommands[msg.Key] != nullptr)
		{
			_keyboardCommands[msg.Key]->Execute();
		}
	}
	if (message.Type == SystemMessageType::eInputMouseMessage)
	{
		//TODO: Write code to handle mouse messages
		InputMouseMessage& msg = static_cast<InputMouseMessage&>(message);
	}
}
