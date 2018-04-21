#include "MComponentFactory.h"




MCharacterComponent * ComponentFactory::MakeMCharacterComponent()
{
	return new MCharacterComponent();
}

MBackgroundComponent * ComponentFactory::MakeMBackgroundComponent()
{
	return new MBackgroundComponent();
}

MPhantomComponent * ComponentFactory::MakeMPhantomComponent()
{
	return new MPhantomComponent();
}
