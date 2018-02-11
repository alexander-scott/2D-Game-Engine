#pragma once

#include "FrameTimer.h"

#include "IScene.h"

#include "ISystem.h"
#include "BuildSceneMessage.h"

class SceneManager : public ISystem
{
public:
	SceneManager() : ISystem(SystemType::eSceneManager) 
	{ 
		SystemMessageDispatcher::Instance().AddListener(this, SystemMessageType::eBuildSceneMessage);
		SystemMessageDispatcher::Instance().AddListener(this, SystemMessageType::eDrawScene);
		SystemMessageDispatcher::Instance().AddListener(this, SystemMessageType::eUpdateScene);
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

			case SystemMessageType::eDrawScene:
			{
				_currentScene->Draw();
				break;
			}

			case SystemMessageType::eUpdateScene:
			{
				_currentScene->Update(_frameTimer.Mark());
				break;
			}
		}
	}

private:
	shared_ptr<IScene>		_currentScene;
	FrameTimer				_frameTimer;
};