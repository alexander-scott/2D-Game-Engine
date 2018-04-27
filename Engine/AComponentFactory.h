#pragma once

#include "AControllerComponent.h"
#include "APlatformManagerComponent.h"
#include "AGameManagerComponent.h"

namespace ComponentFactory
{
	AControllerComponent * MakeAlexControllerComponent();
	APlatformManagerComponent * MakeAlexPlatformManagerComponent(std::vector<std::shared_ptr<GameObject>> platforms);
	AGameManagerComponent * MakeAlexGameManagerComponent();
}