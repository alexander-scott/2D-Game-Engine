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

static constexpr float PI = 3.141592741f;

static constexpr int MAX_POLY_VERTEX_COUNT = 64;

static float GRAVITY_SCALE = 20.0f; // Default is 20
static Vec2 GRAVITY_VECTOR(0, 9.81f * GRAVITY_SCALE); // Default is 9.81 * SCALE

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
	eInputHandler,
	ePhysics,
	eAudio
};

enum SystemMessageType
{
	// Engine messages
	eDrawScene, // SENT BY: Engine - RECIEVED BY: SceneManager - WHEN: Central Update Loop
	eUpdateScene, // SENT BY: Engine - RECIEVED BY: SceneManager - WHEN: Central Update Loop
	eGraphicsStartFrame, // SENT BY: Engine - RECIEVED BY: Graphics - WHEN: Central Update Loop
	eGraphicsEndFrame, // SENT BY: Engine - RECIEVED BY: Graphics - WHEN: Central Update Loop

	// Scene messages
	eRequestBuildSceneMessage, // SENT BY: Engine/Editor - RECIEVED BY: SceneBuilder - WHEN: When a scene is selected to be built
	eRequestSaveSceneMessage, // SENT BY: Editor - RECIEVED BY: SceneManager - WHEN: When the editor requests the scene be saved
	eBuildSceneMessage, // SENT BY: SceneBuilder - RECIEVED BY: SceneManager - WHEN: When scene has finished being built
	eSaveSceneMessage, // SENT BY: SceneManager - RECIEVED BY: SceneSaver - WHEN: When scene is about to be saved to a specific filepath
	eSceneSelectedToPlay, // SENT BY: SceneManager - RECIEVED BY: Physics - WHEN: Immediately when scene is selected to play. Used to cache relevant components.
	eSendMessageToGameObjects, // SENT BY: ######### - RECIEVED BY: SceneManager - WHEN: When a system wants to message GameObjects in a scene

	// Graphics messages
	eGraphicsInitalise, // SENT BY: MainWindow - RECIEVED BY: Graphics - WHEN: In SystemsInitalised() in MainWindow. Passes the HWND instance to Graphics.
	eGraphicsDestroy, // SENT BY: ######### - RECIEVED BY: Graphics - WHEN: When the application is shutting down. Destroys all D3D resources.
	eGraphicsDrawScene, // SENT BY: SceneManager - RECIEVED BY: Graphics - WHEN: Every time the scene is called to draw. Passes current scene pointer to graphics.

	// Input messages
	eInputKeyboardMessage,
	eInputMouseMessage,
	eInputUpdateGamePad,

	// Windows messages
	eWindowLostFocus,
	eWindowGainedFocus,

	// Editor messages
	ePlayStarted, // SENT BY: Engine/Editor - RECIEVED BY: SceneManager - WHEN: When the scene should be played. Tells the scene to start updating
	ePlayStopped, // SENT BY: Editor - RECIEVED BY: SceneManager/SceneBuilder - WHEN: When the scene should stop playing. Tells the scene to stop updating and for the scene to be rebuilt.

	// Physics messages
	eUpdatePhysics, // SENT BY: Engine - RECIEVED BY: Physics - WHEN: Central Update Loop

	// Audio messages
	ePlaySound,
	eSuspendAudio,
	eResumeAudio,
};

enum ComponentMessageType
{
	eSetParentTransformMessage,
	eAddForce,
	eActivateRebindingKeyboardCommands,
	eInputHandlerToGameObjectMessage
};

enum DrawableComponentType
{
	eTestDrawingType,
	eSprite,
	eSpriteAnimated,
	eText
};

enum InputGenericStateMessageType
{
	eKeyReleased,
	eKeyPressed
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

struct sCommand
{
	std::string _name;
	int _ID;
};

enum EditorFieldTypes
{
	eInteger,
	eFloat,
	eDouble,
	eString
};

enum ColliderType
{
	eCircle,
	ePolygon,
	eColliderTypeCount
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
struct InspectorField
{
	char* FieldName;
	char* FieldValue;
	int GameObjectID;
	int ComponentIndex;
	int FieldIndex;
	int FieldType;
};

struct RigidBodyData
{
	Vec2 velocity;

	float angularVelocity;
	float torque;

	Vec2 force;

	Mat2 orientationMatrix;

	// Set by rigidbody
	float intertia;  // moment of inertia
	float inverseInertia; // inverse inertia
	float mass;  // _mass
	float inverseMass; // inverse masee

	float staticFriction;
	float dynamicFriction;
	float restitution;

	RigidBodyData(Vec2 velocity, float angularVelocity, float torque, Vec2 force, float staticFriction, float dynamicFrication, float restituation)
		: velocity(velocity), angularVelocity(angularVelocity), torque(torque), force(force),
		staticFriction(staticFriction), dynamicFriction(dynamicFrication), restitution(restituation)
	{

	}
};

struct Bounds
{
public:
	int xPos;
	int yPos;
	int width;
	int height;

	int colliderIndex;

	Bounds() { }
	Bounds(int x, int y, int wid, int hei, int colIndex = -1) : xPos(x), yPos(y), width(wid), height(hei), colliderIndex(colIndex) { }
};

struct Rect
{
public:
	int LeftX;
	int RightX;
	int TopY;
	int BotY;
	Vec2 Centre;
};

#pragma endregion