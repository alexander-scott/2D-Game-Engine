#pragma once
#include "MCharacterComponent.h"
#include "MBackgroundComponent.h"

namespace ComponentFactory {
	MCharacterComponent * MakeMCharacterComponent();
	MBackgroundComponent * MakeMBackgroundComponent();
}