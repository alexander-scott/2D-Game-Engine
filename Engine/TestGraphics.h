#pragma once

#include "IGraphics.h"

class TestGraphics : public IGraphics
{
public:
	TestGraphics() : IGraphics() { }

	virtual void Initalise(class HWNDKey& key) override;
	virtual void Destroy() override;

	virtual void EndFrame() override;
	virtual void BeginFrame() override;

	virtual void PreloadTextures() override;

	virtual void DrawSprite(std::string name, Vec2 pos, RECT* rect, float rot, float scale, Vec2 offset) override;

	virtual void DrawText(std::string text, Vec2 pos, float rot, float* rgb, float scale, Vec2 offset) override;

	virtual void DrawLine(Vec2 v1, Vec2 v2) override;
};