#include "PhysicsSystem.h"

#include "SceneSelectedToPlayMessage.h"
#include "UpdateSystemMessage.h"

PhysicsSystem::PhysicsSystem(std::shared_ptr<SystemMessageDispatcher> dispatcher)
	: ISystem(SystemType::ePhysics, dispatcher)
{
	mObjectGrid = new ObjectGrid(100, 100, 100, 100); // TODO: REMOVE HARD-CODED VALUES
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::InitaliseListeners()
{
	SubscribeToMessageType(SystemMessageType::eSceneSelectedToPlay);
	SubscribeToMessageType(SystemMessageType::eUpdatePhysics);
}

void PhysicsSystem::RecieveMessage(ISystemMessage & message)
{
	switch (message.Type)
	{
		case SystemMessageType::eSceneSelectedToPlay:
		{
			SceneSelectedToPlayMessage& msg = static_cast<SceneSelectedToPlayMessage&>(message);
			auto gameObjects = msg.GetScene()->GetAllGameObjects();
			for (int i = 0; i < gameObjects.size(); i++)
			{
				AddGameObjectToSystem(gameObjects[i]);
			}
			break;
		}

		case SystemMessageType::eUpdatePhysics:
		{
			UpdateSystemMessage& msg = static_cast<UpdateSystemMessage&>(message);
			Update(msg.DeltaTime);
			break;
		}
	}
}

void PhysicsSystem::AddGameObjectToSystem(shared_ptr<GameObject> gameObject)
{
	auto components = gameObject->GetAllComponents();
	for (int i = 0; i < components.size(); i++)
	{
		ColliderComponent* collider = dynamic_cast<ColliderComponent*>(components[i]);
		if (collider != nullptr)
		{
			mGameObjects.push_back(gameObject);
			mColliders.push_back(collider);

			// LEFT, TOP, RIGHT, BOTTOM
			Rect r = collider->GetRect();
			int ltrb[4];
			ltrb[0] = r.LeftX;
			ltrb[1] = abs(r.TopY);
			ltrb[2] = r.RightX;
			ltrb[3] = abs(r.BotY);

			mObjectGrid->Insert(ltrb, (int)mColliders.size() - 1);
			collider->CentreGridSquare = mObjectGrid->GetCellIndex((int)r.Centre.x, (int)abs(r.Centre.y));
			collider->LeftGridSquare = mObjectGrid->GetCellIndex((int)r.LeftX, (int)abs(r.Centre.y));
			collider->RightGridSquare = mObjectGrid->GetCellIndex((int)r.RightX, (int)abs(r.Centre.y));
			collider->BottomGridSquare = mObjectGrid->GetCellIndex((int)r.Centre.x, (int)abs(r.BotY));
			collider->TopGridSquare = mObjectGrid->GetCellIndex((int)r.Centre.x, (int)abs(r.TopY));
			collider->SetPreviousRect(r);
		}
	}
}

void PhysicsSystem::Update(float deltaTime)
{
	// Holds a vector of collisions that occured between objects
	vector<Collision> contacts;
	// Holds a set of every cell index that the collider intersects with. Set is used instead of vector to prevent duplicate cells being inserted
	set<int> intersectingCells;

	for (int i = 0; i < mColliders.size(); i++)
	{
		// If an objects position has changed it's grid positions might have too so we'll need to update it in the grid
		if (mColliders[i]->GetActive() && mColliders[i]->GetTransformComponent()->CheckChanged())
		{
			UpdateObjectInGrid(mColliders[i], i);
		}
	}

	for (int i = 0; i < mColliders.size(); i++) // For every collider in the scene
	{
		ColliderComponent *A = mColliders[i];

		if (!A->GetActive())
			continue;

		GetIntersectingCells(intersectingCells, A);

		for (auto& cell : intersectingCells) // For each cell that this collider intersects
		{
			const GridNode* node = mObjectGrid->GetFirstNode(cell); // Get the GetFirstNode grid node in this cell

			while (node) // While node is not null go through every collider in the node
			{
				int element = node->element;
				node = mObjectGrid->GetNextNode(node); // Load the GetNextNode element for the GetNextNode loop

				if (element <= i) // If the element in this node has an ID less than 'i' that means that we will have already checked this potential collision earlier in the loop
					continue;

				ColliderComponent *B = mColliders[element];
				if (A->GetRigidbodyComponent()->GetInverseMass() == 0 && B->GetRigidbodyComponent()->GetInverseMass() == 0)
					continue;

				if (!B->GetActive())
					continue;

				Collision collision(A, B);
				collision.CheckForCollision();

				if (collision.GetContactCount()) // If there is a collision the number of contacts will be greater than 0
				{
					if (A->GetRigidbodyComponent()->GetActive() && B->GetRigidbodyComponent()->GetActive())
						contacts.emplace_back(collision);

					// TODO: Tell each gameobject that a collision has taken place
					/*CollisionMessage colMsg(mGameObjects[i]);
					mGameObjects[element]->SendMessageToComponents(colMsg);

					CollisionMessage colMsg2(mGameObjects[element]);
					mGameObjects[i]->SendMessageToComponents(colMsg2);*/
				}
			}
		}
	}

	// Integrate forces
	for (int i = 0; i < mColliders.size(); ++i)
		IntegrateForces(mColliders[i], deltaTime);

	// Initialize collision
	for (int i = 0; i < contacts.size(); ++i)
		contacts[i].PrepareToSolve(deltaTime);

	// Resolve collisions
	for (int i = 0; i < contacts.size(); ++i)
		contacts[i].ResolveCollision();

	// Integrate velocities
	for (int i = 0; i < mColliders.size(); ++i)
		IntegrateVelocity(mColliders[i], deltaTime);

	// Correct positions
	for (int i = 0; i < contacts.size(); ++i)
		contacts[i].PenetrationCorrection();

	// Clear all forces
	for (int i = 0; i < mColliders.size(); ++i)
	{
		ColliderComponent *b = mColliders[i];
		b->GetRigidbodyComponent()->SetForce(Vec2(0, 0));
		b->GetRigidbodyComponent()->SetTorque(0);
	}
}

void PhysicsSystem::IntegrateForces(ColliderComponent * collider, float deltaTime)
{
	if (collider->GetRigidbodyComponent()->GetInverseMass() == 0.0f || !collider->GetActive() || !collider->GetRigidbodyComponent()->GetActive())
		return;

	collider->GetRigidbodyComponent()->SetVelocity(collider->GetRigidbodyComponent()->GetVelocity() +
		(collider->GetRigidbodyComponent()->GetForce() * collider->GetRigidbodyComponent()->GetInverseMass() +
		(GRAVITY_VECTOR * (collider->GetRigidbodyComponent()->GetInverseMass() * 3000))) * (deltaTime / 2.0f));

	collider->GetRigidbodyComponent()->SetAngularVelocity(collider->GetRigidbodyComponent()->GetAngularVelocity() +
		collider->GetRigidbodyComponent()->GetTorque() * collider->GetRigidbodyComponent()->GetInverseIntertia() * (deltaTime / 2.0f));
}

void PhysicsSystem::IntegrateVelocity(ColliderComponent * collider, float deltaTime)
{
	if (collider->GetRigidbodyComponent()->GetInverseMass() == 0.0f || !collider->GetActive() || !collider->GetRigidbodyComponent()->GetActive())
		return;

	// Calculate position
	collider->GetTransformComponent()->SetWorldPosition(collider->GetTransformComponent()->GetWorldPosition() + collider->GetRigidbodyComponent()->GetVelocity() * deltaTime);

	if (!collider->GetRigidbodyComponent()->RotationLocked())
	{
		// Calculate rotation (RADIANS)
		collider->GetTransformComponent()->SetWorldRotation(collider->GetTransformComponent()->GetWorldRotation()
			+ collider->GetRigidbodyComponent()->GetAngularVelocity() * deltaTime);

		// Set RB orientation matrix
		collider->GetRigidbodyComponent()->SetOrientationMatrix(collider->GetTransformComponent()->GetWorldRotation());
	}

	IntegrateForces(collider, deltaTime);
}

void PhysicsSystem::UpdateObjectInGrid(ColliderComponent * collider, int colliderIndex)
{
	Rect newRect = collider->GetRect();
	int centreCell = mObjectGrid->GetCellIndex((int)newRect.Centre.x, (int)abs(newRect.Centre.y));
	int leftCell = mObjectGrid->GetCellIndex((int)newRect.LeftX, (int)abs(newRect.Centre.y));
	int rightCell = mObjectGrid->GetCellIndex((int)newRect.RightX, (int)abs(newRect.Centre.y));
	int bottomCell = mObjectGrid->GetCellIndex((int)newRect.Centre.x, (int)abs(newRect.BotY));
	int topCell = mObjectGrid->GetCellIndex((int)newRect.Centre.x, (int)abs(newRect.TopY));

	if (centreCell != collider->CentreGridSquare ||
		leftCell != collider->LeftGridSquare ||
		rightCell != collider->RightGridSquare ||
		bottomCell != collider->BottomGridSquare ||
		topCell != collider->TopGridSquare) // A cell has changed
	{
		Rect prevRect = collider->GetPreviousRect();
		int ltrb[4];
		ltrb[0] = prevRect.LeftX;
		ltrb[1] = abs(prevRect.TopY);
		ltrb[2] = prevRect.RightX;
		ltrb[3] = abs(prevRect.BotY);
		mObjectGrid->Erase(ltrb, colliderIndex);

		ltrb[0] = newRect.LeftX;
		ltrb[1] = abs(newRect.TopY);
		ltrb[2] = newRect.RightX;
		ltrb[3] = abs(newRect.BotY);
		mObjectGrid->Insert(ltrb, colliderIndex);

		collider->CentreGridSquare = centreCell;
		collider->LeftGridSquare = leftCell;
		collider->RightGridSquare = rightCell;
		collider->BottomGridSquare = bottomCell;
		collider->TopGridSquare = topCell;

		collider->SetPreviousRect(newRect);
	}

	collider->GetTransformComponent()->SetChanged(false);
}

void PhysicsSystem::GetIntersectingCells(std::set<int>& intersectingCells, ColliderComponent * collider)
{
	Rect r = collider->GetRect(); // Get the rect belonging to this collider

	intersectingCells.clear();
	for (int i = 0; i < 5; i++) // For every important point on the rect, get the cell that it is in
	{
		if (i == 0) // Centre
			intersectingCells.insert(mObjectGrid->GetCellIndex((int)r.Centre.x, (int)abs(r.Centre.y)));
		else if (i == 1) // Left
			intersectingCells.insert(mObjectGrid->GetCellIndex((int)r.LeftX, (int)abs(r.Centre.y)));
		else if (i == 2) // Right
			intersectingCells.insert(mObjectGrid->GetCellIndex((int)r.RightX, (int)abs(r.Centre.y)));
		else if (i == 3) // Top
			intersectingCells.insert(mObjectGrid->GetCellIndex((int)r.Centre.x, (int)abs(r.TopY)));
		else if (i == 4) // Bottom
			intersectingCells.insert(mObjectGrid->GetCellIndex((int)r.Centre.x, (int)abs(r.BotY)));
	}
}
