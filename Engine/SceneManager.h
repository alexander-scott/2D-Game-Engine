#pragma once

#include "FrameTimer.h"

#include "IScene.h"

#include "ISystem.h"
#include "BuildSceneMessage.h"
#include "DrawSceneMessage.h"

class SceneManager : public ISystem
{
public:
	SceneManager(std::shared_ptr<SystemMessageDispatcher> dispatcher) 
		: ISystem(SystemType::eSceneManager, dispatcher) { }

	void InitaliseListeners() override
	{
		SubscribeToMessageType(SystemMessageType::eBuildSceneMessage);
		SubscribeToMessageType(SystemMessageType::eDrawScene);
		SubscribeToMessageType(SystemMessageType::eUpdateScene);
	}

	void RecieveMessage(ISystemMessage& message) override
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

				DrawSceneMessage message; // Initalise the draw scene message
				_currentScene->Draw(message); // Populate it from the scene
				SendMessageToDispatcher(message); // Send it to the Graphics system
				break;
			}

			case SystemMessageType::eUpdateScene: // Recieved from engine
			{
				if (_currentScene == nullptr)
					throw std::exception("CURRENT SCENE NOT INITALISED");

				_currentScene->Update(_frameTimer.Mark());
				break;
			}
		}
	}

private:
	shared_ptr<IScene>		_currentScene;
	FrameTimer				_frameTimer;
};