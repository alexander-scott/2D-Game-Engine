#include "ComponentSaver.h"

IComponent* _component;

// Define component functions here
inline map<string,string> SaveTransformComponent();

ComponentSaver::ComponentSaver()
{
	functionMapper.Insert(ComponentType::eTransformComponent, SaveTransformComponent);
}

map<string, string> ComponentSaver::SaveComponent(IComponent * component)
{
	_component = component;

	return functionMapper.CallFunction<map<string, string>>(_component->GetType());
}

map<string, string> SaveTransformComponent()
{
	// Call function in TransformComponent that returns a vector of type XMLNODE which contains a string name and value for every value
	return ComponentFactory::ExtractTransformComponent(static_cast<TransformComponent*>(_component));
}
