#pragma once

#include "PlayScene.h"

#include "ISystem.h"
#include "PostOfficeListener.h"
#include "PostOfficeMessenger.h"
#include "PostOffice.h"

class SceneBuilder : public ISystem, public PostOfficeListener, public PostOfficeMessenger
{
public:
	SceneBuilder();

	void RecieveMessage(IMessage& message) override;

private:
	shared_ptr<PlayScene> BuildScene();
};

