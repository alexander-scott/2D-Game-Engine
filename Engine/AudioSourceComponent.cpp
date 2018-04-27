#include "AudioSourceComponent.h"

AudioSourceComponent::AudioSourceComponent()
	: IComponent("AudioSourceComponent")
{
	_hasRequests = false;
}

AudioSourceComponent::~AudioSourceComponent()
{
}

bool AudioSourceComponent::CheckPlayRequests()
{
	return _hasRequests;
}

std::vector<std::string> AudioSourceComponent::GetPlayRequests()
{
	auto returnVec = std::vector<std::string>(_playRequests);
	_hasRequests = false; 
	_playRequests.clear();
	return returnVec;
}

void AudioSourceComponent::PlayAudioFile(std::string fileName)
{
	_playRequests.push_back(fileName); 
	_hasRequests = true;
}
