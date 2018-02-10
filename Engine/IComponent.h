#pragma once

#include <string>

#include "Consts.h"

using namespace std;

class IComponent
{
public:
	virtual ComponentType GetType() { return _type; }

	void SetActive(bool active) { _active = active; }
	bool GetActive() { return _active; }

protected:
	ComponentType	_type;
	bool			_active = true;
};