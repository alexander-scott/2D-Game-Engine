#pragma once

#include "AlexControllerComponent.h"
#include "AlexPlatformManagerComponent.h"

namespace ComponentFactory
{
	AlexControllerComponent * MakeAlexControllerComponent();
	AlexPlatformManagerComponent* MakeAlexPlatformManagerComponent(std::vector<std::shared_ptr<GameObject>> platforms);
}