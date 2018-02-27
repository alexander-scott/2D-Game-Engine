#include "Editor.h"

#include "RequestBuildSceneMessage.h"
#include "RequestSaveSceneMessage.h"

#include "InputKeyboardMessage.h"
#include "InputMouseMessage.h"

Editor::Editor(std::shared_ptr<SystemMessageDispatcher> dispatcher)
	: ISystem(SystemType::eEditor, dispatcher)
{
}

Editor::~Editor()
{
}

void Editor::InitaliseListeners()
{

}

void Editor::RecieveMessage(ISystemMessage & message)
{
}

void Editor::PlayStarted()
{
}

void Editor::PlayStopped()
{
}

void Editor::LoadNewScene(const char * filePath)
{
	// Request a new scene be built by the SceneBuilder system
	RequestBuildSceneMessage message(filePath); // Hardcoded for now
	SendMessageToDispatcher(message);
}

void Editor::SaveScene(const char * filePath)
{
	RequestSaveSceneMessage message(filePath);
	SendMessageToDispatcher(message);
}

void Editor::KeyboardInput(int keyCode, KeyboardMessageType messageType)
{
	InputKeyboardMessage message(messageType, static_cast<unsigned char>(keyCode));
	SendMessageToDispatcher(message);
}

void Editor::MouseInput(int xpos, int ypos, MouseMessageType messageType)
{
	InputMouseMessage message(messageType, xpos, ypos);
	SendMessageToDispatcher(message);
}
