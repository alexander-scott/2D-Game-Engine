#pragma once

#include "EditorEngineInterface.h"

namespace EditorInputInterface
{
	extern "C" { DllExport void MouseMove(void* systemsPtr, int xPos, int yPos); }

	extern "C" { DllExport void LeftMouseClick(void* systemsPtr, int xPos, int yPos); }
	extern "C" { DllExport void LeftMouseRelease(void* systemsPtr, int xPos, int yPos); }

	extern "C" { DllExport void RightMouseClick(void* systemsPtr, int xPos, int yPos); }
	extern "C" { DllExport void RightMouseRelease(void* systemsPtr, int xPos, int yPos); }

	extern "C" { DllExport void KeyDown(void* systemsPtr, int keyCode); }
	extern "C" { DllExport void KeyUp(void* systemsPtr, int keyCode); }
}