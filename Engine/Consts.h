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
	eSetParentTransformMessage,
	eTestMessage
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

#pragma region Structs

struct SpriteData
{
public:
	std::string		Name;
	Vec2			Pos;
	RECT*			Rect;
	float			Rot;
	float			Scale;
	Vec2			Offset;
};

struct TextData
{
	std::string		Text;
	Vec2			Pos;
	float			Rot;
	float*			RgbColours;
	float			Scale;
	Vec2			Offset;
};

#pragma endregion