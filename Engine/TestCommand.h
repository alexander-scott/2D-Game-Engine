#pragma once

#include "ICommand.h"

class MoveUpCommand : public ICommand
{
public:
	MoveUpCommand() { _name = "move_up"; };
	ISystemToGameObjectMessage Execute();
};

class MoveLeftCommand : public ICommand
{
public:
	MoveLeftCommand() { _name = "move_left"; };
	ISystemToGameObjectMessage Execute();
};

class MoveRightCommand : public ICommand
{
public:
	MoveRightCommand() { _name = "move_right"; };
	ISystemToGameObjectMessage Execute();
};

class MoveDownCommand : public ICommand
{
public:
	MoveDownCommand() { _name = "move_down"; };
	ISystemToGameObjectMessage Execute();
};

class RebindSwapCommand: public ICommand
{
public:
	RebindSwapCommand() { _name = "rebind_swap"; };
	ISystemToGameObjectMessage Execute();
};

