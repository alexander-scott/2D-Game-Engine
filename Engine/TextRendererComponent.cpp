#include "TextRendererComponent.h"



TextRendererComponent::TextRendererComponent() : IComponent("TextRendererComponent")
{
}

TextRendererComponent::TextRendererComponent(Vec2 position, float rotation, float scale, RECT *rect, Vec2 offset, std::string text, float* rgb) : IComponent("TextRendererComponent")
{
	SetPosition(position);
	SetRotation(rotation);
	SetScale(scale);
	SetRect(rect);
	SetOffset(offset);
	_text = text;
	_rgb = rgb;


}


TextRendererComponent::~TextRendererComponent()
{
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

void TextRendererComponent::Draw(float deltaTime)
{
	//TODO
}
