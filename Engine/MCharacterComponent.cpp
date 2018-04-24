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
		CollisionMessage &message = static_cast<CollisionMessage&>(msg);
		if (message.CollidedObjectTag == "Trap") {
			if (_goesBot == true) {
				ResetPosition();
				//_canGoBot = false; //TODO : add time count so that it can move again after like, 2 sec or so
			}
			if (_goesTop == true) {
				ResetPosition();
				//_canGoTop = false;
			}
			if (_goesRight == true) {
				ResetPosition();
				//_canGoRight = false;
			}
			if (_goesLeft == true) {
				ResetPosition();
				//_goesLeft = false;
				//_canGoLeft = false;
			}
		}
		else {
			_canGoLeft = true;
			_canGoRight = true;
			_canGoTop = true;
			_canGoBot = true;
		}
		if (message.CollidedObjectTag == "Phantom") {
			_spriteAnimatedComponent->SetAnimation("Dead");
		}
		if (message.CollidedObjectTag == "Chest") {
			_spriteAnimatedComponent->SetAnimation("Winning");
			_canGoTop = false;
			_canGoBot = false;
			_canGoLeft = false;
			_canGoRight = false;
		}
		break;


		
	}
	default:
	{
		_canGoLeft = true;
		_canGoRight = true;
		_canGoTop = true;
		_canGoBot = true;
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
	case 5: //space to restart
	{
		if (_spriteAnimatedComponent->GetAnimation() == "Winning") {
			ResetPosition();
			_canGoLeft = true;
			_canGoRight = true;
			_canGoTop = true;
			_canGoBot = true;
			_spriteAnimatedComponent->SetAnimation("WalkBot");
		}
		break;
	}
	}
}

void MCharacterComponent::ResetPosition()
{
	_transformComponent->SetWorldPosition(_startPosition);
}

