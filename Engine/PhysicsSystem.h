#pragma once

#include <set>

#include "ISystem.h"

#include "ColliderComponent.h"
#include "Scene.h"
#include "Collision.h"
#include "ObjectGrid.h"

class PhysicsSystem : public ISystem
{
public:
	PhysicsSystem(std::shared_ptr<SystemMessageDispatcher> dispatcher);
	~PhysicsSystem();

	void InitaliseListeners() override;
	void RecieveMessage(ISystemMessage& message) override;

private:
	void AddGameObjectToSystem(shared_ptr<GameObject> gameObject);
	void Update(float deltaTime);

	void IntegrateForces(ColliderComponent* collider, float deltaTime);
	void IntegrateVelocity(ColliderComponent* collider, float deltaTime);

	void UpdateObjectInGrid(ColliderComponent* collider, int colliderIndex);
	void GetIntersectingCells(std::set<int>& intersectingCells, ColliderComponent* collider);

	ObjectGrid*							mObjectGrid;

	vector<shared_ptr<GameObject>>		mGameObjects;
	vector<ColliderComponent*>			mColliders;
};