#pragma once

#include "ISystem.h"

class InputHandler : public ISystem
{
public:
	InputHandler(std::shared_ptr<SystemMessageDispatcher> dispatcher);

	void InitaliseListeners() override;
	void RecieveMessage(ISystemMessage& message) override;
};

