#pragma once

#include "GameObject.h"

using namespace std;

class IScene
{
public:
	void Draw();

	virtual void Update(float deltaTime) = 0;
	virtual void CacheComponents(shared_ptr<GameObject> gameObj) = 0;

	int GetNumberOfGameObjects() { return (int)mGameObjects.size(); }
	shared_ptr<GameObject> GetGameObjectAtIndex(int index) { return mGameObjects.at(index); }

protected:
	map<int, vector<shared_ptr<GameObject>>>			mRenderLayers;
	vector<shared_ptr<GameObject>>						mGameObjects;
};