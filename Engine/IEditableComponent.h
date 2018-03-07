#pragma once

#include "Consts.h"

class IEditableComponent
{
public:
	virtual int GetEditorFieldCount() = 0;
	virtual InspectorField* GetEditorFields() = 0;
	virtual void SetEditorFieldValue(int fieldIndex, const char* value) = 0;
};