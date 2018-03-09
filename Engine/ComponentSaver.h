#pragma once

#include "rapidxml.hpp"

#include "ComponentFactory.h"

#include <typeindex>

using namespace rapidxml;

// every function pointer will be stored as this type
typedef void(*voidFunctionType)(void);

class ComponentSaver
{
public:
	struct FunctionMapper
	{
		std::map<string, std::pair<voidFunctionType, std::type_index>> m1;

		template<typename T>
		void Insert(string s1, T f1)
		{
			auto tt = std::type_index(typeid(f1));
			m1.insert(std::make_pair(s1,
				std::make_pair((voidFunctionType)f1, tt)));
		}

		template<typename T, typename... Args>
		T CallFunction(string s1, Args&&... args)
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

	ComponentSaver(xml_document<>* doc);

	xml_node<>* SaveComponent(IComponent* component);

private:
	FunctionMapper functionMapper;
};