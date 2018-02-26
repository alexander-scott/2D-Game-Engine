#pragma once
class ICommand
{
public:
	virtual ~ICommand() {};
	virtual void Execute(/*player instance? Message to game loop?*/) = 0;
};

