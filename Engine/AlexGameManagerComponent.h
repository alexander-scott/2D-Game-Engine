#pragma once

#include "IComponent.h"

#include "IUpdateableComponent.h"
#include "IStartableComponent.h"

#include "AlexPlatformManagerComponent.h"
#include "AlexControllerComponent.h"

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

	AlexControllerComponent *		_player;
	AlexPlatformManagerComponent *	_platformManager;

	float							_minDistBetweenPlatforms;
	std::vector<Vec2>				_platformPositions;

	bool							_platformsMoving;
	float							_platformStartHeight;
};