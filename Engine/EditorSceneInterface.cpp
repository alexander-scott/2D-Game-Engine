#include "EditorSceneInterface.h"

int EditorSceneInterface::GetGameObjectCount(void* sceneManagerPtr)
{
	SceneManager* editor = static_cast<SceneManager*>(sceneManagerPtr);
	auto scene = editor->GetScene();
	if (scene != nullptr)
		return scene->GetNumberOfGameObjects();
	else
		return 0;
}

SceneItem* EditorSceneInterface::PopulateHierarchyItems(void* sceneManagerPtr, int itemCount)
{
	auto scene = static_cast<SceneManager*>(sceneManagerPtr)->GetScene();

	SceneItem* items = new SceneItem[itemCount];
	for (int i = 0; i < itemCount; i++)
	{
		auto gameObj = scene->GetGameObject(i);

		items[i].GameObjectID = gameObj->GetID().Data1; // Set GameObject ID

		auto parentGO = gameObj->GetParent();
		if (parentGO == nullptr) // If the GameObject doesn't have a parent set ID to NULL
			items[i].GameObjectParentID = NULL;
		else // If the GameObject does have a parent set the parent ID to the parent GameObject's ID
			items[i].GameObjectParentID = parentGO->GetID().Data1;

		char* result = new char[gameObj->GetTag().length() + 1];
		strcpy_s(result, gameObj->GetTag().length() + 1, gameObj->GetTag().c_str());
		items[i].GameObjectName = result; // Set the GameObject's name

		items[i].ComponentCount = (int)gameObj->GetAllComponents().size();
	}

	return items;
}

InspectorItem* EditorSceneInterface::PopulateInspector(void* sceneManagerPtr, unsigned long gameObjectID)
{
	auto gameObject = static_cast<SceneManager*>(sceneManagerPtr)->GetScene()->GetGameObject(gameObjectID);
	auto components = gameObject->GetAllComponents();

	InspectorItem* items = new InspectorItem[components.size()];
	for (int i = 0; i < components.size(); i++)
	{

	}

	return nullptr; //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
}

void EditorSceneInterface::FreeMemory(void * ptr)
{
	delete ptr;
}