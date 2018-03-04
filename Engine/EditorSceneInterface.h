#pragma once

#include "EditorEngineInterface.h"

#include "SceneManager.h"

namespace EditorSceneInterface
{
	extern "C" { DllExport int GetGameObjectCount(void* sceneManagerPtr); }

	extern "C" { DllExport SceneItem* PopulateHierarchyItems(void* sceneManagerPtr, int itemCount); }

	extern "C" { DllExport int* GetComponentFieldCounts(void* sceneManagerPtr, unsigned long gameObjectID); }

	extern "C" { DllExport InspectorField* PopulateInspector(void* sceneManagerPtr, unsigned long gameObjectID, int componentIndex); }

	extern "C" { DllExport void RenameGameObject(void* sceneManagerPtr, unsigned long gameObjectID, const char* name); }

	extern "C" { DllExport SceneItem* CreateGameObject(void* sceneManagerPtr); }

	extern "C" { DllExport void FreeMemory(void* ptr); }}