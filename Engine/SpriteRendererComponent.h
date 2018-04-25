#pragma once
#include "IRenderableComponent.h"
#include "ISpriteComponent.h"

class SpriteRendererComponent : /*public IRenderableComponent,*/ public ISpriteComponent, public IComponent
{
public:
	SpriteRendererComponent();
	SpriteRendererComponent(RECT *rect, Vec2 offset, string text, string name);

	~SpriteRendererComponent();

	//void SetDependencies(TransformComponent* transform);

	void Draw(float deltaTime) override; //adds drawing data of this component to the message passed to the draw function

	// Added by Alex 18/04/18. This now takes into account rotations and scale and will return the centre point rather than the scaled/rotated top left point
	virtual Vec2 GetPosition() override;
	



};

