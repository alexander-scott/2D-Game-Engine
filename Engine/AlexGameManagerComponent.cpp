#include "AlexGameManagerComponent.h"

AlexGameManagerComponent::AlexGameManagerComponent()
	: IComponent("AlexGameManagerComponent")
{
	_currentMaxDistBetweenPlatforms = MIN_HEIGHT_BETWEEN_PLATFORMS;
	_widthBoundaries = 200;
	_platformsMoving = false;

	//_previousSpawnPos = _platformManager->GetTransform()->GetWorldPosition().y +
}

AlexGameManagerComponent::~AlexGameManagerComponent()
{
}

void AlexGameManagerComponent::Update(float deltaTime)
{
	if (_player->GetRigidbody()->GetVelocity().y < 0) // If the player is moving upward
	{
		if (_player->GetTransform()->GetWorldPosition().y < MOVEMENT_ZONE_HEIGHT) // If the player is within the zone where platform movement occurs
		{
			if (!_platformsMoving)
			{
				_platformsMoving = true;
				_platformStartHeight = _platformManager->GetTransform()->GetWorldPosition().y;
			}

			float playerDiff = std::abs(_player->GetTransform()->GetWorldPosition().y - MOVEMENT_ZONE_HEIGHT);
			_platformManager->GetTransform()->SetWorldPosition(Vec2(_platformManager->GetTransform()->GetWorldPosition().x, _platformStartHeight + playerDiff));
		}
	}
	else
	{
		_platformsMoving = false;
		_platformManager->GetTransform()->SetChanged(false);
	}

	//_platformManager->GetTransform()->SetWorldPosition(Vec2(_platformManager->GetTransform()->GetWorldPosition().x, _platformManager->GetTransform()->GetWorldPosition().y + 0.1f));
}

void AlexGameManagerComponent::Start()
{
	/*auto platform = _platformManager->GetNewPlatformFromPool();
	platform.GameObject->GetComponent<TransformComponent>()->SetLocalPosition(Vec2(128, 550));

	auto platform2 = _platformManager->GetNewPlatformFromPool();
	platform2.GameObject->GetComponent<TransformComponent>()->SetLocalPosition(Vec2(200, 400));

	auto platform3 = _platformManager->GetNewPlatformFromPool();
	platform3.GameObject->GetComponent<TransformComponent>()->SetLocalPosition(Vec2(272, 250));*/

	SpawnNewPlatform(Vec2(128, 550));

	for (int i = 0; i < 20; i++)
	{
		SpawnNewPlatform();
	}
}

void AlexGameManagerComponent::SpawnNewPlatform()
{
	Vec2 pos = GetNewPositionForPlatform();
	SpawnNewPlatform(pos);
}

void AlexGameManagerComponent::SpawnNewPlatform(Vec2 position)
{
	auto platform = _platformManager->GetNewPlatformFromPool();
	platform.GameObject->GetComponent<TransformComponent>()->SetLocalPosition(position);
	_previousSpawnPos = position;
}

Vec2 AlexGameManagerComponent::GetNewPositionForPlatform()
{
	int xLeftBoundary = 0 + _widthBoundaries;
	int xRightBoundary = SCREEN_WIDTH - _widthBoundaries;

	std::uniform_int_distribution<int> xPosGeneration(xLeftBoundary, xRightBoundary);
	int xPos = xPosGeneration(_randNumGenerator);

	std::uniform_int_distribution<int> yPosGeneration(MIN_HEIGHT_BETWEEN_PLATFORMS, _currentMaxDistBetweenPlatforms);
	int yPos = yPosGeneration(_randNumGenerator);

	return Vec2((float)xPos, _previousSpawnPos.y - (float)yPos);
}