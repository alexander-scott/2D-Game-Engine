#pragma once

#include <string>
#include <map>

#include "Consts.h"
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

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

	virtual xml_node<>* SaveComponent(xml_document<>* doc) = 0;
	virtual int GetEditorFieldCount() = 0;
	virtual InspectorField* GetEditorFields() = 0;
	virtual void SetEditorFieldValue(int fieldIndex, const char* value) = 0;

protected:
	string			_type;
	bool			_active;
};