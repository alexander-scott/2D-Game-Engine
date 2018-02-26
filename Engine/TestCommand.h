#pragma once

#include "ICommand.h"

class MoveUpCommand : public ICommand
{
public:
	void Execute();
};

class MoveLeftCommand : public ICommand
{
public:
	void Execute();
};

class MoveRightCommand : public ICommand
{
public:
	void Execute();
};

class MoveDownCommand : public ICommand
{
public:
	void Execute();
};

