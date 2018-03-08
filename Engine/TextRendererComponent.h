#pragma once
#include "IRenderableComponent.h"

class TextRendererComponent : public IRenderableComponent
{
public:
	TextRendererComponent();
	~TextRendererComponent();

	void SetText(std::string text);
	std::string GetText();
	
	void SetRgb(float* rgb);
	float* GetRbg();

private :
	std::string _text;
	float * _rgb;
};

