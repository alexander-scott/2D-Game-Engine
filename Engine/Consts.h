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
	eRequestBuildSceneMessage,
	eBuildSceneMessage,

	// Graphics messages
	eGraphicsInitalise,
	eGraphicsStartFrame,
	eGraphicsEndFrame,
	eGraphicsDrawSprite,
	eGraphicsDrawText
};

enum SystemType
{
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