#include "TextRendererComponent.h"



TextRendererComponent::TextRendererComponent()
{
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
