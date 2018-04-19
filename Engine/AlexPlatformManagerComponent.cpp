#include "AlexPlatformManagerComponent.h"

#include "TransformComponent.h"

AlexPlatformManagerComponent::AlexPlatformManagerComponent(std::vector<shared_ptr<GameObject>> platformPool) 
	: IComponent("AlexPlatformManagerComponent")
{
	_platformPool = platformPool;

	// Set all platforms as inactive
	_inActivePlatforms = std::vector<shared_ptr<GameObject>>(_platformPool);
}

AlexPlatformManagerComponent::~AlexPlatformManagerComponent()
{
}

AlexPlatformManagerComponent::Platform AlexPlatformManagerComponent::GetNewPlatformFromPool()
{
	if (_inActivePlatforms.size() > 0)
	{
		auto platform = _inActivePlatforms[0];
		_activePlatforms.push_back(platform);
		_inActivePlatforms.erase(_inActivePlatforms.begin());

		platform->SetActive(true);
		return Platform(platform, (int)_activePlatforms.size() - 1);
	}
	else
	{
		throw std::exception("Run out of platforms in AlexPlatformManagerComponent!");
	}
}

void AlexPlatformManagerComponent::ReturnPlatformToPool(Platform platform)
{
	platform.GameObject->SetActive(false);
	_activePlatforms.erase(_activePlatforms.begin() + platform.ActivePlatformIndex);
	_inActivePlatforms.push_back(platform.GameObject);
}