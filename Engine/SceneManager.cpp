#include "SceneManager.h"

#include "BuildSceneMessage.h"
#include "DrawSceneMessage.h"
#include "ISystemToGameObjectMessage.h"

SceneManager::SceneManager(std::shared_ptr<SystemMessageDispatcher> dispatcher)
	: ISystem(SystemType::eSceneManager, dispatcher) 
{ 
}

void SceneManager::InitaliseListeners()
{
	SubscribeToMessageType(SystemMessageType::eBuildSceneMessage);
	SubscribeToMessageType(SystemMessageType::eDrawScene);
	SubscribeToMessageType(SystemMessageType::eUpdateScene);
	SubscribeToMessageType(SystemMessageType::eSendMessageToGameObjects);
}

void SceneManager::RecieveMessage(ISystemMessage & message)
{
	switch (message.Type)
	{
		case SystemMessageType::eBuildSceneMessage:
		{
			BuildSceneMessage & msg = static_cast<BuildSceneMessage&>(message);
			_currentScene = msg.GetScene();
			break;
		}

		case SystemMessageType::eDrawScene: // Recieved from engine
		{
			if (_currentScene == nullptr)
				throw std::exception("CURRENT SCENE NOT INITALISED");

			// Pass a pointer to the current scene to the Graphics system to be drawn
			DrawSceneMessage message(_currentScene);
			SendMessageToDispatcher(message);
			break;
		}

		case SystemMessageType::eUpdateScene: // Recieved from engine
		{
			if (_currentScene == nullptr)
				throw std::exception("CURRENT SCENE NOT INITALISED");

			_currentScene->Update(_frameTimer.Mark());
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