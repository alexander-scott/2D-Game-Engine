#include "ComponentSaver.h"

IComponent* _component;
xml_document<>* _doc;
xml_node<>* _componentNode;

// Define component functions here
inline void SaveTransformComponent();
inline void SaveRigidbodyComponent();
inline void SaveCircleColliderComponent();
inline void SaveBoxColliderComponent();

ComponentSaver::ComponentSaver(xml_document<>* doc)
{
	_doc = doc;

	// Insert defined functions into the map
	_functionMapper.Insert("TransformComponent", SaveTransformComponent);
	_functionMapper.Insert("RigidbodyComponent", SaveRigidbodyComponent);
}

xml_node<>* ComponentSaver::SaveComponent(IComponent * component)
{
	_component = component;

	_componentNode = _doc->allocate_node(node_element, "Component");
	_componentNode->append_attribute(_doc->allocate_attribute("type", _doc->allocate_string(_component->GetType().c_str())));

	// Call the function listed in the function mapper
	_functionMapper.CallFunction<void>(component->GetType());

	return _componentNode;
}

std::string GUIDToString(GUID *guid)
{
	char guid_string[37]; // 32 hex chars + 4 hyphens + null terminator
	snprintf(
		guid_string, sizeof(guid_string) / sizeof(guid_string[0]),
		"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		guid->Data1, guid->Data2, guid->Data3,
		guid->Data4[0], guid->Data4[1], guid->Data4[2],
		guid->Data4[3], guid->Data4[4], guid->Data4[5],
		guid->Data4[6], guid->Data4[7]);
	return guid_string;
}

void SaveTransformComponent()
{
	TransformComponent* transform = dynamic_cast<TransformComponent*>(_component);

	_componentNode->append_attribute(_doc->allocate_attribute("xpos", _doc->allocate_string(to_string(transform->GetLocalPosition().x).c_str())));
	_componentNode->append_attribute(_doc->allocate_attribute("ypos", _doc->allocate_string(to_string(transform->GetLocalPosition().y).c_str())));
	_componentNode->append_attribute(_doc->allocate_attribute("rotation", _doc->allocate_string(to_string(transform->GetLocalRotation()).c_str())));
	_componentNode->append_attribute(_doc->allocate_attribute("scale", _doc->allocate_string(to_string(transform->GetLocalScale()).c_str())));
}

inline void SaveRigidbodyComponent()
{
	RigidBodyComponent* rigidbody = dynamic_cast<RigidBodyComponent*>(_component);

	_componentNode->append_attribute(_doc->allocate_attribute("staticfriction", _doc->allocate_string(to_string(rigidbody->GetStaticFriction()).c_str())));
	_componentNode->append_attribute(_doc->allocate_attribute("dynamicfriction", _doc->allocate_string(to_string(rigidbody->GetDynamicFriction()).c_str())));
	_componentNode->append_attribute(_doc->allocate_attribute("restitution", _doc->allocate_string(to_string(rigidbody->GetRestitution()).c_str())));
	_componentNode->append_attribute(_doc->allocate_attribute("density", _doc->allocate_string(to_string(rigidbody->GetDensity()).c_str())));
	_componentNode->append_attribute(_doc->allocate_attribute("static", _doc->allocate_string(to_string(rigidbody->IsStatic()).c_str())));
	_componentNode->append_attribute(_doc->allocate_attribute("lockrotation", _doc->allocate_string(to_string(rigidbody->RotationLocked()).c_str())));
}

inline void SaveCircleColliderComponent()
{
	CircleColliderComponent* collider = dynamic_cast<CircleColliderComponent*>(_component);

	_componentNode->append_attribute(_doc->allocate_attribute("radius", _doc->allocate_string(to_string(collider->GetRadius()).c_str())));
	_componentNode->append_attribute(_doc->allocate_attribute("transformcomponent", _doc->allocate_string(GUIDToString(&collider->GetGameObjectID()).c_str())));
	_componentNode->append_attribute(_doc->allocate_attribute("rigidbodycomponent", _doc->allocate_string(GUIDToString(&collider->GetGameObjectID()).c_str())));
}

inline void SaveBoxColliderComponent()
{
	BoxColliderComponent* collider = dynamic_cast<BoxColliderComponent*>(_component);

	_componentNode->append_attribute(_doc->allocate_attribute("width", _doc->allocate_string(to_string(collider->GetWidth()).c_str())));
	_componentNode->append_attribute(_doc->allocate_attribute("height", _doc->allocate_string(to_string(collider->GetHeight()).c_str())));
	_componentNode->append_attribute(_doc->allocate_attribute("transformcomponent", _doc->allocate_string(GUIDToString(&collider->GetGameObjectID()).c_str())));
	_componentNode->append_attribute(_doc->allocate_attribute("rigidbodycomponent", _doc->allocate_string(GUIDToString(&collider->GetGameObjectID()).c_str())));
}