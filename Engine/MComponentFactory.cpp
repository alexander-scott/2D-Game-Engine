#include "MComponentFactory.h"




MCharacterComponent * ComponentFactory::MakeMCharacterComponent()
{
	return new MCharacterComponent();
}
