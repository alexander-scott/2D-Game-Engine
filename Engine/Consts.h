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
	eEditor,
	eSceneManager,
	eSceneBuilder,
	eSceneSaver,
	eGraphics,
	eInputHandler
};

enum SystemMessageType
{
	// Scene messages
	eDrawScene,
	eUpdateScene,
	eSendMessageToGameObjects,

	// Scene build/save messages
	eRequestBuildSceneMessage,
	eRequestSaveSceneMessage,
	eBuildSceneMessage,
	eSaveSceneMessage,

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
	eInputUpdateGamePad,

	// Windows messages
	eWindowLostFocus,

	// Editor messages
	ePlayStarted,
	ePlayStopped
};

enum ComponentMessageType
{
	eSetParentTransformMessage,
	eActivateRebindingKeyboardCommands
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

enum EditorFieldTypes
{
	eInteger,
	eFloat,
	eDouble,
	eString
};

#pragma endregion

#pragma region Operators

// This fixes an issue where you are unable to have a GUID as a key in a map
inline bool operator<(const GUID & lhs, const GUID & rhs)
{
	return (memcmp(&lhs, &rhs, sizeof(GUID)) > 0 ? true : false);
}

#pragma endregion

#pragma region Structs

struct SceneItem
{
	int GameObjectID;
	unsigned int GameObjectParentID;
	char* GameObjectName;
	int ComponentCount;
};

// The InspectorField will display the field name and field value
// TODO: Pass in field type too.
struct InspectorField
{
	char* FieldName;
	char* FieldValue;
	int GameObjectID;
	int ComponentIndex;
	int FieldIndex;
	int FieldType;
};

#pragma endregion