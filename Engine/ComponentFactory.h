#pragma once

#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include "TextRendererComponent.h"

namespace ComponentFactory
{
	TransformComponent * MakeTransformComponent(Vec2 position, float rotation, float scale); //let this for now
	//in the future we will have to delete position, rotation and scale from sprite & text renderer components

	SpriteRendererComponent * MakeSpriteRendererComponent(Vec2 position, float rotation, float scale, RECT* rect, Vec2 offset, string name);
	TextRendererComponent * MakeTextRendererComponent(Vec2 position, float rotation, float scale, RECT *rect, Vec2 offset, std::string text, float* rgb);

}