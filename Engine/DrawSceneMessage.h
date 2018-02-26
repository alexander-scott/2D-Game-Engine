#pragma once

#include "ISystemMessage.h"

class Scene;

class DrawSceneMessage : public ISystemMessage
{
public:
	DrawSceneMessage(std::shared_ptr<Scene> scene) 
		: ISystemMessage(SystemMessageType::eGraphicsDrawScene) 
	{
		_scene = scene;
	}

	std::shared_ptr<Scene> GetScene() { return _scene; }

private:
	std::shared_ptr<Scene>		_scene;
};