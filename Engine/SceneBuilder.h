#pragma once

#include "IScene.h"

#include "ISystem.h"
#include "SystemMessageDispatcher.h"

#include "rapidxml.hpp"
#include <fstream>

using namespace rapidxml;

class SceneBuilder : public ISystem
{
public:
	SceneBuilder(); 

	void RecieveMessage(ISystemMessage& message) override;

private:
	shared_ptr<IScene> BuildTestScene(string filePath);
	shared_ptr<IScene> BuildScene(string filePath);
};