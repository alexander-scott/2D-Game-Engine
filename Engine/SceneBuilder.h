#pragma once

#include "IScene.h"

#include "ISystem.h"
#include "PostOfficeListener.h"
#include "PostOffice.h"

class SceneBuilder : public ISystem, public PostOfficeListener
{
public:
	SceneBuilder();

	void RecieveMessage(IMessage& message) override;

private:
	shared_ptr<IScene> BuildScene();
};