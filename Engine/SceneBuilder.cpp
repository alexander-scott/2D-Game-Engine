#include "SceneBuilder.h"

#include "BuildSceneMessage.h"

SceneBuilder::SceneBuilder() : ISystem(SystemType::eSceneBuilder), PostOfficeMessenger(MessengerType::eSceneBuilderMessenger)
{
	PostOffice::Instance().AddListener(this, MessageType::eRequestBuildSceneMessage);
}

void SceneBuilder::RecieveMessage(IMessage & message)
{
	if (message.Type == MessageType::eRequestBuildSceneMessage)
	{
		shared_ptr<PlayScene> scene = BuildScene();

		BuildSceneMessage sceneMsg(scene);
		PostOffice::Instance().SendMessageToListeners(sceneMsg);
	}
}

shared_ptr<PlayScene> SceneBuilder::BuildScene()
{
	return make_shared<PlayScene>();
}