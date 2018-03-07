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

int* EditorSceneInterface::GetComponentFieldCounts(void* sceneManagerPtr, unsigned long gameObjectID)
{
	auto gameObject = static_cast<SceneManager*>(sceneManagerPtr)->GetScene()->GetGameObject(gameObjectID);
	auto components = gameObject->GetAllComponents();
	int componentCount = (int)components.size();

	int* componentFieldCounts = new int[componentCount];
	for (int i = 0; i < componentCount; i++)
	{
		componentFieldCounts[i] = (int)components[i]->GetEditorFieldCount();
	}

	return componentFieldCounts;
}

InspectorField* EditorSceneInterface::PopulateInspector(void* sceneManagerPtr, unsigned long gameObjectID, int componentIndex)
{
	auto gameObject = static_cast<SceneManager*>(sceneManagerPtr)->GetScene()->GetGameObject(gameObjectID);
	auto components = gameObject->GetAllComponents();
	int componentCount = (int)components.size();

	auto componentFields = components[componentIndex]->GetEditorFields();

	for (int i = 0; i < components[componentIndex]->GetEditorFieldCount(); i++)
	{
		componentFields[i].GameObjectID = (int)gameObjectID;
		componentFields[i].ComponentIndex = componentIndex;
		componentFields[i].FieldIndex = i;
	}

	return componentFields;
}

void EditorSceneInterface::RenameGameObject(void* sceneManagerPtr, unsigned long gameObjectID, const char* name)
{
	static_cast<SceneManager*>(sceneManagerPtr)->GetScene()->GetGameObject(gameObjectID)->SetTag(string(name));
}

SceneItem* EditorSceneInterface::CreateGameObject(void* sceneManagerPtr)
{
	auto scene = static_cast<SceneManager*>(sceneManagerPtr)->GetScene();

	auto gameObject = GameObject::MakeGameObject("New GameObject");
	scene->AddGameObject(gameObject);

	SceneItem* item = new SceneItem;
	item->GameObjectID = gameObject->GetID().Data1; // Set GameObject ID
	item->GameObjectParentID = NULL;

	char* result = new char[gameObject->GetTag().length() + 1];
	strcpy_s(result, gameObject->GetTag().length() + 1, gameObject->GetTag().c_str());
	item->GameObjectName = result; // Set the GameObject's name

	item->ComponentCount = 0;

	return item;
}

void EditorSceneInterface::DeleteGameObject(void * sceneManagerPtr, unsigned long gameObjectID)
{
	static_cast<SceneManager*>(sceneManagerPtr)->GetScene()->DeleteGameObject(gameObjectID);
}

void EditorSceneInterface::ModifyGameObjectComponentField(void* sceneManagerPtr, unsigned long gameObjectID, int componentID, int fieldIndex, const char* value)
{
	auto components = static_cast<SceneManager*>(sceneManagerPtr)->GetScene()->GetGameObject(gameObjectID)->GetAllComponents();
	components[componentID]->SetEditorFieldValue(fieldIndex, value);
}

void EditorSceneInterface::FreeMemory(void * ptr)
{
	delete ptr;
}