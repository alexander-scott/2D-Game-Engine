#pragma once

#include "ISystem.h"

class EditorSystem : public ISystem
{
public:
	EditorSystem(std::shared_ptr<SystemMessageDispatcher> dispatcher);
	~EditorSystem();

	void InitaliseListeners() override;
	void RecieveMessage(ISystemMessage& message) override;

	void PlayStarted();
	void PlayStopped();

	void LoadNewScene(const char* filePath);
	void SaveScene(const char* filePath);

	void KeyboardInput(int keyCode, KeyboardMessageType messageType);
	void MouseInput(int xpos, int ypos, MouseMessageType messageType);
};

