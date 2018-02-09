#pragma once

#include <map>
#include <vector>

#include "Math.h"

static constexpr int SCREEN_WIDTH = 800;
static constexpr int SCREEN_HEIGHT = 600;

enum MessageType
{
	eTestMessage
};

enum MessengerType
{
	eEngine,
	eMessengerTypeCount
};