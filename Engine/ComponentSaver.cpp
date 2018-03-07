#include "ComponentSaver.h"

IComponent* _component;
xml_document<>* _doc;
xml_node<>* _componentNode;

// Define component functions here
inline void SaveTransformComponent();

ComponentSaver::ComponentSaver(xml_document<>* doc)
{
	_doc = doc;

	// Insert defined functions into the map
	functionMapper.Insert("TransformComponent", SaveTransformComponent);
}

xml_node<>* ComponentSaver::SaveComponent(IComponent * component)
{
	_component = component;

	_componentNode = _doc->allocate_node(node_element, "Component");
	_componentNode->append_attribute(_doc->allocate_attribute("type", _doc->allocate_string(_component->GetType().c_str())));

	// Call the function listed in the function mapper
	functionMapper.CallFunction<void>(component->GetType());

	return _componentNode;
}

void SaveTransformComponent()
{
	TransformComponent* transform = dynamic_cast<TransformComponent*>(_component);

	_componentNode->append_attribute(_doc->allocate_attribute("xpos", _doc->allocate_string(to_string(transform->GetLocalPosition().x).c_str())));
	_componentNode->append_attribute(_doc->allocate_attribute("ypos", _doc->allocate_string(to_string(transform->GetLocalPosition().y).c_str())));
	_componentNode->append_attribute(_doc->allocate_attribute("rotation", _doc->allocate_string(to_string(transform->GetLocalRotation()).c_str())));
	_componentNode->append_attribute(_doc->allocate_attribute("scale", _doc->allocate_string(to_string(transform->GetLocalScale()).c_str())));
}