#pragma once
#include "MCharacterComponent.h"
#include "MBackgroundComponent.h"
#include "MPhantomComponent.h"


namespace ComponentFactory {
	MCharacterComponent * MakeMCharacterComponent();
	MBackgroundComponent * MakeMBackgroundComponent();
	MPhantomComponent * MakeMPhantomComponent();
}