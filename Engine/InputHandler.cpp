#include "InputHandler.h"

#include "InputKeyboardMessage.h"
#include "InputMouseMessage.h"
#include "ISystemToGameObjectMessage.h"
#include "InputHandlerToGameObjectMessage.h"

#include "GlobalVariables.h"

#include <fstream>

InputHandler::InputHandler(std::shared_ptr<SystemMessageDispatcher> dispatcher)
	:ISystem(SystemType::eInputHandler, dispatcher)
{ 
	_gamePadP1 = std::make_unique<DirectX::GamePad>();
	_bKeyboardSwapCommands = false;
	_connectedGamePadP1 = false;
}

void InputHandler::InitaliseListeners()
{
	SubscribeToMessageType(SystemMessageType::eInputKeyboardMessage);
	SubscribeToMessageType(SystemMessageType::eInputMouseMessage);
	SubscribeToMessageType(SystemMessageType::eInputUpdateGamePad);

	AddMapToVectorOfCommands();
	LoadMapFromXMLFile(GlobalVariables::Instance().ResourcesFilePath + "//InputMaps//InputMapTest.xml");
	AddMapToVectorOfCommands();
	LoadKeyboardGameMapping();
	LoadGamePadGameMapping();
	SaveMapsInput();
}

void InputHandler::LoadKeyboardGameMapping()
{
	_keyboardCurrentCommandMap = _keyboardListOfCommandMap[0];
	_keyboardCurrentActivatedMap = 0;
}

void InputHandler::LoadGamePadGameMapping()
{
	_gamePadCurrentCommandMap = _gamePadListOfCommandMap[0];
	_gamePadCurrentActivatedMap = 0;
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
							keyMessage,-2.0f);
						SendMessageToDispatcher(ISystemToGameObjectMessage(message));
					}
					else if (msg.MessageType == KeyboardMessageType::eKeyUp)
					{
						InputHandlerToGameObjectMessage message(InputGenericStateMessageType::eKeyReleased,
							keyMessage,-2.0f);
						SendMessageToDispatcher(ISystemToGameObjectMessage(message));
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
			if (_stateGamePadP1.IsConnected() && !_connectedGamePadP1)
			{
				_connectedGamePadP1 = true;
			}
			else if (!(_stateGamePadP1.IsConnected()) && _connectedGamePadP1)
			{
				_connectedGamePadP1 = false;
				//reset inputs in case of a disconnection
				SendGamePadNeutralState();
			}

			if(_connectedGamePadP1) //send updates of gamepad to game components only if it's connected
			{
				_buttonStateTrackerP1.Update(_stateGamePadP1);
				SendGamePadButtonState(_buttonStateTrackerP1, DirectX::GamePad::ButtonStateTracker::PRESSED);
				SendGamePadButtonState(_buttonStateTrackerP1, DirectX::GamePad::ButtonStateTracker::RELEASED);
				SendGamePadAnalogStickState(_stateGamePadP1);
				SendGamePadAnalogTriggerState(_stateGamePadP1);
			}
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
	_gamePadListOfCommandMap.push_back(std::map<std::string, sCommand>());
}

