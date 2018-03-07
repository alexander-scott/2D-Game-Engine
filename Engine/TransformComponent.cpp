#include "TransformComponent.h"

TransformComponent::TransformComponent(Vec2 localPosition, float localRotation, float localScale)
	: IComponent("TransformComponent")
{
	_hasChanged = false;

	_localPosition = localPosition;
	_localScale = localScale;
	_localRotation = localRotation;

	_parent = nullptr;
}

void TransformComponent::SetLocalPosition(Vec2 position)
{
	if (position.x != _localPosition.x || position.y != _localPosition.y)
	{
		_hasChanged = true;
	}

	_localPosition = position;
}

void TransformComponent::SetLocalScale(float scale)
{
	if (scale != _localScale)
	{
		_hasChanged = true;
	}

	_localScale = scale;
}

void TransformComponent::SetLocalRotation(float rot)
{
	if (rot != _localRotation)
	{
		_hasChanged = true;
	}

	_localRotation = rot;
}

float TransformComponent::GetLocalRotation() const
{
	return _localRotation;
}

float TransformComponent::GetLocalScale() const
{
	return _localScale;
}

Vec2 TransformComponent::GetLocalPosition() const
{
	return _localPosition;
}

void TransformComponent::SetWorldPosition(Vec2 position)
{
	// Calculate the new position
	Vec2 newPos;
	if (_parent != nullptr)
		newPos = position - _parent->GetWorldPosition();
	else
		newPos = position;

	// If the new position is different to the old postion set hasChanged to true
	if (newPos.x != _localPosition.x || newPos.y != _localPosition.y)
		_hasChanged = true;

	_localPosition = newPos;
}

void TransformComponent::SetWorldScale(float scale)
{
	float newScale;
	if (_parent != nullptr)
		newScale = (_parent->GetWorldScale() + scale) / 2;
	else
		newScale = scale;

	if (newScale != _localScale)
		_hasChanged = true;

	_localScale = newScale;
}

void TransformComponent::SetWorldRotation(float rot)
{
	float newRot;
	if (_parent != nullptr)
		newRot = rot - _parent->GetWorldRotation();
	else
		newRot = rot;

	if (newRot != _localRotation)
		_hasChanged = true;

	_localRotation = newRot;
}

float TransformComponent::GetWorldRotation() const
{
	if (_parent != nullptr)
		return _localRotation + _parent->GetWorldRotation();
	else
		return _localRotation;
}

float TransformComponent::GetWorldScale() const
{
	if (_parent != nullptr)
		return _localScale * _parent->GetWorldScale();
	else
		return _localScale;
}

Vec2 TransformComponent::GetWorldPosition() const
{
	if (_parent != nullptr)
		return _localPosition + _parent->GetWorldPosition();
	else
		return _localPosition;
}

TransformComponent * ComponentFactory::MakeTransformComponent(Vec2 position, float rotation, float scale)
{
	TransformComponent * transform = new TransformComponent(position, rotation, scale);

	return transform;
}

map<string, string> TransformComponent::ExtractComponent()
{
	map<string, string> returnMap;
	returnMap.insert(std::make_pair(string("type"), string("TransformComponent")));

	returnMap.insert(std::make_pair(string("xpos"), to_string(GetLocalPosition().x)));
	returnMap.insert(std::make_pair(string("ypos"), to_string(GetLocalPosition().y)));
	returnMap.insert(std::make_pair(string("rotation"), to_string(GetLocalRotation())));
	returnMap.insert(std::make_pair(string("scale"), to_string(GetLocalScale())));

	return returnMap;
}

IComponent* TransformComponent::BuildComponent(xml_node<>* node)
{
	float xPos = (float)atof(node->first_attribute("xpos")->value());
	float yPos = -(float)atof(node->first_attribute("ypos")->value());
	float rot = (float)atof(node->first_attribute("rotation")->value());
	float scale = (float)atof(node->first_attribute("scale")->value());

	return ComponentFactory::MakeTransformComponent(Vec2(xPos, yPos), rot, scale);
}

xml_node<>* TransformComponent::SaveComponent(xml_document<>* doc)
{
	TransformComponent* transform = dynamic_cast<TransformComponent*>(this);
	auto componentNode = doc->allocate_node(node_element, "Component");

	componentNode->append_attribute(doc->allocate_attribute("xpos", doc->allocate_string(to_string(transform->GetLocalPosition().x).c_str())));
	componentNode->append_attribute(doc->allocate_attribute("ypos", doc->allocate_string(to_string(transform->GetLocalPosition().y).c_str())));
	componentNode->append_attribute(doc->allocate_attribute("rotation", doc->allocate_string(to_string(transform->GetLocalRotation()).c_str())));
	componentNode->append_attribute(doc->allocate_attribute("scale", doc->allocate_string(to_string(transform->GetLocalScale()).c_str())));

	return componentNode;
}

int TransformComponent::GetEditorFieldCount()
{
	return 4;
}

InspectorField* TransformComponent::GetEditorFields()
{
	auto inspectorFields = new InspectorField[4];

	inspectorFields[0].FieldName = "XPos";
	inspectorFields[0].FieldType = (int)EditorFieldTypes::eFloat;
	char* xPosValue = new char[to_string(GetLocalPosition().x).length() + 1];
	strcpy_s(xPosValue, to_string(GetLocalPosition().x).length() + 1, to_string(GetLocalPosition().x).c_str());
	inspectorFields[0].FieldValue = xPosValue;

	inspectorFields[1].FieldName = "YPos";
	inspectorFields[1].FieldType = (int)EditorFieldTypes::eFloat;
	char* yPosValue = new char[to_string(GetLocalPosition().y).length() + 1];
	strcpy_s(yPosValue, to_string(GetLocalPosition().y).length() + 1, to_string(GetLocalPosition().y).c_str());
	inspectorFields[1].FieldValue = yPosValue;

	inspectorFields[2].FieldName = "Rotation";
	inspectorFields[2].FieldType = (int)EditorFieldTypes::eFloat;
	char* rotationValue = new char[to_string(GetLocalRotation()).length() + 1];
	strcpy_s(rotationValue, to_string(GetLocalRotation()).length() + 1, to_string(GetLocalRotation()).c_str());
	inspectorFields[2].FieldValue = rotationValue;

	inspectorFields[3].FieldName = "Scale";
	inspectorFields[3].FieldType = (int)EditorFieldTypes::eFloat;
	char* scaleValue = new char[to_string(GetLocalScale()).length() + 1];
	strcpy_s(scaleValue, to_string(GetLocalScale()).length() + 1, to_string(GetLocalScale()).c_str());
	inspectorFields[3].FieldValue = scaleValue;

	return inspectorFields;
}