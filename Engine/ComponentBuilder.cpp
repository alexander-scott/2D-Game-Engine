#include "ComponentBuilder.h"

xml_node<>* _node;

// Define component functions here
inline IComponent * BuildTransformComponent();

// List component functions against string types found in the XML files
ComponentBuilder::ComponentBuilder()
{
	functionMapper.Insert("TransformComponent", BuildTransformComponent);
}

IComponent * ComponentBuilder::BuildComponent(xml_node<>* node)
{
	_node = node;

	// Call the function listed in the function mapper
	return functionMapper.CallFunction<IComponent*>(string(node->first_attribute("type")->value()));
}

IComponent * BuildTransformComponent()
{
	float xPos = (float)atof(_node->first_attribute("xpos")->value());
	float yPos = -(float)atof(_node->first_attribute("ypos")->value());
	float rot = (float)atof(_node->first_attribute("rotation")->value());
	float scale = (float)atof(_node->first_attribute("scale")->value());

	return ComponentFactory::MakeTransformComponent(Vec2(xPos, yPos), rot, scale);
}