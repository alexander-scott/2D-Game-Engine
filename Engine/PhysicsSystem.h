#pragma once

#include "ISystem.h"

class PhysicsSystem : public ISystem
{
public:
	PhysicsSystem(std::shared_ptr<SystemMessageDispatcher> dispatcher);
	~PhysicsSystem();

	void InitaliseListeners() override;
	void RecieveMessage(ISystemMessage& message) override;


};