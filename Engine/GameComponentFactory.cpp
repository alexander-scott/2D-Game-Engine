#include "GameComponentFactory.h"

PlayerControllerComponent* ComponentFactory::MakePlayerComponent()
{
	return new PlayerControllerComponent();
}