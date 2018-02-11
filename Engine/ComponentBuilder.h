#pragma once

#include "rapidxml.hpp"

#include "ComponentFactory.h"

using namespace rapidxml;

namespace ComponentBuilder
{
	IComponent * BuildComponent(xml_node<>* node);
}