void InputHandler::SendGamePadButtonState(DirectX::GamePad::ButtonStateTracker & buttonStateTracker,
	DirectX::GamePad::ButtonStateTracker::ButtonState buttonStateEnum)
{
	sCommand keyMessage;
	InputGenericStateMessageType buttonStateMessage;
	if (buttonStateEnum == DirectX::GamePad::ButtonStateTracker::PRESSED)
		buttonStateMessage = InputGenericStateMessageType::eKeyPressed;
	else
		buttonStateMessage = InputGenericStateMessageType::eKeyReleased;

	//ABXY buttons
	if (buttonStateTracker.a == buttonStateEnum)
	{
		keyMessage = _gamePadCurrentCommandMap["A"];
		InputHandlerToGameObjectMessage message(buttonStateMessage, keyMessage, -2.0f);
		SendMessageToDispatcher(ISystemToGameObjectMessage(message));
	}
	if (buttonStateTracker.b == buttonStateEnum)
	{
		keyMessage = _gamePadCurrentCommandMap["B"];
		InputHandlerToGameObjectMessage message(buttonStateMessage, keyMessage, -2.0f);
		SendMessageToDispatcher(ISystemToGameObjectMessage(message));
	}
	if (buttonStateTracker.x == buttonStateEnum)
	{
		keyMessage = _gamePadCurrentCommandMap["X"];
		InputHandlerToGameObjectMessage message(buttonStateMessage, keyMessage, -2.0f);
		SendMessageToDispatcher(ISystemToGameObjectMessage(message));
	}
	if (buttonStateTracker.y == buttonStateEnum)
	{
		keyMessage = _gamePadCurrentCommandMap["Y"];
		InputHandlerToGameObjectMessage message(buttonStateMessage, keyMessage, -2.0f);
		SendMessageToDispatcher(ISystemToGameObjectMessage(message));
	}

	//Back and Start buttons
	if (buttonStateTracker.back == buttonStateEnum)
	{
		keyMessage = _gamePadCurrentCommandMap["BACK"];
		InputHandlerToGameObjectMessage message(buttonStateMessage, keyMessage, -2.0f);
		SendMessageToDispatcher(ISystemToGameObjectMessage(message));
	}
	if (buttonStateTracker.start == buttonStateEnum)
	{
		keyMessage = _gamePadCurrentCommandMap["START"];
		InputHandlerToGameObjectMessage message(buttonStateMessage, keyMessage, -2.0f);
		SendMessageToDispatcher(ISystemToGameObjectMessage(message));
	}

	//Left and right stick clicks
	if (buttonStateTracker.leftStick == buttonStateEnum)
	{
		keyMessage = _gamePadCurrentCommandMap["LEFT_STICK"];
		InputHandlerToGameObjectMessage message(buttonStateMessage, keyMessage, -2.0f);
		SendMessageToDispatcher(ISystemToGameObjectMessage(message));
	}
	if (buttonStateTracker.rightStick == buttonStateEnum)
	{
		keyMessage = _gamePadCurrentCommandMap["RIGHT_STICK"];
		InputHandlerToGameObjectMessage message(buttonStateMessage, keyMessage, -2.0f);
		SendMessageToDispatcher(ISystemToGameObjectMessage(message));
	}

	//Left and right bumpers
	if (buttonStateTracker.leftShoulder == buttonStateEnum)
	{
		keyMessage = _gamePadCurrentCommandMap["LEFT_BUMPER"];
		InputHandlerToGameObjectMessage message(buttonStateMessage, keyMessage, -2.0f);
		SendMessageToDispatcher(ISystemToGameObjectMessage(message));
	}
	if (buttonStateTracker.rightShoulder == buttonStateEnum)
	{
		keyMessage = _gamePadCurrentCommandMap["RIGHT_BUMPER"];
		InputHandlerToGameObjectMessage message(buttonStateMessage, keyMessage, -2.0f);
		SendMessageToDispatcher(ISystemToGameObjectMessage(message));
	}

	//DPAD buttons
	if (buttonStateTracker.dpadUp == buttonStateEnum)
	{
		keyMessage = _gamePadCurrentCommandMap["DPAD_UP"];
		InputHandlerToGameObjectMessage message(buttonStateMessage, keyMessage, -2.0f);
		SendMessageToDispatcher(ISystemToGameObjectMessage(message));
	}
	if (buttonStateTracker.dpadDown == buttonStateEnum)
	{
		keyMessage = _gamePadCurrentCommandMap["DPAD_DOWN"];
		InputHandlerToGameObjectMessage message(buttonStateMessage, keyMessage, -2.0f);
		SendMessageToDispatcher(ISystemToGameObjectMessage(message));
	}
	if (buttonStateTracker.dpadLeft == buttonStateEnum)
	{
		keyMessage = _gamePadCurrentCommandMap["DPAD_LEFT"];
		InputHandlerToGameObjectMessage message(buttonStateMessage, keyMessage, -2.0f);
		SendMessageToDispatcher(ISystemToGameObjectMessage(message));
	}
	if (buttonStateTracker.dpadRight == buttonStateEnum)
	{
		keyMessage = _gamePadCurrentCommandMap["DPAD_RIGHT"];
		InputHandlerToGameObjectMessage message(buttonStateMessage, keyMessage, -2.0f);
		SendMessageToDispatcher(ISystemToGameObjectMessage(message));
	}
}

