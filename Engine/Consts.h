#pragma once

#include <map>
#include <vector>
#include <memory>

#include "Math.h"

#pragma region Values

static constexpr int SCREEN_WIDTH = 800;
static constexpr int SCREEN_HEIGHT = 600;

#pragma endregion

#pragma region Enums

enum SystemType
{
	eMainWindow,
	eSceneManager,
	eSceneBuilder,
	eGraphics
};

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

#pragma endregion