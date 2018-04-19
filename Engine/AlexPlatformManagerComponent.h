#pragma once

#include "IComponent.h"

#include "GameObject.h"

#include "TransformComponent.h"

class AlexPlatformManagerComponent : public IComponent
{
public:
	AlexPlatformManagerComponent(std::vector<shared_ptr<GameObject>> platformPool);
	~AlexPlatformManagerComponent();

	void SetDependencies(TransformComponent* transform) { _transform = transform; }

	shared_ptr<GameObject> GetNewPlatformFromPool();
	void ReturnPlatformToPool(shared_ptr<GameObject> platform);

	TransformComponent* GetTransform() { return _transform; }

private:
	std::vector<shared_ptr<GameObject>>		_platformPool;
	std::vector<shared_ptr<GameObject>>		_activePlatforms;
	std::vector<shared_ptr<GameObject>>		_inActivePlatforms;

	TransformComponent* _transform;
};