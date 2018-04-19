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

shared_ptr<GameObject> AlexPlatformManagerComponent::GetNewPlatformFromPool()
{
	if (_inActivePlatforms.size() > 0)
	{
		auto platform = _inActivePlatforms[0];
		_activePlatforms.push_back(platform);
		_inActivePlatforms.erase(_inActivePlatforms.begin());

		platform->SetActive(true);
		return platform;
	}
	else
	{
		throw std::exception("Run out of platforms in AlexPlatformManagerComponent!");
		return nullptr;
	}
}

void AlexPlatformManagerComponent::ReturnPlatformToPool(shared_ptr<GameObject> platform)
{

}