#pragma once
#include "MCharacterComponent.h"
#include "MBackgroundComponent.h"
#include "MPhantomComponent.h"
#include "MChestComponent.h"
#include "MIntroComponent.h"

namespace ComponentFactory {
	MCharacterComponent * MakeMCharacterComponent();
	MBackgroundComponent * MakeMBackgroundComponent();
	MPhantomComponent * MakeMPhantomComponent();
	MChestComponent * MakeMChestComponent();
	MIntroComponent * MakeMIntroComponent();
}