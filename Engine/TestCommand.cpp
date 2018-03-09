#include "TestCommand.h"

ISystemToGameObjectMessage MoveUpCommand::Execute()
{
	//there must be a more elegant way to do this
	IComponentMessage * testComponent = new IComponentMessage(eSetParentTransformMessage);
	ISystemToGameObjectMessage  * test = new ISystemToGameObjectMessage(*testComponent);
	return *test;
}

ISystemToGameObjectMessage MoveLeftCommand::Execute()
{
	//To set properly
	return (ISystemToGameObjectMessage(IComponentMessage(eSetParentTransformMessage)));
}

ISystemToGameObjectMessage MoveRightCommand::Execute()
{
	//To set properly
	return (ISystemToGameObjectMessage(IComponentMessage(eSetParentTransformMessage)));
}

ISystemToGameObjectMessage MoveDownCommand::Execute()
{
	//To set properly
	return (ISystemToGameObjectMessage(IComponentMessage(eSetParentTransformMessage)));
}
