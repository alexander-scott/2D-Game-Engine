#pragma once

#include "Scene.h"

#include "ISystem.h"

#include "rapidxml.hpp"

using namespace rapidxml;

class SceneSaver : public ISystem
{
public:
	SceneSaver(std::shared_ptr<SystemMessageDispatcher> dispatcher);

	void InitaliseListeners() override;
	void RecieveMessage(ISystemMessage& message) override;

private:
	void BuildXMLFile(shared_ptr<Scene> scene);
	void SaveScene(string filePath);
};

