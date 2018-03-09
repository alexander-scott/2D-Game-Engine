#include "ComponentBuilder.h"
#include "Scene.h"

xml_node<>* _node;
shared_ptr<Scene> _scene;

// Define component functions here
inline IComponent * BuildTransformComponent();

// List component functions against string types found in the XML files
ComponentBuilder::ComponentBuilder(shared_ptr<Scene> scene)
{
	_scene = scene;
	_functionMapper.Insert("TransformComponent", BuildTransformComponent);
}

IComponent * ComponentBuilder::BuildComponent(xml_node<>* node)
{
	_node = node;

	// Call the function listed in the function mapper
	return _functionMapper.CallFunction<IComponent*>(string(node->first_attribute("type")->value()));
}

IComponent * BuildTransformComponent()
{
	float xPos = (float)atof(_node->first_attribute("xpos")->value());
	float yPos = -(float)atof(_node->first_attribute("ypos")->value());
	float rot = (float)atof(_node->first_attribute("rotation")->value());
	float scale = (float)atof(_node->first_attribute("scale")->value());

	return ComponentFactory::MakeTransformComponent(Vec2(xPos, yPos), rot, scale);
}

GUID ComponentBuilder::StringToGUID(const std::string& guid) {
	GUID output;
	unsigned long p0;
	int p1, p2, p3, p4, p5, p6, p7, p8, p9, p10;

	int err = sscanf_s(guid.c_str(), "%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		&p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10);

	if (err != 11)
		throw std::logic_error("Invalid GUID, format should be {00000000-0000-0000-0000-000000000000}");

	// Set the data like this to avoid corrupting the stack
	output.Data1 = p0;
	output.Data2 = p1;
	output.Data3 = p2;
	output.Data4[0] = p3;
	output.Data4[1] = p4;
	output.Data4[2] = p5;
	output.Data4[3] = p6;
	output.Data4[4] = p7;
	output.Data4[5] = p8;
	output.Data4[6] = p9;
	output.Data4[7] = p10;
	return output;
}