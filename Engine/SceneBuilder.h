#pragma once

#include "IScene.h"

#include "ISystem.h"

#include "rapidxml.hpp"

using namespace rapidxml;

class SceneBuilder : public ISystem
{
public:
	SceneBuilder(); 

	void InitaliseListeners() override;
	void RecieveMessage(ISystemMessage& message) override;

protected:
	shared_ptr<IScene> BuildScene(string filePath);
};