#pragma once

#include "IMessage.h"

#include "IScene.h"

class BuildSceneMessage : public IMessage
{
public:
	BuildSceneMessage(shared_ptr<IScene> scene) : IMessage(MessageType::eBuildSceneMessage), _scene(scene) { }

	shared_ptr<IScene> GetScene() { return _scene; }

private:
	shared_ptr<IScene>		_scene;
};