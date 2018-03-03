#pragma once

#include "EditorEngineInterface.h"

namespace EditorInputInterface
{
	extern "C" { DllExport void MouseMove(void* editorPtr, int xPos, int yPos); }

	extern "C" { DllExport void LeftMouseClick(void* editorPtr, int xPos, int yPos); }
	extern "C" { DllExport void LeftMouseRelease(void* editorPtr, int xPos, int yPos); }
	extern "C" { DllExport void RightMouseClick(void* editorPtr, int xPos, int yPos); }
	extern "C" { DllExport void RightMouseRelease(void* editorPtr, int xPos, int yPos); }

	extern "C" { DllExport void KeyDown(void* editorPtr, int keyCode); }
	extern "C" { DllExport void KeyUp(void* editorPtr, int keyCode); }
}