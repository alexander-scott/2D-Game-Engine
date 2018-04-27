#include "MPhantomComponent.h"



MPhantomComponent::MPhantomComponent() : IComponent("MPhantomComponent")
{
	_goesBot = false;
	_goesTop = false;
	_goesLeft = true;
	_goesRight = false;
}


MPhantomComponent::~MPhantomComponent()
{
}

void MPhantomComponent::Update(float deltaTime)
{

	if ((_transformComponent->GetWorldPosition().x < -10.0f) ){
		_transformComponent->SetWorldPosition(Vec2( 805.0f, (float)(rand() % 600)));
	}
	if ((_transformComponent->GetWorldPosition().y < 0.0f)) {
		_transformComponent->SetWorldPosition(Vec2(500.0f, (float)(rand() % 100) + 800.0f));
	}
	_goesBot = rand() % 2;
	_goesTop = rand() % 2;
	_goesLeft = rand() % 2;
	_goesRight = rand() % 2;

	if (_goesRight) {
		_spriteAnimatedComponent->SetAnimation("GoesRight");
		_transformComponent->SetWorldPosition(Vec2(_transformComponent->GetWorldPosition().x + 2.5f, _transformComponent->GetWorldPosition().y));
	}
	if (_goesLeft) {
		_spriteAnimatedComponent->SetAnimation("GoesLeft");
		_transformComponent->SetWorldPosition(Vec2(_transformComponent->GetWorldPosition().x - 5.0f, _transformComponent->GetWorldPosition().y));
	}
	if (_goesTop) {
		_spriteAnimatedComponent->SetAnimation("GoesTop");
		_transformComponent->SetWorldPosition(Vec2(_transformComponent->GetWorldPosition().x, _transformComponent->GetWorldPosition().y - 2.5f));
	}
	if (_goesBot) {
		_spriteAnimatedComponent->SetAnimation("GoesBot");
		_transformComponent->SetWorldPosition(Vec2(_transformComponent->GetWorldPosition().x, _transformComponent->GetWorldPosition().y + 2.5f));
	}
}
