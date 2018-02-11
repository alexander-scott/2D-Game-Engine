#pragma once

#include "GameObject.h"

using namespace std;

class IScene
{
public:
	IScene(std::string sceneName);

	~IScene()
	{
		for (auto go : _gameObjects)
		{
			go = nullptr;
		}
	}

	virtual void Draw();
	virtual void Update(float deltaTime);

	void AddGameObject(shared_ptr<GameObject> gameObject);

	int GetNumberOfGameObjects() { return (int)_gameObjects.size(); }
	shared_ptr<GameObject> GetGameObjectAtIndex(int index) { return _gameObjects.at(index); }

protected:
	std::string											_sceneName;
	map<int, vector<shared_ptr<GameObject>>>			_renderLayers;
	vector<shared_ptr<GameObject>>						_gameObjects;
};