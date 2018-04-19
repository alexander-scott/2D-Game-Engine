#pragma once

#include "IComponent.h"

#include "IUpdateableComponent.h"
#include "IStartableComponent.h"

#include "GameObject.h"

class AlexPlatformManagerComponent : public IComponent, public IUpdateableComponent, public IStartableComponent
{
public:
	AlexPlatformManagerComponent(std::vector<shared_ptr<GameObject>> platformPool);
	~AlexPlatformManagerComponent();

	virtual void Update(float deltaTime) override;
	virtual void Start() override;

	shared_ptr<GameObject> GetNewPlatformFromPool();
	void ReturnPlatformToPool(shared_ptr<GameObject> platform);

private:
	std::vector<shared_ptr<GameObject>>		_platformPool;
	std::vector<shared_ptr<GameObject>>		_activePlatforms;
	std::vector<shared_ptr<GameObject>>		_inActivePlatforms;
};