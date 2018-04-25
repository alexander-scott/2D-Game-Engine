#include "MIntroComponent.h"



MIntroComponent::MIntroComponent() : IComponent("MIntroComponent")
{
}


MIntroComponent::~MIntroComponent()
{
}

void MIntroComponent::RecieveMessage(IComponentMessage & msg)
{
	if (msg.MessageType == ComponentMessageType::eInputHandlerToGameObjectMessage) {
		InputHandlerToGameObjectMessage &msgHandler = static_cast<InputHandlerToGameObjectMessage&>(msg);
		int idMsg = msgHandler.Command._ID;
		if (idMsg == 1 || idMsg == 2 || idMsg == 3 || idMsg == 4) {
			_spriteAnimatedComponent->SetAnimation("Hidden");
		}
	}

}
