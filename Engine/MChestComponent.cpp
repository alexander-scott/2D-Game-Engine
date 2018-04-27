#include "MChestComponent.h"



MChestComponent::MChestComponent() : IComponent("MChestComponent")
{
}


MChestComponent::~MChestComponent()
{
}

void MChestComponent::Update(float deltaTime)
{
	//Was put to start the level again by changing the chest position but i prefer letting it at its original position after all...
	//if (_spriteAnimatedComponent->GetAnimation() == "Opened") { //replace the chest randomly somewhere else
	//	float xPos = ((float)(rand() % 400)) + 400.0f;
	//	float yPos = ((float)(rand() % 300)) + 300.0f;
	//	_transformComponent->SetWorldPosition(Vec2(xPos, yPos));
	//	_spriteAnimatedComponent->SetAnimation("Closed");
	//}
}

void MChestComponent::RecieveMessage(IComponentMessage & msg) 
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