void InputHandler::SendGamePadAnalogStickState(DirectX::GamePad::State & state)
{
	sCommand keyMessage;
	InputGenericStateMessageType stateAxisXMessage,stateAxisYMessage;
	float posX;
	float posY;

	stateAxisXMessage = InputGenericStateMessageType::eAnalogStickAxisXMessage;
	stateAxisYMessage = InputGenericStateMessageType::eAnalogStickAxisYMessage;
	//send left stick state
	posX = state.thumbSticks.leftX;
	posY = state.thumbSticks.leftY;
	keyMessage = _gamePadCurrentCommandMap["LEFT_STICK_ANALOG"];
	InputHandlerToGameObjectMessage messageLX(stateAxisXMessage, keyMessage, posX);
	SendMessageToDispatcher(ISystemToGameObjectMessage(messageLX));
	InputHandlerToGameObjectMessage messageLY(stateAxisYMessage, keyMessage, posY);
	SendMessageToDispatcher(ISystemToGameObjectMessage(messageLY));

	//send right stick state
	posX = state.thumbSticks.rightX;
	posY = state.thumbSticks.rightY;
	keyMessage = _gamePadCurrentCommandMap["RIGHT_STICK_ANALOG"];
	InputHandlerToGameObjectMessage messageRX(stateAxisXMessage, keyMessage, posX);
	SendMessageToDispatcher(ISystemToGameObjectMessage(messageRX));
	InputHandlerToGameObjectMessage messageRY(stateAxisYMessage, keyMessage, posY);
	SendMessageToDispatcher(ISystemToGameObjectMessage(messageRY));
}

void InputHandler::SendGamePadAnalogTriggerState(DirectX::GamePad::State & state)
{
	sCommand keyMessage;
	InputGenericStateMessageType stateMessage;
	stateMessage = InputGenericStateMessageType::eAnalogTriggerMessage;

	float triggerLeftAmount = state.triggers.left;
	keyMessage = _gamePadCurrentCommandMap["LEFT_TRIGGER"];
	InputHandlerToGameObjectMessage messageL(stateMessage, keyMessage, triggerLeftAmount);
	SendMessageToDispatcher(ISystemToGameObjectMessage(messageL));

	float triggerRightAmount = state.triggers.right;
	keyMessage = _gamePadCurrentCommandMap["RIGHT_TRIGGER"];
	InputHandlerToGameObjectMessage messageR(stateMessage, keyMessage, triggerRightAmount);
	SendMessageToDispatcher(ISystemToGameObjectMessage(messageR));
}

void InputHandler::SendGamePadNeutralState()
{
	sCommand keyMessage;
	InputGenericStateMessageType stateAxisXMessage, stateAxisYMessage, stateTriggerMessage;

	stateAxisXMessage = InputGenericStateMessageType::eAnalogStickAxisXMessage;
	stateAxisYMessage = InputGenericStateMessageType::eAnalogStickAxisYMessage;
	stateTriggerMessage = InputGenericStateMessageType::eAnalogTriggerMessage;

	keyMessage = _gamePadCurrentCommandMap["LEFT_STICK_ANALOG"];
	InputHandlerToGameObjectMessage messageLX(stateAxisXMessage, keyMessage, 0.0f);
	SendMessageToDispatcher(ISystemToGameObjectMessage(messageLX));
	InputHandlerToGameObjectMessage messageLY(stateAxisYMessage, keyMessage, 0.0f);
	SendMessageToDispatcher(ISystemToGameObjectMessage(messageLY));

	keyMessage = _gamePadCurrentCommandMap["RIGHT_STICK_ANALOG"];
	InputHandlerToGameObjectMessage messageRX(stateAxisXMessage, keyMessage, 0.0f);
	SendMessageToDispatcher(ISystemToGameObjectMessage(messageRX));
	InputHandlerToGameObjectMessage messageRY(stateAxisYMessage, keyMessage, 0.0f);
	SendMessageToDispatcher(ISystemToGameObjectMessage(messageRY));

	InputHandlerToGameObjectMessage messageL(stateTriggerMessage, keyMessage, 0.0f);
	SendMessageToDispatcher(ISystemToGameObjectMessage(messageL));
	InputHandlerToGameObjectMessage messageR(stateTriggerMessage, keyMessage, 0.0f);
	SendMessageToDispatcher(ISystemToGameObjectMessage(messageR));
}

