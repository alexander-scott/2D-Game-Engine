#include "EditorInputInterface.h"

#include "Editor.h"

void EditorInputInterface::MouseMove(void * editorPtr, int xPos, int yPos)
{
	Editor* editor = static_cast<Editor*>(editorPtr);
	editor->MouseInput(xPos, yPos, MouseMessageType::eMouseMoved);
}

void EditorInputInterface::LeftMouseClick(void * editorPtr, int xPos, int yPos)
{
	Editor* editor = static_cast<Editor*>(editorPtr);
	editor->MouseInput(xPos, yPos, MouseMessageType::eLeftMouseClicked);
}

void EditorInputInterface::LeftMouseRelease(void * editorPtr, int xPos, int yPos)
{
	Editor* editor = static_cast<Editor*>(editorPtr);
	editor->MouseInput(xPos, yPos, MouseMessageType::eLeftMouseReleased);
}

void EditorInputInterface::RightMouseClick(void * editorPtr, int xPos, int yPos)
{
	Editor* editor = static_cast<Editor*>(editorPtr);
	editor->MouseInput(xPos, yPos, MouseMessageType::eRightMouseClicked);
}

void EditorInputInterface::RightMouseRelease(void * editorPtr, int xPos, int yPos)
{
	Editor* editor = static_cast<Editor*>(editorPtr);
	editor->MouseInput(xPos, yPos, MouseMessageType::eRightMouseReleased);
}

void EditorInputInterface::KeyDown(void * editorPtr, int keyCode)
{
	Editor* editor = static_cast<Editor*>(editorPtr);
	editor->KeyboardInput(keyCode, KeyboardMessageType::eKeyDown);
}

void EditorInputInterface::KeyUp(void * editorPtr, int keyCode)
{
	Editor* editor = static_cast<Editor*>(editorPtr);
	editor->KeyboardInput(keyCode, KeyboardMessageType::eKeyUp);
}
