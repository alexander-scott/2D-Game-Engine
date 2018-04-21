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

	//if ((_transformComponent->GetWorldPosition().x < 0) || (_transformComponent->GetWorldPosition().y > 0)){
	//	//float x = (float)(rand() % 100) + 600;
	//	//float y = (float)(rand() % 100) + 800;
	//	//_transformComponent->SetWorldPosition(Vec2(x, y));
	//	_transformComponent->SetWorldPosition(Vec2(600.0f, 800.0f));
	//}
	_goesBot = rand() % 2;
	_goesTop = rand() % 2;
	_goesLeft = rand() % 2;
	_goesRight = rand() % 2;

	if (_goesRight) {
		_transformComponent->SetWorldPosition(Vec2(_transformComponent->GetWorldPosition().x + 5.0f, _transformComponent->GetWorldPosition().y));
	}
	if (_goesLeft) {
		_transformComponent->SetWorldPosition(Vec2(_transformComponent->GetWorldPosition().x - 6.0f, _transformComponent->GetWorldPosition().y));
	}
	if (_goesTop) {
		_transformComponent->SetWorldPosition(Vec2(_transformComponent->GetWorldPosition().x, _transformComponent->GetWorldPosition().y - 6.0f));
	}
	if (_goesBot) {
		_transformComponent->SetWorldPosition(Vec2(_transformComponent->GetWorldPosition().x, _transformComponent->GetWorldPosition().y + 5.0f));
	}
}
