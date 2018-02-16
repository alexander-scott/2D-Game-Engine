#pragma once

#include "GameObject.h"

using namespace std;

class IScene
{
public:
	IScene(std::string sceneName);
	~IScene();

	virtual void Draw(DrawSceneMessage& message);
	virtual void Update(float deltaTime);

	void SendMessageToGameObjects(IComponentMessage& message);

	std::string GetSceneName() { return _sceneName; }
	void AddGameObject(shared_ptr<GameObject> gameObject);

	int GetNumberOfGameObjects() { return (int)_gameObjects.size(); }
	shared_ptr<GameObject> GetGameObject(GUID id) { return _gameObjectIDs.find(id)->second; }
	shared_ptr<GameObject> GetGameObject(int index) { return _gameObjects.at(index); }

protected:
	vector<shared_ptr<GameObject>>						_gameObjects;

	string												_sceneName;
	map<int, vector<shared_ptr<GameObject>>>			_renderLayers;
	map<GUID, shared_ptr<GameObject>>					_gameObjectIDs;
};