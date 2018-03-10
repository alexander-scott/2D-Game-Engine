#include "ComponentBuilder.h"
#include "Scene.h"

xml_node<>* _node;
shared_ptr<Scene> _scene;

// Define component functions here
inline IComponent * BuildTransformComponent();
inline IComponent * BuildRigidbodyComponent();
inline IComponent * BuildCircleColliderComponent();
inline IComponent * BuildBoxColliderComponent();

// List component functions against string types found in the XML files
ComponentBuilder::ComponentBuilder(shared_ptr<Scene> scene)
{
	_scene = scene;
	_functionMapper.Insert("TransformComponent", BuildTransformComponent);
	_functionMapper.Insert("RigidbodyComponent", BuildRigidbodyComponent);
	_functionMapper.Insert("CircleColliderComponent", BuildCircleColliderComponent);
	_functionMapper.Insert("BoxColliderComponent", BuildBoxColliderComponent);
}

IComponent * ComponentBuilder::BuildComponent(xml_node<>* node)
{
	_node = node;

	// Call the function listed in the function mapper
	return _functionMapper.CallFunction<IComponent*>(string(node->first_attribute("type")->value()));
}

GUID StringToGUID(const std::string& guid) {
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

IComponent * BuildTransformComponent()
{
	float xPos = (float)atof(_node->first_attribute("xpos")->value());
	float yPos = -(float)atof(_node->first_attribute("ypos")->value());
	float rot = (float)atof(_node->first_attribute("rotation")->value());
	float scale = (float)atof(_node->first_attribute("scale")->value());

	return ComponentFactory::MakeTransformComponent(Vec2(xPos, yPos), rot, scale);
}

IComponent * BuildRigidbodyComponent()
{
	float staticF = (float)atof(_node->first_attribute("staticfriction")->value());
	float dynamicF = (float)atof(_node->first_attribute("dynamicfriction")->value());
	float restitution = (float)atof(_node->first_attribute("restitution")->value());
	float density = (float)atof(_node->first_attribute("density")->value());

	bool isStatic = false;
	if (bool(_node->first_attribute("static")->value()))
		isStatic = true;

	bool lockRotation = false;
	if (bool(_node->first_attribute("lockrotation")->value()))
		lockRotation = true;

	return ComponentFactory::MakeRigidbodyComponent(staticF, dynamicF, restitution, density, isStatic, lockRotation);
}

inline IComponent * BuildCircleColliderComponent()
{
	float radius = (float)atof(_node->first_attribute("radius")->value());

	GUID transGameObjID = StringToGUID(string(_node->first_attribute("transformcomponent")->value()));
	TransformComponent* trans = _scene->GetGameObject(transGameObjID)->GetComponent<TransformComponent>();

	GUID rbGameObjID = StringToGUID(string(_node->first_attribute("rigidbodycomponent")->value()));
	RigidBodyComponent* rigidbody = _scene->GetGameObject(rbGameObjID)->GetComponent<RigidBodyComponent>();

	return ComponentFactory::MakeCircleColliderComponent(radius, trans, rigidbody);
}

inline IComponent * BuildBoxColliderComponent()
{
	float width = (float)atof(_node->first_attribute("width")->value());
	float height = (float)atof(_node->first_attribute("height")->value());

	GUID transGameObjID = StringToGUID(string(_node->first_attribute("transformcomponent")->value()));
	TransformComponent* trans = _scene->GetGameObject(transGameObjID)->GetComponent<TransformComponent>();

	GUID rbGameObjID = StringToGUID(string(_node->first_attribute("rigidbodycomponent")->value()));
	RigidBodyComponent* rigidbody = _scene->GetGameObject(rbGameObjID)->GetComponent<RigidBodyComponent>();

	return ComponentFactory::MakeBoxCollider(width, height, trans, rigidbody);
}
