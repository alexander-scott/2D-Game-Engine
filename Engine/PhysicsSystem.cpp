#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem(std::shared_ptr<SystemMessageDispatcher> dispatcher)
	: ISystem(SystemType::ePhysics, dispatcher)
{
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::InitaliseListeners()
{
	SubscribeToMessageType(SystemMessageType::eUpdatePhysics);
}

void PhysicsSystem::RecieveMessage(ISystemMessage & message)
{
}
