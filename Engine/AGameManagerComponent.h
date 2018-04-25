#pragma once

#include "IComponent.h"

#include "IUpdateableComponent.h"
#include "IStartableComponent.h"

#include "APlatformManagerComponent.h"
#include "AControllerComponent.h"
#include "TextRendererComponent.h"

#include <random>

class AGameManagerComponent : public IComponent, public IUpdateableComponent, public IStartableComponent
{
public:
	AGameManagerComponent();
	~AGameManagerComponent();

	void SetDependencies(AControllerComponent* player, APlatformManagerComponent* platformManager, TextRendererComponent* text)
	{
		_player = player; _platformManager = platformManager; _scoreText = text; 
	}

	virtual void Start() override;
	virtual void Update(float deltaTime) override;

private:
	Vec2 GetNewPositionForPlatform();
	void SpawnNewPlatform();
	void SpawnNewPlatform(Vec2 position);

	void AddGameProgression();

	AControllerComponent *		_player;
	APlatformManagerComponent *	_platformManager;
	TextRendererComponent *			_scoreText;

	int								_score;
	const int						TERMINAL_SCORE = 10000;

	bool							_gameOver;

	// Platform movement
	bool							_platformsMoving;
	float							_platformStartHeight;
	float							_playerHeight;
	const float						MOVEMENT_ZONE_HEIGHT = 300;

	// Platform spawning
	int								_currentMaxDistBetweenPlatforms;
	int								_widthBoundaries;
	Vec2							_previousSpawnPos;
	std::default_random_engine		_randNumGenerator;
	const int						WIDTH_BOUNDARIES = 200;
	const int						MIN_HEIGHT_BETWEEN_PLATFORMS = 50;
	const int						MAX_HEIGHT_BETWEEN_PLATFORMS = 150;

	std::vector<APlatformManagerComponent::Platform> _platforms;
};