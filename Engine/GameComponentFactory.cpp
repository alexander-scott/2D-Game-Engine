#include "GameComponentFactory.h"

PlayerController* ComponentFactory::MakePlayerComponent()
{
	return new PlayerController();
}