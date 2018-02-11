#pragma once

#include "IScene.h"

#include "ISystem.h"
#include "SystemMessageDispatcher.h"

#include "rapidjson\document.h"
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"

class SceneBuilder : public ISystem
{
public:
	SceneBuilder();

	void RecieveMessage(ISystemMessage& message) override;

private:
	shared_ptr<IScene> BuildScene();
};