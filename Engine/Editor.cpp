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
