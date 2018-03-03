#pragma once

#include "Scene.h"

#include "ISystem.h"

#include "rapidxml_print.hpp"
#include "rapidxml.hpp"

using namespace rapidxml;

class SceneSaver : public ISystem
{
public:
	SceneSaver(std::shared_ptr<SystemMessageDispatcher> dispatcher);

	void InitaliseListeners() override;
	void RecieveMessage(ISystemMessage& message) override;

private:
	void SaveScene(shared_ptr<Scene> scene, string filePath);
	std::string GUIDToString(GUID *guid);
};

