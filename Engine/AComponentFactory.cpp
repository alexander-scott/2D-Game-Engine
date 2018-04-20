#include "AComponentFactory.h"

AControllerComponent* ComponentFactory::MakeAlexControllerComponent()
{
	return new AControllerComponent();
}

APlatformManagerComponent * ComponentFactory::MakeAlexPlatformManagerComponent(std::vector<std::shared_ptr<GameObject>> platforms)
{
	return new APlatformManagerComponent(platforms);
}

AGameManagerComponent * ComponentFactory::MakeAlexGameManagerComponent()
{
	return new AGameManagerComponent();
}
