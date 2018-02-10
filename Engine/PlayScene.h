#pragma once

#include "IScene.h"

class PlayScene : public IScene
{
public:
	void Update(float deltaTime) override;
	void CacheComponents(shared_ptr<GameObject> gameObj) override;
};