//TODO Input: Refactor this
void InputHandler::SaveMapsInput()
{
	std::ofstream file(GlobalVariables::Instance().ResourcesFilePath + "//InputMaps//InputMapTestSave.xml");
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

	xml_node<>* peripheral2 = doc.allocate_node(node_element, "Peripheral");
	peripheral2->append_attribute(doc.allocate_attribute("name", "gamepad"));
	root->append_node(peripheral2);
	xml_node<>* map2 = doc.allocate_node(node_element, "Map");
	map2->append_attribute(doc.allocate_attribute("context", "main"));
	peripheral2->append_node(map2);
	

	for (int i = 0; i < _gamePadListOfCommandMap.size(); i++)
	{
		for (auto& it : _gamePadListOfCommandMap[i])
		{
			xml_node<>* command = doc.allocate_node(node_element, "Command");
			const std::string pKey = (it.first);
			command->append_attribute(doc.allocate_attribute("key", doc.allocate_string(pKey.c_str())));
			const sCommand currentCommand = (it.second);
			command->append_attribute(doc.allocate_attribute("name", doc.allocate_string(currentCommand._name.c_str())));
			string stringID = to_string((currentCommand._ID));
			command->append_attribute(doc.allocate_attribute("ID", doc.allocate_string(stringID.c_str())));
			map2->append_node(command);
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
			map<unsigned char, sCommand> entryPointKeyboardVector;
			map<std::string, sCommand> entryPointGamePadVector;
			sCommand dataRetrieved;
			if (peripheralName == "keyboard")
			{
				while (commandNode)
				{
					dataRetrieved._name = commandNode->first_attribute("name")->value();
					dataRetrieved._ID = atoi(commandNode->first_attribute("ID")->value());
					const unsigned char* pKey = (reinterpret_cast<const unsigned char*>(commandNode->first_attribute("key")->value()));
					entryPointKeyboardVector[*pKey] = dataRetrieved;
					commandNode = commandNode->next_sibling("Command");
				}
				_keyboardListOfCommandMap[peripheralCount] = entryPointKeyboardVector;
				entryPointKeyboardVector.clear();
			}
			if (peripheralName == "gamepad")
			{
				bool buttonExists;
				while (commandNode)
				{
					buttonExists = false;
					dataRetrieved._name = commandNode->first_attribute("name")->value();
					dataRetrieved._ID = atoi(commandNode->first_attribute("ID")->value());
					std::string sKey = commandNode->first_attribute("key")->value();
					//check if key provided in the xml file is a correct key
					for each (std::string button in _listOfAvailableGamepadButtons)
					{
						if (sKey == button)
						{
							entryPointGamePadVector[sKey] = dataRetrieved;
							buttonExists = true;
							break;
						}
					}
					//if not, note this in the log
					if (!buttonExists)
						Logger::Instance().LogMessage("A gamepad command has a incorrect button assigned to it."
							, "INPUT_HANDLER", LogSeverity::eWarning);
					commandNode = commandNode->next_sibling("Command");
				}
				_gamePadListOfCommandMap[peripheralCount] = entryPointGamePadVector;
				entryPointGamePadVector.clear();
			}
			peripheralNode = peripheralNode->next_sibling("Peripheral");
		}

	}
	catch (exception& e)
	{
		Logger::Instance().LogMessage(e.what(), "INPUT_HANDLER", LogSeverity::eError);
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
