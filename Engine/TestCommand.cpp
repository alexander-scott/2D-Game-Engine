#include "TestCommand.h"

ISystemToGameObjectMessage MoveUpCommand::Execute()
{
	//there must be a more elegant way to do this
	IComponentMessage componentMessage(eSetParentTransformMessage);
	ISystemToGameObjectMessage systemMessage(componentMessage);
	return systemMessage;
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

ISystemToGameObjectMessage RebindSwapCommand::Execute()
{
	//send a message to game logic to activate the rebinding interface
	//the game logic will then tell the inputhandler to activate rebinding mode
	IComponentMessage componentMessage(eActivateRebindingKeyboardCommands);
	ISystemToGameObjectMessage systemMessage(componentMessage);
	return (ISystemToGameObjectMessage(IComponentMessage(eSetParentTransformMessage)));
}
