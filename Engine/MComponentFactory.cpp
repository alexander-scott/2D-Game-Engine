#include "MComponentFactory.h"




MCharacterComponent * ComponentFactory::MakeMCharacterComponent()
{
	return new MCharacterComponent();
}

MBackgroundComponent * ComponentFactory::MakeMBackgroundComponent()
{
	return new MBackgroundComponent();
}
