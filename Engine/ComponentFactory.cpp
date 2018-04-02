#include "ComponentFactory.h"

TransformComponent * ComponentFactory::MakeTransformComponent(Vec2 position, float rotation, float scale)
{
	TransformComponent * transform = new TransformComponent(position, rotation, scale);

	return transform;
}

SpriteRendererComponent * ComponentFactory::MakeSpriteRendererComponent(Vec2 position, float rotation, float scale, RECT* rect, Vec2 offset, string text, string name, string animation) {
	SpriteRendererComponent * sprite = new SpriteRendererComponent(position, rotation, scale, rect, offset, text, name, animation);
	return sprite;
}

TextRendererComponent * ComponentFactory::MakeTextRendererComponent(Vec2 position, float rotation, float scale, RECT * rect, Vec2 offset, std::string text, float4 * rgb3)
{
	TextRendererComponent * textComponent = new TextRendererComponent(position, rotation, scale, rect, offset, text, rgb3);
	return textComponent;
}
