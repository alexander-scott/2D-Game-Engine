#pragma once

#include "MainWindow.h"

#define DllExport __declspec(dllexport)

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")

namespace EditorInterface
{
	extern "C" { DllExport void* InitaliseEngine(HWND hWnd, int Width, int Height, const char* filePath); }
	extern "C" { DllExport void StartUpdateLoop(void* systemsPtr); }
}