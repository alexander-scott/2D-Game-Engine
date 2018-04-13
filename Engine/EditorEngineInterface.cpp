#include "EditorEngineInterface.h"

#include "Logger.h"
#include "Engine.h"

#include "Editor.h"

void * EditorEngineInterface::InitaliseEngine(HWND hWnd, const char * filePath)
{
	try
	{
		Logger::Instance().LogMessage("Initalising Systems", LogSeverity::eInfo);

		return new Engine(hWnd, filePath);
	}
	catch (const CustomException& e)
	{
		const std::wstring eMsg = e.GetFullMessage() +
			L"\n\nException caught at main window creation.";
		Logger::Instance().LogMessage("Exception caught at main window creation", "MAIN", LogSeverity::eError);
		MessageBox(nullptr, eMsg.c_str(), e.GetExceptionType().c_str(), MB_ICONERROR);
	}
	catch (const std::exception& e)
	{
		// need to convert std::exception what() string from narrow to wide string
		const std::string whatStr(e.what());
		const std::wstring eMsg = std::wstring(whatStr.begin(), whatStr.end()) +
			L"\n\nException caught at main window creation.";
		Logger::Instance().LogMessage("Exception caught at main window creation", "MAIN", LogSeverity::eError);
		MessageBox(nullptr, eMsg.c_str(), L"Unhandled STL Exception", MB_ICONERROR);
	}
	catch (...)
	{
		Logger::Instance().LogMessage("Exception caught at main window creation", "MAIN", LogSeverity::eError);
		MessageBox(nullptr, L"\n\nException caught at main window creation.",
			L"Unhandled Non-STL Exception", MB_ICONERROR);
	}

	return nullptr;
}

void * EditorEngineInterface::GetEditorSystem(void* enginePtr)
{
	Engine* engine = static_cast<Engine*>(enginePtr);
	return engine->GetSystem(SystemType::eEditor).get();
}

void * EditorEngineInterface::GetSceneManagerSystem(void* enginePtr)
{
	Engine* engine = static_cast<Engine*>(enginePtr);
	return engine->GetSystem(SystemType::eSceneManager).get();
}

// Reason this is in a seperate function to initalise engine is because we need to 
// return a pointer to the system manager which will never happen if we started a while loop
void EditorEngineInterface::StartUpdateLoop(void * enginePtr)
{
	Engine* engine = static_cast<Engine*>(enginePtr);

	Logger::Instance().LogMessage("Starting main update loop", LogSeverity::eInfo);

	engine->StartUpdateLoop();

	Logger::Instance().LogMessage("Program shutting down", LogSeverity::eInfo);
	Logger::Instance().LogMessage("---------------------", LogSeverity::eInfo);
}

void EditorEngineInterface::CleanD3D(void * enginePtr)
{
	Engine* engine = static_cast<Engine*>(enginePtr);
	delete engine;
}

void EditorEngineInterface::LoadNewScene(void * editorPtr, const char * filePath)
{
	Editor* editor = static_cast<Editor*>(editorPtr);
	editor->LoadNewScene(filePath);
}

void EditorEngineInterface::SaveScene(void * editorPtr, const char * filePath)
{
	Editor* editor = static_cast<Editor*>(editorPtr);
	editor->SaveScene(filePath);
}

void EditorEngineInterface::PlayStarted(void * editorPtr)
{
	Editor* editor = static_cast<Editor*>(editorPtr);
	editor->PlayStarted();
}

void EditorEngineInterface::PlayStopped(void * editorPtr)
{
	Editor* editor = static_cast<Editor*>(editorPtr);
	editor->PlayStopped();
}