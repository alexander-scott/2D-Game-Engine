#pragma once

#include "ISystem.h"
#include "TestCommand.h"
#include "DirectXTK\Inc\GamePad.h"
#include "Logger.h"

class ISystemToGameObjectMessage;

class InputHandler : public ISystem
{
public:
	InputHandler(std::shared_ptr<SystemMessageDispatcher> dispatcher);

	void InitaliseListeners() override;
	void TestKeyboardInitialCommands();
	void LoadKeyboardGameMapping();
	void RecieveMessage(ISystemMessage& message) override;

	void SwapCommands(std::vector<unsigned char>& rebindQueue);

	void SendMessageToScene(ISystemToGameObjectMessage& message);
private:
	std::unique_ptr <DirectX::GamePad> _gamePadP1;
	DirectX::GamePad::State _stateGamePadP1;

	bool _bKeyboardSwapCommands;
	bool _debugSwap = false; //to delete for final release
	std::map <unsigned char, ICommand*> _keyboardCurrentCommandMap;
	std::map <unsigned char, ICommand*> _keyboardGameCommandMap;

	std::vector<unsigned char> _rebindKeyboardQueue;
};

