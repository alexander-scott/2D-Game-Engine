#include "PComponentFactory.h"

PCarComponent * ComponentFactory::MakePCarComponent()
{
	return new PCarComponent();
}
