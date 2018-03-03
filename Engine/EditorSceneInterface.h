#pragma once

#include "EditorEngineInterface.h"

#include "SceneManager.h"

namespace EditorSceneInterface
{
	extern "C" { DllExport int GetGameObjectCount(void* sceneManagerPtr); }

	extern "C" { DllExport SceneItem* PopulateHierarchyItems(void* sceneManagerPtr, int itemCount); }

	extern "C" { DllExport InspectorItem* PopulateInspector(void* sceneManagerPtr, unsigned long gameObjectID); }

	extern "C" { DllExport void FreeMemory(void* ptr); }}