#pragma once

#include "ISystem.h"
#include "TestCommand.h"
#include "DirectXTK\Inc\GamePad.h"
#include "Logger.h"
#include "rapidxml_print.hpp"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

class ISystemToGameObjectMessage;

struct sCommand
{
	std::string _name;
	int _ID;
};

class InputHandler : public ISystem
{
public:
	InputHandler(std::shared_ptr<SystemMessageDispatcher> dispatcher);

	void InitaliseListeners() override;
	void TestKeyboardInitialCommands();
	void LoadKeyboardGameMapping();
	void RecieveMessage(ISystemMessage& message) override;

	void SwapCommands(std::vector<unsigned char>& rebindQueue);

	void AddMapToVectorOfCommands(/*may need to create message with number of players and which peripheral*/);
	void SaveMapInput();
	void LoadMapFromXMLFile(std::string fileName);

	void SendMessageToScene(ISystemToGameObjectMessage& message);
private:
	std::unique_ptr <DirectX::GamePad> _gamePadP1;
	DirectX::GamePad::State _stateGamePadP1;

	bool _bKeyboardSwapCommands;
	bool _debugSwap = true; //to delete for final release
	//std::map <unsigned char, ICommand*> _keyboardCurrentCommandMap;
	//std::map <unsigned char, ICommand*> _keyboardGameCommandMap;
	map <unsigned char, sCommand> _keyboardCurrentCommandMap;
	vector< std::map <unsigned char, sCommand> > _keyboardListOfCommandMap;
	int _keyboardCurrentActivatedMap; //holds which map in the _keyboardListOfCommandMap vector is active

	vector<unsigned char> _rebindKeyboardQueue;
};

