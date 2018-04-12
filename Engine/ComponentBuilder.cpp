#include "ComponentBuilder.h"
#include "Scene.h"

xml_node<>* _node;
shared_ptr<Scene> _scene;

map<string, GUID>* depdendecies;
IComponent * dependencyComponent;

#pragma region Core component function declarations

inline IComponent * BuildTransformComponent();

inline IComponent * BuildSpriteRendererComponent();
inline void FetchSpriteRendererDependencies();

inline IComponent * BuildTextRendererComponent();
inline void FetchTextRendererDependencies();

inline IComponent * BuildRigidbodyComponent();

inline IComponent * BuildCircleColliderComponent();
inline void FetchCircleColliderDependencies();

inline IComponent * BuildBoxColliderComponent();
inline void FetchBoxColliderDependencies();

#pragma endregion

#pragma region AlexGame component function declarations

inline IComponent * BuildPlayerController();
inline void FetchPlayerControllerDependencies();

#pragma endregion

ComponentBuilder::ComponentBuilder(shared_ptr<Scene> scene)
{
	_scene = scene;

#pragma region Core component function mapping

	_buildMapper.Insert("TransformComponent", BuildTransformComponent);

	_buildMapper.Insert("SpriteRendererComponent", BuildSpriteRendererComponent);
	_dependencyBuildMapper.Insert("SpriteRendererComponent", FetchSpriteRendererDependencies);

	_buildMapper.Insert("TextRendererComponent", BuildTextRendererComponent);
	_dependencyBuildMapper.Insert("TextRendererComponent", FetchTextRendererDependencies);

	_buildMapper.Insert("RigidbodyComponent", BuildRigidbodyComponent);

	_buildMapper.Insert("CircleColliderComponent", BuildCircleColliderComponent);
	_dependencyBuildMapper.Insert("CircleColliderComponent", FetchCircleColliderDependencies);

	_buildMapper.Insert("BoxColliderComponent", BuildBoxColliderComponent);
	_dependencyBuildMapper.Insert("BoxColliderComponent", FetchBoxColliderDependencies);

#pragma endregion

#pragma region AlexGame component function mapping

	_buildMapper.Insert("PlayerControllerComponent", BuildPlayerController);
	_dependencyBuildMapper.Insert("PlayerControllerComponent", FetchPlayerControllerDependencies);

#pragma endregion	

}

#pragma region Core component functions

IComponent * ComponentBuilder::BuildComponent(xml_node<>* node)
{
	_node = node;

	// Call the function listed in the function mapper
	return _buildMapper.CallFunction<IComponent*>(string(node->first_attribute("type")->value()));
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

IComponent * BuildSpriteRendererComponent()
{
	LONG rectTop = (LONG)atof(_node->first_attribute("rectTop")->value());
	LONG rectBottom = (LONG)atof(_node->first_attribute("rectBottom")->value());
	LONG rectLeft = (LONG)atof(_node->first_attribute("rectLeft")->value());
	LONG rectRight = (LONG)atof(_node->first_attribute("rectRight")->value());

	float offset1 = (float)atof(_node->first_attribute("offset1")->value());
	float offset2 = (float)atof(_node->first_attribute("offset2")->value());

	RECT *rect = new RECT(); rect->top = rectTop; rect->left = rectLeft; rect->right = rectRight; rect->bottom = rectBottom;
	Vec2 offset = Vec2(offset1, offset2);

	std::string text = (std::string)(_node->first_attribute("text")->value()); //path to texture "file"
	std::string name = (std::string)(_node->first_attribute("name")->value()); //name of the object (ex : PlayerGreen,etc.)
	std::string animation = (std::string)(_node->first_attribute("animation")->value()); //name of animation (ex : walk, crawl, etc)

	return ComponentFactory::MakeSpriteRendererComponent(rect, offset, text, name, animation);
}

IComponent * BuildTextRendererComponent()
{
	LONG rectTop = (LONG)atof(_node->first_attribute("rectTop")->value());
	LONG rectBottom = (LONG)atof(_node->first_attribute("rectBottom")->value());
	LONG rectLeft = (LONG)atof(_node->first_attribute("rectLeft")->value());
	LONG rectRight = (LONG)atof(_node->first_attribute("rectRight")->value());
	
	float offset1 = (float)atof(_node->first_attribute("offset1")->value());
	float offset2 = (float)atof(_node->first_attribute("offset2")->value());

	std::string text = (std::string)(_node->first_attribute("text")->value());
	RECT *rect = new RECT(); rect->top = rectTop; rect->left = rectLeft; rect->right = rectRight; rect->bottom = rectBottom; 
	Vec2 offset = Vec2(offset1, offset2); 
	
	float rgb1 = (float)atof(_node->first_attribute("rgb1")->value());
	float rgb2 = (float)atof(_node->first_attribute("rgb2")->value());
	float rgb3 = (float)atof(_node->first_attribute("rgb3")->value());
	float rgb4 = (float)atof(_node->first_attribute("rgb4")->value());

	float4 *_rgb3 = new float4(rgb1, rgb2, rgb3, rgb4);

	return ComponentFactory::MakeTextRendererComponent(rect, offset, text, _rgb3);
}

IComponent * BuildRigidbodyComponent()
{
	float staticF = (float)atof(_node->first_attribute("staticfriction")->value());
	float dynamicF = (float)atof(_node->first_attribute("dynamicfriction")->value());
	float restitution = (float)atof(_node->first_attribute("restitution")->value());
	float density = (float)atof(_node->first_attribute("density")->value());

	bool isStatic = false;
	if (bool(atoi(_node->first_attribute("static")->value())))
		isStatic = true;

	bool lockRotation = false;
	if (bool(atoi(_node->first_attribute("lockrotation")->value())))
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

void FetchSpriteRendererDependencies()
{
	SpriteRendererComponent* renderer = static_cast<SpriteRendererComponent*>(dependencyComponent);
	TransformComponent* transform;

	map<string, GUID>::iterator it;
	for (it = depdendecies->begin(); it != depdendecies->end(); it++)
	{
		if (it->first == "transformcomponent")
		{
			transform = _scene->GetGameObject(it->second)->GetComponent<TransformComponent>();
			break;
		}
	}

	renderer->SetDependencies(transform);
}

inline void FetchTextRendererDependencies()
{
	TextRendererComponent* renderer = static_cast<TextRendererComponent*>(dependencyComponent);
	TransformComponent* transform;

	map<string, GUID>::iterator it;
	for (it = depdendecies->begin(); it != depdendecies->end(); it++)
	{
		if (it->first == "transformcomponent")
		{
			transform = _scene->GetGameObject(it->second)->GetComponent<TransformComponent>();
			break;
		}
	}

	renderer->SetDependencies(transform);
}

#pragma endregion

#pragma region AlexGame component functions

IComponent * BuildPlayerController()
{
	return ComponentFactory::MakePlayerComponent();
}

void FetchPlayerControllerDependencies()
{
	PlayerControllerComponent* playerController = static_cast<PlayerControllerComponent*>(dependencyComponent);
	TransformComponent* transform;

	map<string, GUID>::iterator it;
	for (it = depdendecies->begin(); it != depdendecies->end(); it++)
	{
		if (it->first == "transformcomponent")
		{
			transform = _scene->GetGameObject(it->second)->GetComponent<TransformComponent>();
			break;
		}
	}

	playerController->SetDependencies(transform);
}

#pragma endregion