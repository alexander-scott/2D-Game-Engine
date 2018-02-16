#pragma once

#include "ISystem.h"
#include "TestCommand.h"

class InputHandler : public ISystem
{
public:
	InputHandler(std::shared_ptr<SystemMessageDispatcher> dispatcher);

	void InitaliseListeners() override;
	void RecieveMessage(ISystemMessage& message) override;
private:
	std::map <unsigned char, ICommand*> _keyboardCommands;
};

