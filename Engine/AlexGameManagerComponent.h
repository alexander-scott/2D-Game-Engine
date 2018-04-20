#pragma once

#include "IComponent.h"

#include "IUpdateableComponent.h"
#include "IStartableComponent.h"

#include "AlexPlatformManagerComponent.h"
#include "AlexControllerComponent.h"

#include <random>

class AlexGameManagerComponent : public IComponent, public IUpdateableComponent, public IStartableComponent
{
public:
	AlexGameManagerComponent();
	~AlexGameManagerComponent();

	void SetDependencies(AlexControllerComponent* player, AlexPlatformManagerComponent* platformManager)
	{
		_player = player; _platformManager = platformManager;
	}

	virtual void Update(float deltaTime) override;
	virtual void Start() override;

private:
	Vec2 GetNewPositionForPlatform();
	void SpawnNewPlatform();
	void SpawnNewPlatform(Vec2 position);

	void AddGameProgression();

	AlexControllerComponent *		_player;
	AlexPlatformManagerComponent *	_platformManager;

	int								_score;
	const int						TERMINAL_SCORE = 10000;

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

	std::vector<AlexPlatformManagerComponent::Platform> _platforms;
};