#include "EditorInterface.h"

#include "Logger.h"
#include "SystemManager.h"

void * EditorInterface::InitaliseEngine(HWND hWnd)
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

// Reason this is in a seperate function to initalise engine is because we need to 
// return a pointer to the system manager which will never happen if we started a while loop
void EditorInterface::StartUpdateLoop(void * systemsPtr)
{
	SystemManager* systemManager = static_cast<SystemManager*>(systemsPtr);

	Logger::Instance().LogMessage("Starting main update loop", LogSeverity::eInfo);

	systemManager->StartUpdateLoop();

	Logger::Instance().LogMessage("Program shutting down", LogSeverity::eInfo);
	Logger::Instance().LogMessage("---------------------", LogSeverity::eInfo);
}

void EditorInterface::LoadNewScene(void * systemsPtr, const char * filePath)
{

}

void EditorInterface::SaveScene(void * systemsPtr, const char * filePath)
{
}

void EditorInterface::PlayStarted(void * systemsPtr)
{
}

void EditorInterface::PlayStopped(void * systemsPtr)
{
}

void EditorInterface::CleanD3D(void * systemsPtr)
{
	SystemManager* systemManager = static_cast<SystemManager*>(systemsPtr);
	delete systemManager;
}

void EditorInterface::MouseMove(void * systemsPtr, int xPos, int yPos)
{
	
}

void EditorInterface::LeftMouseClick(void * systemsPtr, int xPos, int yPos)
{
	
}

void EditorInterface::LeftMouseRelease(void * systemsPtr, int xPos, int yPos)
{
	
}

void EditorInterface::RightMouseClick(void * systemsPtr, int xPos, int yPos)
{
	
}

void EditorInterface::RightMouseRelease(void * systemsPtr, int xPos, int yPos)
{

}

void EditorInterface::KeyDown(void * systemsPtr, int keyCode)
{
	
}

void EditorInterface::KeyUp(void * systemsPtr, int keyCode)
{
	
}
