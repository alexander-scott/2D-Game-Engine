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

MChestComponent * ComponentFactory::MakeMChestComponent()
{
	return new MChestComponent();
}

MIntroComponent * ComponentFactory::MakeMIntroComponent()
{
	return new MIntroComponent();
}
