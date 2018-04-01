#pragma once
#include "IRenderableComponent.h"
#include <WindowsNumerics.h>
using namespace Windows::Foundation::Numerics;

class TextRendererComponent : public IRenderableComponent, public IComponent
{
public:
	//TextRendererComponent();
	TextRendererComponent(RECT *rect, Vec2 offset, std::string text, float* rgb);
	TextRendererComponent(RECT *rect, Vec2 offset, std::string text, float4* rgb);
	~TextRendererComponent();

	void SetDependencies(TransformComponent* transform);

	void SetText(std::string text);
	std::string GetText();
	
	void SetRgb(float* rgb);
	float* GetRbg();

	void SetRgb3(float4* rgb);
	float4* GetRbg3();

	void Draw(float deltaTime) override;

private :
	std::string _text;
	float * _rgb = nullptr;
	float4	*_rgb3 = nullptr;
	//float rgb1;

};

