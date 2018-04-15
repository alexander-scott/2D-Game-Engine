#include "TextRendererComponent.h"




TextRendererComponent::TextRendererComponent(RECT *rect, Vec2 offset, std::string text, float* rgb) : IComponent("TextRendererComponent")
{
	Type = eText;
	SetRect(rect);
	SetOffset(offset);
	_text = text;
	SetRgb(rgb);
}

TextRendererComponent::TextRendererComponent(RECT * rect, Vec2 offset, std::string text, float4 * rgb3) : IComponent("TextRendererComponent")
{
	Type = eText;
	SetRect(rect);
	SetOffset(offset);
	_text = text;
	_rgb3 = rgb3;
}


TextRendererComponent::~TextRendererComponent()
{
}

void TextRendererComponent::SetDependencies(TransformComponent * transform)
{
	_transformComponent = transform;
}

void TextRendererComponent::SetText(std::string text)
{
	_text = text;
}

std::string TextRendererComponent::GetText()
{
	return _text;
}

void TextRendererComponent::SetRgb(float * rgb)
{
	_rgb = rgb;
}

float * TextRendererComponent::GetRbg()
{	
	return _rgb;
}

void TextRendererComponent::SetRgb3(float4 * rgb3)
{
	_rgb3 = rgb3;
}

float4 * TextRendererComponent::GetRbg3()
{
	return _rgb3;
}

void TextRendererComponent::Draw(float deltaTime)
{
	//TODO - delete
}
