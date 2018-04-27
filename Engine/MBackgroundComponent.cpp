#include "MBackgroundComponent.h"



MBackgroundComponent::MBackgroundComponent() : IComponent("MBackgroundComponent")
{
}


MBackgroundComponent::~MBackgroundComponent()
{
}

void MBackgroundComponent::Update(float deltaTime) {
	if (_transformComponent->GetWorldPosition().y < 0.0f)
		_transformComponent->SetWorldPosition(Vec2( (float)(rand() % 800), 615.0f));
	_transformComponent->SetWorldPosition(Vec2(_transformComponent->GetWorldPosition().x, _transformComponent->GetWorldPosition().y - 1.0f));
}