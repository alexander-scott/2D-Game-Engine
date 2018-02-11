#pragma once

#include <map>
#include <vector>
#include <memory>

#include "Math.h"

#pragma region Values

static constexpr int SCREEN_WIDTH = 800;
static constexpr int SCREEN_HEIGHT = 600;

static constexpr bool KEY_PRESS_AUTOREPEAT = false;

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
	eGraphicsDrawText,

	// Input messages
	eInputKeyboardMessage,
	eInputMouseMessage
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

enum KeyboardMessageType
{
	eKeyDown,
	eKeyUp,
	eCharPressed
};

enum MouseMessageType
{
	eMouseMoved,
	eLeftMouseClicked,
	eLeftMouseReleased,
	eRightMouseClicked,
	eRightMouseReleased
};

#pragma endregion