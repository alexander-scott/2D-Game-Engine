#pragma once
#include "IRenderableComponent.h"

class TextRendererComponent : public IRenderableComponent, public IComponent
{
public:
	TextRendererComponent();
	TextRendererComponent(Vec2 position, float rotation, float scale, RECT *rect, Vec2 offset, std::string text, float* rgb);
	~TextRendererComponent();

	void SetText(std::string text);
	std::string GetText();
	
	void SetRgb(float* rgb);
	float* GetRbg();

	void Draw(float deltaTime) override;

private :
	std::string _text;
	float * _rgb;
};

