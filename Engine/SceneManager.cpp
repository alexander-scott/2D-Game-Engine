#include "SceneManager.h"

#include "BuildSceneMessage.h"

#include "RequestSaveSceneMessage.h"
#include "SaveSceneMessage.h"
#include "SceneMessage.h"
#include "UpdateSystemMessage.h"

#include "ISystemToGameObjectMessage.h"

SceneManager::SceneManager(std::shared_ptr<SystemMessageDispatcher> dispatcher)
	: ISystem(SystemType::eSceneManager, dispatcher) 
{ 
	_isPlaying = false;
}

void SceneManager::InitaliseListeners()
{
	SubscribeToMessageType(SystemMessageType::eBuildSceneMessage);
	SubscribeToMessageType(SystemMessageType::eRequestSaveSceneMessage);
	SubscribeToMessageType(SystemMessageType::eDrawScene);
	SubscribeToMessageType(SystemMessageType::eUpdateScene);
	SubscribeToMessageType(SystemMessageType::eSendMessageToGameObjects);
	SubscribeToMessageType(SystemMessageType::ePlayStarted);
	SubscribeToMessageType(SystemMessageType::ePlayStopped);
}

void SceneManager::RecieveMessage(ISystemMessage & message)
{
	switch (message.Type)
	{
		case SystemMessageType::eBuildSceneMessage:
		{
			BuildSceneMessage & msg = static_cast<BuildSceneMessage&>(message);
			_currentScene = nullptr;
			_currentScene = msg.GetScene();
			break;
		}

		case SystemMessageType::eRequestSaveSceneMessage:
		{
			if (_currentScene != nullptr)
			{
				RequestSaveSceneMessage& msg = static_cast<RequestSaveSceneMessage&>(message);
				SaveSceneMessage newMsg(_currentScene, msg.FilePath);
				SendMessageToDispatcher(newMsg);
			}
			break;
		}

		case SystemMessageType::eDrawScene:
		{
			if (_currentScene != nullptr)
			{
				// Pass a pointer to the current scene to the Graphics system to be drawn
				SceneMessage msg(SystemMessageType::eGraphicsDrawScene, _currentScene);
				SendMessageToDispatcher(msg);
			}		
			break;
		}

		case SystemMessageType::eUpdateScene:
		{
			if (_currentScene != nullptr && _isPlaying) // Only update scene if were are in play mode
			{
				UpdateSystemMessage& msg = static_cast<UpdateSystemMessage&>(message);
				_currentScene->Update(msg.DeltaTime);
			}
			break;
		}

		case SystemMessageType::ePlayStarted:
		{
			_isPlaying = true;

			SceneMessage msg(SystemMessageType::eSceneSelectedToPlay, _currentScene);
			SendMessageToDispatcher(msg);

			_currentScene->Start();
			break;
		}

		case SystemMessageType::ePlayStopped:
		{
			_isPlaying = false;
			break;
		}

		case SystemMessageType::eSendMessageToGameObjects:
		{
			if (_currentScene == nullptr)
				throw std::exception("CURRENT SCENE NOT INITALISED");

			ISystemToGameObjectMessage & msg = static_cast<ISystemToGameObjectMessage&>(message);
			_currentScene->SendMessageToGameObjects(msg.Message);
			break;
		}
	}
}