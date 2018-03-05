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

// The InspectorField will display the field name and field value
// TODO: Pass in field type too.
struct InspectorField
{
	char* FieldName;
	char* FieldValue;
	int GameObjectID;
	int ComponentIndex;
	int FieldIndex;
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