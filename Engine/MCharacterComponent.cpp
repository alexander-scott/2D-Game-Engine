#include "MCharacterComponent.h"



MCharacterComponent::MCharacterComponent() : IComponent("MCharacterComponent")
{
	//_transformComponent = nullptr;
	//_rigidBodyComponent = nullptr;
	_goesBot = false;
	_goesTop = false;
	_goesLeft = false;
	_goesRight = false;

	_canGoTop = true; 
	_canGoBot = true;
	_canGoLeft = true;
	_canGoRight = true;

}


MCharacterComponent::~MCharacterComponent()
{
}

void MCharacterComponent::Update(float deltaTime)
{
	if (_goesRight && _canGoRight) {
		_transformComponent->SetWorldPosition(Vec2(_transformComponent->GetWorldPosition().x+1.0f, _transformComponent->GetWorldPosition().y ));
	}
	if (_goesLeft && _canGoLeft) {
		_transformComponent->SetWorldPosition(Vec2(_transformComponent->GetWorldPosition().x - 1.0f, _transformComponent->GetWorldPosition().y));
	}
	if (_goesTop && _canGoTop) {
		_transformComponent->SetWorldPosition(Vec2(_transformComponent->GetWorldPosition().x, _transformComponent->GetWorldPosition().y-1.0f));
	}
	if (_goesBot && _canGoBot) {
		_transformComponent->SetWorldPosition(Vec2(_transformComponent->GetWorldPosition().x, _transformComponent->GetWorldPosition().y + 1.0f));
	}
}

void MCharacterComponent::RecieveMessage(IComponentMessage & msg)
{
	switch (msg.MessageType) {
	case ComponentMessageType::eInputHandlerToGameObjectMessage:
	{
		InputHandlerToGameObjectMessage &msgHandler = static_cast<InputHandlerToGameObjectMessage&>(msg);
		ProcessInput(msgHandler.MessageType, msgHandler.Command, msgHandler.Range);
		break;
	}
	//add collision case with rigidbody
	case ComponentMessageType::eCollisionMessage: {
		int i = 0;
		CollisionMessage &message = static_cast<CollisionMessage&>(msg);
		if (message.CollidedObjectTag == "Trap") {
			if (_goesBot == true) {
				_canGoBot = false;
			}
			if (_goesTop == true) {
				_canGoTop = false;
			}
			if (_goesRight == true) {
				_canGoRight = false;
			}
			if (_goesLeft == true) {
				//_goesLeft = false;
				_canGoLeft = false;
			}
		}
		if (message.CollidedObjectTag == "Phantom") {
			int i = 0; 
		}

		break;


		
	}
	}
}

void MCharacterComponent::ProcessInput(InputGenericStateMessageType msgType, sCommand msgCommand, float msgRange)
{
	bool keyPressed;
	if (msgType == InputGenericStateMessageType::eKeyPressed) {
		keyPressed = true;
	}
	else
		keyPressed = false;

	switch (msgCommand._ID) {
	case 1: //W
	{
		_goesTop = keyPressed;
		_spriteAnimatedComponent->SetAnimation("WalkTop"); 
		break;
	}
	case 2://S
	{
		_goesBot = keyPressed;
		_spriteAnimatedComponent->SetAnimation("WalkBot");
		break;
	}
	case 3://A
	{
		_goesLeft = keyPressed;
		_spriteAnimatedComponent->SetAnimation("WalkLeft");
		break;
	}
	case 4://D
	{
		_goesRight = keyPressed;
		_spriteAnimatedComponent->SetAnimation("WalkRight");
		break;
	}
	}
}

