#pragma once

#include "ISystem.h"
#include "TestCommand.h"
#include "DirectXTK\Inc\GamePad.h"

class InputHandler : public ISystem
{
public:
	InputHandler(std::shared_ptr<SystemMessageDispatcher> dispatcher);

	void InitaliseListeners() override;
	void RecieveMessage(ISystemMessage& message) override;
private:
	std::unique_ptr <DirectX::GamePad> _gamePadP1;
	DirectX::GamePad::State _stateGamePadP1;

	std::map <unsigned char, ICommand*> _keyboardCommands;
};

