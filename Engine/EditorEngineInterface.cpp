#include "EditorEngineInterface.h"

#include "Logger.h"
#include "SystemManager.h"

#include "Editor.h"

void * EditorEngineInterface::InitaliseEngine(HWND hWnd)
{
	try
	{
		Logger::Instance().LogMessage("Initalising Systems", LogSeverity::eInfo);

		return new SystemManager(hWnd);
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

void * EditorEngineInterface::GetEditorSystem(void* systemsPtr)
{
	SystemManager* systemManager = static_cast<SystemManager*>(systemsPtr);
	return systemManager->GetSystem(SystemType::eEditor).get();
}

void * EditorEngineInterface::GetSceneManagerSystem(void* systemsPtr)
{
	SystemManager* systemManager = static_cast<SystemManager*>(systemsPtr);
	return systemManager->GetSystem(SystemType::eSceneManager).get();
}

// Reason this is in a seperate function to initalise engine is because we need to 
// return a pointer to the system manager which will never happen if we started a while loop
void EditorEngineInterface::StartUpdateLoop(void * systemsPtr)
{
	SystemManager* systemManager = static_cast<SystemManager*>(systemsPtr);

	Logger::Instance().LogMessage("Starting main update loop", LogSeverity::eInfo);

	systemManager->StartUpdateLoop();

	Logger::Instance().LogMessage("Program shutting down", LogSeverity::eInfo);
	Logger::Instance().LogMessage("---------------------", LogSeverity::eInfo);
}

void EditorEngineInterface::CleanD3D(void * systemsPtr)
{
	SystemManager* systemManager = static_cast<SystemManager*>(systemsPtr);
	delete systemManager;
}

void EditorEngineInterface::LoadNewScene(void * editorPtr, const char * filePath)
{
	Editor* editorSystem = static_cast<Editor*>(editorPtr);
	editorSystem->LoadNewScene(filePath);
}

void EditorEngineInterface::SaveScene(void * editorPtr, const char * filePath)
{
	Editor* editorSystem = static_cast<Editor*>(editorPtr);
	editorSystem->SaveScene(filePath);
}

void EditorEngineInterface::PlayStarted(void * editorPtr)
{
	Editor* editorSystem = static_cast<Editor*>(editorPtr);
	editorSystem->PlayStarted();
}

void EditorEngineInterface::PlayStopped(void * editorPtr)
{
	Editor* editorSystem = static_cast<Editor*>(editorPtr);
	editorSystem->PlayStopped();
}