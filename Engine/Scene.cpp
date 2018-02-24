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

// In this function you can dissassemble GameObjects and add them to various structures.
// Only called at scene initalisation so doesn't have to be performant
void Scene::AddGameObject(shared_ptr<GameObject> gameObject)
{
	_gameObjects.push_back(gameObject);

	_gameObjectIDs.insert(make_pair(gameObject->GetID(), gameObject));
};
