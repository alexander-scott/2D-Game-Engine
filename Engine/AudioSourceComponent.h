#pragma once

#include "IComponent.h"
#include "IMessageableComponent.h"

class AudioSourceComponent : public IComponent
{
public:
	AudioSourceComponent();
	~AudioSourceComponent();

	bool CheckPlayRequests();
	std::vector<std::string> GetPlayRequests();

	void PlayAudioFile(std::string fileName);

private:
	std::vector<std::string>	_playRequests;
	bool						_hasRequests;
};

