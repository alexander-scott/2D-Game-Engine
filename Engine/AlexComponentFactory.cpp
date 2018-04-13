#include "AlexComponentFactory.h"

AlexControllerComponent* ComponentFactory::MakeAlexControllerComponent()
{
	return new AlexControllerComponent();
}