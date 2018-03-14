#include "ComponentBuilder.h"
#include "Scene.h"

xml_node<>* _node;
shared_ptr<Scene> _scene;

// Define component build functions here
inline IComponent * BuildTransformComponent();
inline IComponent * BuildRigidbodyComponent();
inline IComponent * BuildCircleColliderComponent();
inline IComponent * BuildBoxColliderComponent();

map<string, GUID>* depdendecies;
IComponent * dependencyComponent;

// Define fetch dependency functions here
inline void FetchCircleColliderDependencies();
inline void FetchBoxColliderDependencies();

ComponentBuilder::ComponentBuilder(shared_ptr<Scene> scene)
{
	_scene = scene;

	// Insert build functions here
	_buildMapper.Insert("TransformComponent", BuildTransformComponent);
	_buildMapper.Insert("RigidbodyComponent", BuildRigidbodyComponent);
	_buildMapper.Insert("CircleColliderComponent", BuildCircleColliderComponent);
	_buildMapper.Insert("BoxColliderComponent", BuildBoxColliderComponent);

	// Insert fetch dependency functions here
	_dependencyBuildMapper.Insert("CircleColliderComponent", FetchCircleColliderDependencies);
	_dependencyBuildMapper.Insert("BoxColliderComponent", FetchBoxColliderDependencies);
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

#pragma region Build functions

IComponent * ComponentBuilder::BuildComponent(xml_node<>* node)
{
	_node = node;

	// Call the function listed in the function mapper
	return _buildMapper.CallFunction<IComponent*>(string(node->first_attribute("type")->value()));
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

IComponent * BuildCircleColliderComponent()
{
	float radius = (float)atof(_node->first_attribute("radius")->value());

	return ComponentFactory::MakeCircleColliderComponent(radius);
}

IComponent * BuildBoxColliderComponent()
{
	float width = (float)atof(_node->first_attribute("width")->value());
	float height = (float)atof(_node->first_attribute("height")->value());

	return ComponentFactory::MakeBoxCollider(width, height);
}

#pragma endregion

#pragma region Fetch dependency functions

void ComponentBuilder::BuildComponentDependecies(IComponent * component, map<string, GUID>* dependecies)
{
	depdendecies = dependecies;
	dependencyComponent = component;

	// Call the function listed in the function mapper
	_dependencyBuildMapper.CallFunction<void>(component->GetType());
}

void FetchCircleColliderDependencies()
{
	CircleColliderComponent* collider = static_cast<CircleColliderComponent*>(dependencyComponent);

	TransformComponent* transform;
	RigidBodyComponent* rigidbody;

	map<string, GUID>::iterator it;
	for (it = depdendecies->begin(); it != depdendecies->end(); it++)
	{
		if (it->first == "transformcomponent")
		{
			transform = _scene->GetGameObject(it->second)->GetComponent<TransformComponent>();
		}
		else if (it->first == "rigidbodycomponent")
		{
			rigidbody = _scene->GetGameObject(it->second)->GetComponent<RigidBodyComponent>();
		}
	}

	collider->SetDependencies(transform, rigidbody);
}

void FetchBoxColliderDependencies()
{
	BoxColliderComponent* collider = static_cast<BoxColliderComponent*>(dependencyComponent);

	TransformComponent* transform;
	RigidBodyComponent* rigidbody;

	map<string, GUID>::iterator it;
	for (it = depdendecies->begin(); it != depdendecies->end(); it++)
	{
		if (it->first == "transformcomponent")
		{
			transform = _scene->GetGameObject(it->second)->GetComponent<TransformComponent>();
		}
		else if (it->first == "rigidbodycomponent")
		{
			rigidbody = _scene->GetGameObject(it->second)->GetComponent<RigidBodyComponent>();
		}
	}

	collider->SetDependencies(transform, rigidbody);
}

#pragma endregion