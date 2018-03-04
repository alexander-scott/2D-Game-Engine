#pragma once

#include <string>
#include <map>

#include "Consts.h"

using namespace std;

class IComponent
{
public:
	IComponent(ComponentType componentType) : _type(componentType) 
	{
		_active = true;
	}
	
	virtual ComponentType GetType() { return _type; }

	void SetActive(bool active) { _active = active; }
	bool GetActive() { return _active; }

	virtual map<string, string> ExtractComponent() = 0;

protected:
	ComponentType	_type;
	bool			_active;
};