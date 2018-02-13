#include "ComponentBuilder.h"

#include <unordered_map>
#include <typeindex>

// every function pointer will be stored as this type
typedef void(*voidFunctionType)(void);

struct FunctionMapper 
{
	std::map<std::string, std::pair<voidFunctionType, std::type_index>> m1;

	template<typename T>
	void Insert(std::string s1, T f1) 
	{
		auto tt = std::type_index(typeid(f1));
		m1.insert(std::make_pair(s1,
			std::make_pair((voidFunctionType)f1, tt)));
	}

	template<typename T, typename... Args>
	T CallFunction(std::string s1, Args&&... args) 
	{
		auto mapIter = m1.find(s1);
		/*chk if not end*/
		auto mapVal = mapIter->second;

		// auto typeCastedFun = reinterpret_cast<T(*)(Args ...)>(mapVal.first); 
		auto typeCastedFun = (T(*)(Args ...))(mapVal.first);

		//compare the types is equal or not
		assert(mapVal.second == std::type_index(typeid(typeCastedFun)));
		return typeCastedFun(std::forward<Args>(args)...);
	}
};

// Define component functions here
inline TransformComponent * BuildTransformComponent(xml_node<> * node);

// Map component functions to strings here
FunctionMapper GetFunctionMapper()
{
	FunctionMapper functionMapper;
	functionMapper.Insert("TransformComponent", BuildTransformComponent);
	return functionMapper;
}

static std::unordered_map<std::string, ComponentType> ComponentMap
{
	{ "TransformComponent", ComponentType::eTransformComponent }
};

IComponent * ComponentBuilder::BuildComponent(xml_node<>* node)
{
	std::string componentType = string(node->first_attribute("type")->value());

	// BROKEN
	//return GetFunctionMapper().CallFunction<IComponent*>(componentType, node);

	// Check component type exists
	auto iterator = ComponentMap.find(componentType);
	if (iterator == ComponentMap.end())
		throw std::exception("Unable to find component type");

	switch (ComponentMap[componentType])
	{
		case ComponentType::eTransformComponent:
		{
			return BuildTransformComponent(node);
		}
	}

	throw std::exception("CODE SHOULD NEVER REACH HERE");
	return nullptr;
}

TransformComponent * BuildTransformComponent(xml_node<>* node)
{
	float xPos = (float)atof(node->first_attribute("xpos")->value());
	float yPos = -(float)atof(node->first_attribute("ypos")->value());
	float rot = (float)atof(node->first_attribute("rotation")->value());
	float scale = (float)atof(node->first_attribute("scale")->value());

	return ComponentFactory::MakeTransformComponent(Vec2(xPos, yPos), rot, scale);
}