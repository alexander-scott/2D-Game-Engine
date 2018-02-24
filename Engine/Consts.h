#pragma once

#include <map>
#include <vector>
#include <memory>

#include "Math.h"
#include "WinDefines.h"

#pragma region Values

static constexpr int SCREEN_WIDTH = 800;
static constexpr int SCREEN_HEIGHT = 600;

static constexpr bool KEY_PRESS_AUTOREPEAT = false;

static constexpr float MS_PER_UPDATE = 0.01f;

#pragma endregion

#pragma region Enums

enum SystemType
{
	eMainWindow,
	eEngine,
	eSceneManager,
	eSceneBuilder,
	eGraphics,
	eInputHandler
};

enum SystemMessageType
{
	// Scene messages
	eDrawScene,
	eUpdateScene,
	eSendMessageToGameObjects,

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
	eGraphicsDrawScene,

	// Input messages
	eInputKeyboardMessage,
	eInputMouseMessage,

	// Windows messages
	eWindowLostFocus,

	// System messages
	eSystemUpdate,
};

enum ComponentType
{
	eTransformComponent
};

enum ComponentMessageType
{
	eSetParentTransformMessage
};

enum DrawableComponentType
{
	eTestDrawingType
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

#pragma region Operators

// This fixes an issue where you are unable to have a GUID as a key in a map
inline bool operator<(const GUID & lhs, const GUID & rhs)
{
	return (memcmp(&lhs, &rhs, sizeof(GUID)) > 0 ? true : false);
}

#pragma endregion