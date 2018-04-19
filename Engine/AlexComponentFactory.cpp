#include "AlexComponentFactory.h"

AlexControllerComponent* ComponentFactory::MakeAlexControllerComponent()
{
	return new AlexControllerComponent();
}

AlexPlatformManagerComponent * ComponentFactory::MakeAlexPlatformManagerComponent(std::vector<std::shared_ptr<GameObject>> platforms)
{
	return new AlexPlatformManagerComponent(platforms);
}

AlexGameManagerComponent * ComponentFactory::MakeAlexGameManagerComponent()
{
	return new AlexGameManagerComponent();
}
