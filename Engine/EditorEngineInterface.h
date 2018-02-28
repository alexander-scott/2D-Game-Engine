#pragma once

#include "MainWindow.h"

#define DllExport __declspec(dllexport)

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")

namespace EditorEngineInterface
{
	extern "C" { DllExport void* InitaliseEngine(HWND hWnd); }
	extern "C" { DllExport void* GetEditorSystem(void* enginePtr); }
	extern "C" { DllExport void* GetSceneManagerSystem(void* enginePtr); }

	extern "C" { DllExport void StartUpdateLoop(void* enginePtr); }

	extern "C" { DllExport void LoadNewScene(void* editorPtr, const char* filePath); }
	extern "C" { DllExport void SaveScene(void* editorPtr, const char* filePath); }

	extern "C" { DllExport void PlayStarted(void* editorPtr); }
	extern "C" { DllExport void PlayStopped(void* editorPtr); }

	extern "C" { DllExport void CleanD3D(void* enginePtr); }
}