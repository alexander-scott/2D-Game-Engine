#pragma once

#include <map>
#include <vector>
#include <memory>

#include "Math.h"

static constexpr int SCREEN_WIDTH = 800;
static constexpr int SCREEN_HEIGHT = 600;

enum SystemMessageType
{
	// Scene messages
	eDrawScene,
	eUpdateScene,

	// Scene build messages
	eRequestBuildSceneMessage,
	eBuildSceneMessage,

	// Graphics messages
	eGraphicsInitalise,
	eGraphicsDestroy,
	eGraphicsStartFrame,
	eGraphicsEndFrame,
	eGraphicsDrawSprite,
	eGraphicsDrawText
};

enum SystemType
{
	eMainWindow,
	eSceneManager,
	eSceneBuilder,
	eGraphics
};

enum ComponentType
{
	eTransformComponent
};

enum ComponentMessageType
{
	eTestMessage
};

enum MessengerType
{
	eTestMessenger,
};