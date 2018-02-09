#include "Engine.h"

// Constructor that uses width and height from Consts.h
Engine::Engine(MainWindow & wnd) : _mainWindow(wnd)
{
}

// Constructor that uses width and height that are passed in from MainWindow.h
Engine::Engine(MainWindow& wnd, int width, int height) : _mainWindow(wnd)
{

}

Engine::~Engine()
{

}

void Engine::Update()
{
	float deltaTime = _frameTimer.Mark();
}