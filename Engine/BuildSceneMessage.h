#pragma once

#include "ISystemMessage.h"

class IScene;

class BuildSceneMessage : public ISystemMessage
{
public:
	BuildSceneMessage(shared_ptr<IScene> scene) : ISystemMessage(SystemMessageType::eBuildSceneMessage), _scene(scene) { }

	shared_ptr<IScene> GetScene() { return _scene; }

private:
	shared_ptr<IScene>		_scene;
};