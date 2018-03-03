#pragma once

#include "FrameTimer.h"

#include "Scene.h"

#include "ISystem.h"

struct SceneItem
{
	int GameObjectID;
	unsigned int GameObjectParentID;
	char* GameObjectName;
	int ComponentCount;
};

struct InspectorItem
{
	char* FieldName;
	char* FieldValue;
	int FieldType;
};

class SceneManager : public ISystem
{
public:
	SceneManager(std::shared_ptr<SystemMessageDispatcher> dispatcher);

	void InitaliseListeners() override;

	void RecieveMessage(ISystemMessage& message) override;

	shared_ptr<Scene> GetScene() { return _currentScene; }

private:
	shared_ptr<Scene>		_currentScene;
	FrameTimer				_frameTimer;
	bool					_isPlaying;
};