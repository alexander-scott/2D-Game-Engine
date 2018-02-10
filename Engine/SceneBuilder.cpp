#include "SceneBuilder.h"

#include "BuildSceneMessage.h"

SceneBuilder::SceneBuilder() : ISystem(SystemType::eSceneBuilder)
{
	SubscribeToMessageType(SystemMessageType::eRequestBuildSceneMessage);
}

void SceneBuilder::RecieveMessage(ISystemMessage & message)
{
	if (message.Type == SystemMessageType::eRequestBuildSceneMessage)
	{
		// If the engine asks the SceneBuilder system to create a Scene, build one and send a pointer to it in a message.
		// In the future the ReqestBuildScene message will contain info like scene name or scene file path etc.
		shared_ptr<IScene> scene = BuildScene();

		BuildSceneMessage sceneMsg(scene);
		PostOffice::Instance().SendMessageToListeners(sceneMsg);
	}
}

shared_ptr<IScene> SceneBuilder::BuildScene()
{
	// BUILD AND RETURN AN EMPTY ISCENE FOR NOW.
	return make_shared<IScene>();
}