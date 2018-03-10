#include "Scene.h"

Scene::Scene(std::string sceneName) : _sceneName(sceneName) { }

Scene::~Scene()
{
	for (auto go : _gameObjects)
	{
		go = nullptr;
	}
}

void Scene::Update(float deltaTime)
{
	for (auto go : _gameObjects)
	{
		go->Update(deltaTime);
	}
}

void Scene::SendMessageToGameObjects(IComponentMessage & message)
{
	for (auto go : _gameObjects)
	{
		go->SendMessageToComponent(message);
	}
}

void Scene::AddGameObject(shared_ptr<GameObject> gameObject)
{
	_gameObjects.push_back(gameObject);

	_gameObjectIDs.insert(make_pair(gameObject->GetID(), gameObject));
}

void Scene::DeleteGameObject(unsigned long id)
{
	int index = 0;
	GUID guidToDelete;
	for (auto go : _gameObjectIDs)
	{
		if (go.first.Data1 == id)
		{
			guidToDelete = go.first;
			break;
		}

		index++;
	}

	_gameObjects.erase(_gameObjects.begin() + index);

	std::map<GUID, std::shared_ptr<GameObject>>::iterator it;
	it = _gameObjectIDs.find(guidToDelete);
	_gameObjectIDs.erase(it);
}

