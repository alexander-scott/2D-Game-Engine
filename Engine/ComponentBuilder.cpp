#include "ComponentBuilder.h"

#include <unordered_map>

// TODO: Instead of having enums in this map, have function pointers
static std::unordered_map<std::string, ComponentType> ComponentMap
{
	{ "TransformComponent", ComponentType::eTransformComponent }
};

// Define component functions here
inline TransformComponent * BuildTransformComponent(xml_node<> * node);

IComponent * ComponentBuilder::BuildComponent(xml_node<>* node)
{
	std::string componentType = string(node->first_attribute("type")->value());

	// Check component type exists
	auto iterator = ComponentMap.find(componentType);
	if (iterator == ComponentMap.end())
		throw std::exception("Unable to find component type");

	switch (ComponentMap[componentType])
	{
		case ComponentType::eTransformComponent:
		{
			return BuildTransformComponent(node);
		}
	}

	throw std::exception("CODE SHOULD NEVER REACH HERE");
	return nullptr;
}

TransformComponent * BuildTransformComponent(xml_node<>* node)
{
	float xPos = (float)atof(node->first_attribute("xpos")->value());
	float yPos = -(float)atof(node->first_attribute("ypos")->value());
	float rot = (float)atof(node->first_attribute("rotation")->value());
	float scale = (float)atof(node->first_attribute("scale")->value());

	return ComponentFactory::MakeTransformComponent(Vec2(xPos, yPos), rot, scale);
}