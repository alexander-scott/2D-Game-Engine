#pragma once

#include "IScene.h"

#include "ISystem.h"
#include "SystemMessageDispatcher.h"

#include "ComponentBuilder.h"

#include "rapidxml.hpp"
#include <fstream>

using namespace rapidxml;

class SceneBuilder : public ISystem
{
public:
	SceneBuilder(); 

	void InitaliseListeners() override;
	void RecieveMessage(ISystemMessage& message) override;

private:
	shared_ptr<IScene> BuildScene(string filePath);
};