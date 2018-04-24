#include "MChestComponent.h"



MChestComponent::MChestComponent() : IComponent("MChestComponent")
{
}


MChestComponent::~MChestComponent()
{
}

void MChestComponent::Update(float deltaTime)
{

}

void MChestComponent::RecieveMessage(IComponentMessage & msg) //doesn't work, i don't understand why...
{
	switch (msg.MessageType) {
		case ComponentMessageType::eCollisionMessage: {
			CollisionMessage &message = static_cast<CollisionMessage&>(msg);
			if (message.CollidedObjectTag == "PlayerSprite") {
				_spriteAnimatedComponent->SetAnimation("Opened");
			}
			break;
		}
		default: {
			_spriteAnimatedComponent->SetAnimation("Closed");
			break;
		}


	}
}
