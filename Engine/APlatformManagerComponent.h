#pragma once

#include "IComponent.h"

#include "GameObject.h"

#include "TransformComponent.h"

class APlatformManagerComponent : public IComponent
{
public:
	struct Platform 
	{
	public:
		Platform(shared_ptr<GameObject> gameObj, int index) : GameObject(gameObj), ActivePlatformIndex(index) 
		{ 
			Transform = GameObject->GetComponent<TransformComponent>();
		}

		shared_ptr<GameObject>	GameObject;
		TransformComponent*		Transform;
		int						ActivePlatformIndex;
	};

	APlatformManagerComponent(std::vector<shared_ptr<GameObject>> platformPool);
	~APlatformManagerComponent();

	void SetDependencies(TransformComponent* transform) { _transform = transform; }

	Platform GetNewPlatformFromPool();
	void ReturnPlatformToPool(Platform platform);

	TransformComponent* GetTransform() { return _transform; }

private:
	std::vector<shared_ptr<GameObject>>		_platformPool;
	std::vector<shared_ptr<GameObject>>		_activePlatforms;
	std::vector<shared_ptr<GameObject>>		_inActivePlatforms;

	TransformComponent* _transform;
};