#include "InputHandler.h"

#include "InputKeyboardMessage.h"
#include "InputMouseMessage.h"
#include "ISystemToGameObjectMessage.h"

#include <fstream>

InputHandler::InputHandler(std::shared_ptr<SystemMessageDispatcher> dispatcher)
	:ISystem(SystemType::eInputHandler, dispatcher)
{ 
	_gamePadP1 = std::make_unique<DirectX::GamePad>();
}

void InputHandler::InitaliseListeners()
{
	SubscribeToMessageType(SystemMessageType::eInputKeyboardMessage);
	SubscribeToMessageType(SystemMessageType::eInputMouseMessage);
	SubscribeToMessageType(SystemMessageType::eInputUpdateGamePad);

	TestKeyboardInitialCommands();
	LoadKeyboardGameMapping();
}

void InputHandler::TestKeyboardInitialCommands() //to remove after I have a function to load commands list from a file at initialization
{
	MoveUpCommand* move_up = new MoveUpCommand();
	MoveLeftCommand* move_left = new MoveLeftCommand();
	MoveRightCommand* move_right = new MoveRightCommand();
	MoveDownCommand* move_down = new MoveDownCommand();
	RebindSwapCommand* swap = new RebindSwapCommand();

	_keyboardGameCommandMap['W'] = move_up;
	_keyboardGameCommandMap['A'] = move_left;
	_keyboardGameCommandMap['S'] = move_down;
	_keyboardGameCommandMap['D'] = move_right;
	_keyboardGameCommandMap[' '] = swap;//spacebar to swap commands

	_bKeyboardSwapCommands = false;

	SaveMapInput();
}

void InputHandler::LoadKeyboardGameMapping()
{
	_keyboardCurrentCommandMap = _keyboardGameCommandMap;
}

void InputHandler::RecieveMessage(ISystemMessage & message)
{
	switch (message.Type)
	{
		case SystemMessageType::eInputKeyboardMessage:
		{
			//TODO Input: Write code to handle keyboard messages
			InputKeyboardMessage& msg = static_cast<InputKeyboardMessage&>(message);
			if (_keyboardCurrentCommandMap[msg.Key] != nullptr)
			{
				if (_bKeyboardSwapCommands && msg.MessageType == KeyboardMessageType::eKeyDown)
				{
					//get keys to swap.
					_rebindKeyboardQueue.push_back(msg.Key);
					if (_rebindKeyboardQueue.size() == 1)
					{
						//send a message on screen to tell the user to press the second key
					}
					if (_rebindKeyboardQueue.size() == 2)
					{
						SwapCommands(_rebindKeyboardQueue);
					}
				}	
				//suppress this when communication with game logic is implemented
				else if (msg.Key == ' ' && msg.MessageType == KeyboardMessageType::eKeyDown && (_debugSwap))
				{
					_bKeyboardSwapCommands = true;
					Logger::Instance().LogMessage("Keyboard Swap Commands activated.", LogSeverity::eInfo);
				}
				else //execute regular command binded to key
				{
					SendMessageToScene(_keyboardCurrentCommandMap[msg.Key]->Execute());
				}
			}
			break;
		}
		case SystemMessageType::eInputMouseMessage:
		{
			//TODO Input: Write code to handle mouse messages
			InputMouseMessage& msg = static_cast<InputMouseMessage&>(message);
			break;
		}
		case SystemMessageType::eInputUpdateGamePad:
		{
			_stateGamePadP1 = _gamePadP1->GetState(0);
			break;
		}
	}
}

void InputHandler::SwapCommands(std::vector<unsigned char>& rebindQueue)
{
	ICommand * tempCommand = _keyboardGameCommandMap[rebindQueue[0]];
	_keyboardGameCommandMap[rebindQueue[0]] = _keyboardGameCommandMap[rebindQueue[1]];
	_keyboardGameCommandMap[rebindQueue[1]] = tempCommand;

	std::string log = "The following buttons have been swapped: ";
	log += rebindQueue[0];
	log += " and ";
	log += rebindQueue[1];

	LoadKeyboardGameMapping();
	Logger::Instance().LogMessage(log, LogSeverity::eInfo);
	_bKeyboardSwapCommands = false;
	rebindQueue.clear();
}

void InputHandler::SaveMapInput()
{
	std::ofstream file("InputMap.xml");
	xml_document<> doc;
	xml_node<>* decl = doc.allocate_node(node_declaration);
	doc.append_node(decl);

	xml_node<>* root = doc.allocate_node(node_element, "PlayerInputMap");
	root->append_attribute(doc.allocate_attribute("number", "1"));
	doc.append_node(root);

	xml_node<>* peripheral = doc.allocate_node(node_element, "Peripheral");
	peripheral->append_attribute(doc.allocate_attribute("name", "keyboard"));
	root->append_node(peripheral);
	xml_node<>* map = doc.allocate_node(node_element, "Map");
	map->append_attribute(doc.allocate_attribute("context", "main"));
	peripheral->append_node(map);

	for (auto& it : _keyboardGameCommandMap)
	{
		xml_node<>* command = doc.allocate_node(node_element, "Command");
		const unsigned char * pKey = &(it.first);
		const char* pCharKey = (reinterpret_cast<const char*>(pKey));
		//read only the first char of pCharKey, because useless characters after
		command->append_attribute(doc.allocate_attribute("bind", pCharKey,0,1));
		command->append_attribute(doc.allocate_attribute("name", doc.allocate_string(it.second->GetName().c_str())));
		map->append_node(command);
	}

	file << doc;
	file.close();
	doc.clear();
}

// ISystemToGameObjectMessage must be initalised with an instance of IComponentMessage.
// IComponentMessage has a ComponentMessageType that you must set (such as eMoveForward, eMoveBackward)
// which specific GameObject components can listen for. The GameObject component must also 
// inherit IMessageableComponent.
void InputHandler::SendMessageToScene(ISystemToGameObjectMessage& message)
{
	SendMessageToDispatcher(message);
}
