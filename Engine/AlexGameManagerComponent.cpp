#include "AlexGameManagerComponent.h"

AlexGameManagerComponent::AlexGameManagerComponent()
	: IComponent("AlexGameManagerComponent")
{
	_minDistBetweenPlatforms = 50;
	_platformsMoving = false;
}

AlexGameManagerComponent::~AlexGameManagerComponent()
{
}

void AlexGameManagerComponent::Update(float deltaTime)
{
	if (_player->GetRigidbody()->GetVelocity().y < 0) // If the player is moving upward
	{
		if (_player->GetTransform()->GetWorldPosition().y < 300) // If the player is within the zone where platform movement occurs
		{
			if (!_platformsMoving)
			{
				_platformsMoving = true;
				_platformStartHeight = _platformManager->GetTransform()->GetWorldPosition().y;
			}

			float playerDiff = std::abs(_player->GetTransform()->GetWorldPosition().y - 300);
			_platformManager->GetTransform()->SetWorldPosition(Vec2(_platformManager->GetTransform()->GetWorldPosition().x, _platformStartHeight + playerDiff));
		}
	}
	else
	{
		_platformsMoving = false;
	}

	//_platformManager->GetTransform()->SetWorldPosition(Vec2(_platformManager->GetTransform()->GetWorldPosition().x, _platformManager->GetTransform()->GetWorldPosition().y + 0.1f));
}

void AlexGameManagerComponent::Start()
{
	auto platform = _platformManager->GetNewPlatformFromPool();
	platform->GetComponent<TransformComponent>()->SetLocalPosition(Vec2(128, 550));

	auto platform2 = _platformManager->GetNewPlatformFromPool();
	platform2->GetComponent<TransformComponent>()->SetLocalPosition(Vec2(200, 400));

	auto platform3 = _platformManager->GetNewPlatformFromPool();
	platform3->GetComponent<TransformComponent>()->SetLocalPosition(Vec2(272, 250));
}

Vec2 GetNewPositionForPlatform()
{
	return Vec2();
}