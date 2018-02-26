#include "CustomException.h"

#include "Engine.h"
#include "Logger.h"

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR pArgs, INT)
{
	try
	{
		Logger::Instance().LogMessage("Initalising Systems", LogSeverity::eInfo);
		Engine engine(hInst, pArgs);

		// Update the systems until the user presses esc or closes the window
		Logger::Instance().LogMessage("Starting main update loop", LogSeverity::eInfo);
		engine.StartUpdateLoop(); 

		Logger::Instance().LogMessage("Program shutting down", LogSeverity::eInfo);
		Logger::Instance().LogMessage("---------------------", LogSeverity::eInfo);
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

	return 0;
}