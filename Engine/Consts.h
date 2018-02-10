#pragma once

#include <map>
#include <vector>
#include <memory>

#include "Math.h"

static constexpr int SCREEN_WIDTH = 800;
static constexpr int SCREEN_HEIGHT = 600;

enum MessageType
{
	eTestMessage,
	eRequestBuildSceneMessage,
	eBuildSceneMessage
};

enum MessengerType
{
	eEngineMessenger,
	eSceneBuilderMessenger
};

enum SystemType
{
	eSceneBuilder
};

enum ComponentType
{
	eTransformComponent
};