#pragma once

#include "DirectXTK\Inc\Audio.h"

#include <map>

static std::map<std::string, std::string> AudioFilePaths =
{
	{ "Whoosh",			"..\\Resources\\Audio\\Whoosh.wav" },
};

class AudioSoundFileManager
{
public:
	AudioSoundFileManager(std::shared_ptr<DirectX::AudioEngine> audioEngine);
	~AudioSoundFileManager();

	void PlaySoundEffect(std::string fileName);

private:
	std::map<std::string, std::unique_ptr<DirectX::SoundEffect>>	_audioFiles;
};

