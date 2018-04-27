#include "EditorSystem.h"

#include "RequestBuildSceneMessage.h"
#include "RequestSaveSceneMessage.h"

#include "InputKeyboardMessage.h"
#include "InputMouseMessage.h"

EditorSystem::EditorSystem(std::shared_ptr<SystemMessageDispatcher> dispatcher)
	: ISystem(SystemType::eEditor, dispatcher)
{
}

EditorSystem::~EditorSystem()
{
}

void EditorSystem::InitaliseListeners()
{

}

void EditorSystem::RecieveMessage(ISystemMessage & message)
{
}

void EditorSystem::PlayStarted()
{
	// Start playing
	SendMessageToDispatcher(ISystemMessage(SystemMessageType::ePlayStarted));
}

void EditorSystem::PlayStopped()
{
	// Stop playing
	SendMessageToDispatcher(ISystemMessage(SystemMessageType::ePlayStopped));
}

void EditorSystem::LoadNewScene(const char * filePath)
{
	// Request a new scene be built by the SceneBuilder system
	RequestBuildSceneMessage message(filePath); // Hardcoded for now
	SendMessageToDispatcher(message);
}

void EditorSystem::SaveScene(const char * filePath)
{
	RequestSaveSceneMessage message(filePath);
	SendMessageToDispatcher(message);
}

void EditorSystem::KeyboardInput(int keyCode, KeyboardMessageType messageType)
{
	InputKeyboardMessage message(messageType, static_cast<unsigned char>(keyCode));
	SendMessageToDispatcher(message);
}

void EditorSystem::MouseInput(int xpos, int ypos, MouseMessageType messageType)
{
	InputMouseMessage message(messageType, xpos, ypos);
	SendMessageToDispatcher(message);
}
