#include "ComponentBuilder.h"

xml_node<>* _node;

// Define component functions here
inline IComponent * BuildTransformComponent();
inline IComponent * BuildSpriteRendererComponent();
inline IComponent * BuildTextRendererComponent();


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

//TODO : delete when sure that we don't use it anymore - we should only be using TextRendererComponent or SpriteRendererComponent
IComponent * BuildTransformComponent()
{
	float xPos = (float)atof(_node->first_attribute("xpos")->value());
	float yPos = -(float)atof(_node->first_attribute("ypos")->value());
	float rot = (float)atof(_node->first_attribute("rotation")->value());
	float scale = (float)atof(_node->first_attribute("scale")->value());

	return ComponentFactory::MakeTransformComponent(Vec2(xPos, yPos), rot, scale);
}
//END - TODO

IComponent * BuildSpriteRendererComponent()
{
	float xPos = (float)atof(_node->first_attribute("xpos")->value());
	float yPos = -(float)atof(_node->first_attribute("ypos")->value());
	float rot = (float)atof(_node->first_attribute("rotation")->value());
	float scale = (float)atof(_node->first_attribute("scale")->value());
	RECT *rect = new RECT(); rect->top = 0; rect->left = 0; rect->right = 1; rect->bottom = 1; //TODO : change when possible (see xml scenes)
	Vec2 offset = Vec2(0.0f, 0.0f); //TODO : change when possible (see xml scenes)
	std::string name = "boop!"; //TODO : change

	return ComponentFactory::MakeSpriteRendererComponent(Vec2(xPos, yPos), rot, scale, rect, offset,name);
}

IComponent * BuildTextRendererComponent()
{
	float xPos = (float)atof(_node->first_attribute("xpos")->value());
	float yPos = -(float)atof(_node->first_attribute("ypos")->value());
	float rot = (float)atof(_node->first_attribute("rotation")->value());
	float scale = (float)atof(_node->first_attribute("scale")->value());
	RECT *rect = new RECT(); rect->top = 0; rect->left = 0; rect->right = 1; rect->bottom = 1; //TODO : change when possible (see xml scenes)
	Vec2 offset = Vec2(0.0f, 0.0f); //TODO : change when possible (see xml scenes)
	std::string text = "text";
	float * rgb = new float();


	return ComponentFactory::MakeTextRendererComponent(Vec2(xPos, yPos), rot, scale, rect, offset, text, rgb);
}
