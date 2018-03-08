#pragma once

#include "ISystem.h"
#include "TestCommand.h"
#include "DirectXTK\Inc\GamePad.h"

class ISystemToGameObjectMessage;

class InputHandler : public ISystem
{
public:
	InputHandler(std::shared_ptr<SystemMessageDispatcher> dispatcher);

	void InitaliseListeners() override;
	void TestKeyboardInitialCommands();
	void LoadKeyboardGameMapping();
	void RecieveMessage(ISystemMessage& message) override;

	void SendMessageToScene(ISystemToGameObjectMessage& message);
private:
	std::unique_ptr <DirectX::GamePad> _gamePadP1;
	DirectX::GamePad::State _stateGamePadP1;

	std::map <unsigned char, ICommand*> _keyboardCurrentCommandMap;
	std::map <unsigned char, ICommand*> _keyboardGameCommandMap;
};

