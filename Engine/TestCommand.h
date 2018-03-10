#pragma once

#include "ICommand.h"

class MoveUpCommand : public ICommand
{
public:
	ISystemToGameObjectMessage Execute();
};

class MoveLeftCommand : public ICommand
{
public:
	ISystemToGameObjectMessage Execute();
};

class MoveRightCommand : public ICommand
{
public:
	ISystemToGameObjectMessage Execute();
};

class MoveDownCommand : public ICommand
{
public:
	ISystemToGameObjectMessage Execute();
};

class RebindSwapCommand: public ICommand
{
	ISystemToGameObjectMessage Execute();
};

