#include "Editor.h"

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
}

void Editor::SaveScene(const char * filePath)
{
}
