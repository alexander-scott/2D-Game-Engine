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

			float playerDiff = std::abs(_player->GetTransform()->GetWorldPosition().y - MOVEMENT_ZONE_HEIGHT) * 3;
			_platformManager->GetTransform()->SetWorldPosition(Vec2(_platformManager->GetTransform()->GetWorldPosition().x, _platformStartHeight + playerDiff));
		}
	}
	else
	{
		_platformsMoving = false;
		_platformManager->GetTransform()->SetChanged(false);
	}

	// Remove bottom platforms
	for (int i = 0; i < (int)_platforms.size(); i++)
	{
		if (_platforms[i].Transform->GetWorldPosition().y > SCREEN_HEIGHT)
		{
			_platformManager->ReturnPlatformToPool(_platforms[i]);
			_platforms.erase(_platforms.begin() + i);
		}
	}

	// Add new platforms
	// If the most recent platform added is currently on screen then add another one above it
	if (_platforms[_platforms.size() - 1].Transform->GetWorldPosition().y > 0)
	{
		SpawnNewPlatform();
	}
}

void AlexGameManagerComponent::Start()
{
	// Spawn start platform
	SpawnNewPlatform(Vec2(128, 550));

	// Spawn 10 additional platforms
	for (int i = 0; i < 10; i++)
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
	_platforms.push_back(platform);
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