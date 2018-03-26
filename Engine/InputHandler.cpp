#include "InputHandler.h"

#include "InputKeyboardMessage.h"
#include "InputMouseMessage.h"
#include "ISystemToGameObjectMessage.h"
#include "InputHandlerToGameObjectMessage.h"

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

	AddMapToVectorOfCommands();
	LoadMapFromXMLFile("InputMapTest2.xml");
	AddMapToVectorOfCommands();
	LoadKeyboardGameMapping();
	SaveMapInput();
}
/*
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
*/
void InputHandler::LoadKeyboardGameMapping()
{
	_keyboardCurrentCommandMap = _keyboardListOfCommandMap[0];
	_keyboardCurrentActivatedMap = 0;
}

void InputHandler::RecieveMessage(ISystemMessage & message)
{
	switch (message.Type)
	{
		case SystemMessageType::eInputKeyboardMessage:
		{
			//TODO Input: Write code to handle keyboard messages
			InputKeyboardMessage& msg = static_cast<InputKeyboardMessage&>(message);
			if (_keyboardCurrentCommandMap[msg.Key]._name != "")
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
					sCommand keyMessage = _keyboardCurrentCommandMap[msg.Key];
					if (msg.MessageType == KeyboardMessageType::eKeyDown)
					{
						InputHandlerToGameObjectMessage message(InputGenericStateMessageType::eKeyPressed, 
							keyMessage,-1.0f);
						SendMessageToDispatcher(message);
					}
					else if (msg.MessageType == KeyboardMessageType::eKeyUp)
					{
						InputHandlerToGameObjectMessage message(InputGenericStateMessageType::eKeyReleased,
							keyMessage,-1.0f);
						SendMessageToDispatcher(message);
					}
				}
			}
			break;
		}
		case SystemMessageType::eInputMouseMessage:
		{
			InputMouseMessage& msg = static_cast<InputMouseMessage&>(message);
			break;
		}
		case SystemMessageType::eInputUpdateGamePad:
		{
			_stateGamePadP1 = _gamePadP1->GetState(0);
			break;
		}
		//case add a map context (mode) to vector just pushback

		//case change context, inputhandler will recieve a message from game logic to change to a defined id.
		//Inputhandler doesn't need to know which context correspond to which id
	}
}


void InputHandler::SwapCommands(std::vector<unsigned char>& rebindQueue)
{
	sCommand tempCommand = _keyboardListOfCommandMap[_keyboardCurrentActivatedMap][rebindQueue[0]];
	_keyboardListOfCommandMap[_keyboardCurrentActivatedMap][rebindQueue[0]] 
		= _keyboardListOfCommandMap[_keyboardCurrentActivatedMap][rebindQueue[1]];
	_keyboardListOfCommandMap[_keyboardCurrentActivatedMap][rebindQueue[1]] = tempCommand;

	std::string log = "The following buttons have been swapped: ";
	log += rebindQueue[0];
	log += " and ";
	log += rebindQueue[1];

	LoadKeyboardGameMapping();
	Logger::Instance().LogMessage(log, LogSeverity::eInfo);
	_bKeyboardSwapCommands = false;
	rebindQueue.clear();
}

void InputHandler::AddMapToVectorOfCommands()
{
	//test purposes code, not final
	_keyboardListOfCommandMap.push_back(std::map<unsigned char, sCommand>());
}

void InputHandler::SaveMapInput()
{
	std::ofstream file("InputMapTestSave.xml");
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

	for (int i = 0; i < _keyboardListOfCommandMap.size(); i++)
	{
		for (auto& it : _keyboardListOfCommandMap[i])
		{
			xml_node<>* command = doc.allocate_node(node_element, "Command");
			const unsigned char * pKey = &(it.first);
			const char* pCharKey = (reinterpret_cast<const char*>(pKey));
			//read only the first char of pCharKey, because useless characters after
			command->append_attribute(doc.allocate_attribute("key", pCharKey, 0, 1));
			const sCommand currentCommand = (it.second);
			command->append_attribute(doc.allocate_attribute("name", doc.allocate_string(currentCommand._name.c_str())));
			string stringID = to_string((currentCommand._ID));
			command->append_attribute(doc.allocate_attribute("ID", doc.allocate_string(stringID.c_str())));
			map->append_node(command);
		}
	}

	file << doc;
	file.close();
	doc.clear();
}

void InputHandler::LoadMapFromXMLFile(std::string fileName)//not final, only works for one player and a keyboard
{
	ifstream inFile(fileName);

	if (!inFile)
	{
		Logger::Instance().LogMessage("Could not load XML file!", "INPUT_HANDLER", LogSeverity::eError);
		throw std::exception("Could not load XML file!");
	}

	//Dump contents of file into a string
	string xmlContents;

	//Blocked out of preference
	{
		string line;
		while (getline(inFile, line))
			xmlContents += line;
	}

	//Convert string to rapidxml readable char*
	vector<char> mXmlData = vector<char>(xmlContents.begin(), xmlContents.end());
	mXmlData.push_back('\0');

	//Create a parsed document with &xmlData[0] which is the char*
	xml_document<> doc;
	doc.parse<parse_no_data_nodes>(&mXmlData[0]);

	//Get the root node
	xml_node<>* root = doc.first_node();
	try
	{
		xml_node<>* peripheralNode = root->first_node("Peripheral");
		int peripheralCount = 0;
		while (peripheralNode)
		{
			string peripheralName = peripheralNode->first_attribute("name")->value();
			xml_node<>* mapNode = peripheralNode->first_node("Map");
			xml_node<>* commandNode = mapNode->first_node("Command");
			if (peripheralName == "keyboard")
			{
				map<unsigned char, sCommand>& entryPointVector = _keyboardListOfCommandMap[peripheralCount];
				sCommand dataRetrieved;
				while (commandNode)
				{
					dataRetrieved._name = commandNode->first_attribute("name")->value();
					dataRetrieved._ID = atoi(commandNode->first_attribute("ID")->value());
					const unsigned char* pKey = (reinterpret_cast<const unsigned char*>(commandNode->first_attribute("key")->value()));
					entryPointVector[*pKey] = dataRetrieved;
					commandNode = commandNode->next_sibling("Command");
				}
			}
			peripheralNode = peripheralNode->next_sibling("Peripheral");
		}
		
	}
	catch (exception& e)
	{
		Logger::Instance().LogMessage(e.what(),"INPUT_HANDLER", LogSeverity::eError);
	}
}

// ISystemToGameObjectMessage must be initalised with an instance of IComponentMessage.
// IComponentMessage has a ComponentMessageType that you must set (such as eMoveForward, eMoveBackward)
// which specific GameObject components can listen for. The GameObject component must also 
// inherit IMessageableComponent.
void InputHandler::SendMessageToScene(ISystemToGameObjectMessage& message)
{
	SendMessageToDispatcher(message);
}
