#pragma once

#include <string>
#include <map>

#include "Consts.h"

using namespace std;

class IComponent
{
public:
	IComponent(string componentType) : _type(componentType) 
	{
		_active = true;
	}
	
	virtual string GetType() { return _type; }

	void SetActive(bool active) { _active = active; }
	bool GetActive() { return _active; }

	virtual map<string, string> ExtractComponent() = 0;

protected:
	string		_type;
	bool			_active;
};