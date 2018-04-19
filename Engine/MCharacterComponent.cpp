#include "MCharacterComponent.h"



MCharacterComponent::MCharacterComponent() : IComponent("MCharacterComponent")
{
	//_transformComponent = nullptr;
	//_rigidBodyComponent = nullptr;
}


MCharacterComponent::~MCharacterComponent()
{
}

void MCharacterComponent::Update(float deltaTime)
{
}

void MCharacterComponent::RecieveMessage(IComponentMessage & msg)
{
}

