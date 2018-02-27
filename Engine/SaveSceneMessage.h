#pragma once

#include "ISystemMessage.h"

class Scene;

class SaveSceneMessage : public ISystemMessage
{
public:
	SaveSceneMessage(std::shared_ptr<Scene> scene, std::string filePath) 
		: ISystemMessage(SystemMessageType::eSaveSceneMessage), _scene(scene), _filePath(filePath) { }

	std::shared_ptr<Scene> GetScene() { return _scene; }
	std::string GetFilePath() { return _filePath; }

private:
	std::string					_filePath;
	std::shared_ptr<Scene>		_scene;
};