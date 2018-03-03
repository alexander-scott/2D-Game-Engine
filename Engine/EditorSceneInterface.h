#pragma once

#include "EditorEngineInterface.h"

#include "SceneManager.h"

namespace EditorSceneInterface
{
	extern "C" { DllExport int GetGameObjectCount(void* sceneManagerPtr); }

	extern "C" { DllExport SceneItem* PopulateHierarchyItems(void* sceneManagerPtr, int itemCount); }

	extern "C" { DllExport void FreeHierarchyMemory(void* hierarchy); }
}