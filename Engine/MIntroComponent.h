#pragma once
#include "IComponent.h"
#include "IMessageableComponent.h"

#include "SpriteAnimatedComponent.h"
#include "TransformComponent.h"
#include "InputHandlerToGameObjectMessage.h"

class MIntroComponent : public IComponent, public IMessageableComponent
{
public:
	MIntroComponent();
	~MIntroComponent();

	virtual void RecieveMessage(IComponentMessage& msg) override;

	void SetDependencies(TransformComponent *transformComponent, SpriteAnimatedComponent * sprite) {
		_transformComponent = transformComponent;
		_spriteAnimatedComponent = sprite;
	}

private:
	TransformComponent *_transformComponent;
	SpriteAnimatedComponent * _spriteAnimatedComponent;

};

