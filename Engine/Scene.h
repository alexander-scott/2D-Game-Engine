#pragma once

#include "GameObject.h"

using namespace std;

class Scene
{
public:
	Scene(std::string sceneName);
	~Scene();

	void Update(float deltaTime);

	void SendMessageToGameObjects(IComponentMessage& message);

	std::string GetSceneName() { return _sceneName; }
	void AddGameObject(shared_ptr<GameObject> gameObject);

	int GetNumberOfGameObjects() { return (int)_gameObjects.size(); }
	vector<shared_ptr<GameObject>> GetAllGameObjects() { return _gameObjects; }
	shared_ptr<GameObject> GetGameObject(GUID id) { return _gameObjectIDs.find(id)->second; }
	shared_ptr<GameObject> GetGameObject(int index) { return _gameObjects.at(index); }

protected:
	vector<shared_ptr<GameObject>>						_gameObjects;

	string												_sceneName;
	map<GUID, shared_ptr<GameObject>>					_gameObjectIDs;
};