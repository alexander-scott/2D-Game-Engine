#include "AlexGameManagerComponent.h"

AlexGameManagerComponent::AlexGameManagerComponent()
	: IComponent("AlexGameManagerComponent")
{
	_currentMaxDistBetweenPlatforms = MIN_HEIGHT_BETWEEN_PLATFORMS;
	_widthBoundaries = WIDTH_BOUNDARIES;
	_platformsMoving = false;

	_score = 0;

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
			if (!_platformsMoving) // If the platforms aren't already moving, reset the variables
			{
				_platformsMoving = true;
				_platformStartHeight = _platformManager->GetTransform()->GetWorldPosition().y;
				_playerHeight = MOVEMENT_ZONE_HEIGHT;
			}

			// Calculate the height that the player would be at based on its current velocity
			_playerHeight -= _player->GetRigidbody()->GetVelocity().y * deltaTime;
			// Limit the players actual height however
			_player->GetTransform()->SetWorldPosition(Vec2(_player->GetTransform()->GetWorldPosition().x, MOVEMENT_ZONE_HEIGHT));

			// Move the platform manager to simulate the player moving even though the player is static at this point
			float playerDiff = std::abs(_playerHeight - MOVEMENT_ZONE_HEIGHT) * 3;
			_platformManager->GetTransform()->SetWorldPosition(
				Vec2(_platformManager->GetTransform()->GetWorldPosition().x, _platformStartHeight + playerDiff));
		}
	}
	else // Else the player is movement downwards. Wait for a bounce
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

	AddGameProgression();
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

void AlexGameManagerComponent::AddGameProgression()
{
	_score = (int)_platformManager->GetTransform()->GetWorldPosition().y;

	double percentToTermScore = ((double)_score / (double)TERMINAL_SCORE);
	percentToTermScore *= 100;

	if (percentToTermScore > 100)
		percentToTermScore = 100;

	if (_widthBoundaries > 0)
	{		
		_widthBoundaries = WIDTH_BOUNDARIES - (2 * (int)percentToTermScore);
	}

	if (_currentMaxDistBetweenPlatforms < MAX_HEIGHT_BETWEEN_PLATFORMS)
	{
		_currentMaxDistBetweenPlatforms = MIN_HEIGHT_BETWEEN_PLATFORMS +
			(((std::abs(MAX_HEIGHT_BETWEEN_PLATFORMS - MIN_HEIGHT_BETWEEN_PLATFORMS) / 100) * (int)percentToTermScore));
	}
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