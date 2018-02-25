#pragma once

#include "MainWindow.h"

#define DllExport __declspec(dllexport)

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")

namespace EditorInterface
{
	extern "C" { DllExport void* InitaliseEngine(HWND hWnd); }

	extern "C" { DllExport void StartUpdateLoop(void* systemsPtr); }

	extern "C" { DllExport void LoadNewScene(void* systemsPtr, const char* filePath); }
	extern "C" { DllExport void SaveScene(void* systemsPtr, const char* filePath); }

	extern "C" { DllExport void PlayStarted(void* systemsPtr); }
	extern "C" { DllExport void PlayStopped(void* systemsPtr); }

	extern "C" { DllExport void CleanD3D(void* systemsPtr); }

	extern "C" { DllExport void MouseMove(void* systemsPtr, int xPos, int yPos); }

	extern "C" { DllExport void LeftMouseClick(void* systemsPtr, int xPos, int yPos); }
	extern "C" { DllExport void LeftMouseRelease(void* systemsPtr, int xPos, int yPos); }

	extern "C" { DllExport void RightMouseClick(void* systemsPtr, int xPos, int yPos); }
	extern "C" { DllExport void RightMouseRelease(void* systemsPtr, int xPos, int yPos); }

	extern "C" { DllExport void KeyDown(void* systemsPtr, int keyCode); }
	extern "C" { DllExport void KeyUp(void* systemsPtr, int keyCode); }
}