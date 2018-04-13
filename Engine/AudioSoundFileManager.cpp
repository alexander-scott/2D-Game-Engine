#include "AudioSoundFileManager.h"

#include "GlobalVariables.h"

AudioSoundFileManager::AudioSoundFileManager(std::shared_ptr<DirectX::AudioEngine> audioEngine)
{
	for (auto s : AudioFilePaths)
	{
		std::string filePath = std::string(GlobalVariables::Instance().ResourcesFilePath + s.second);

		std::wstring widestr = std::wstring(filePath.begin(), filePath.end());
		const wchar_t* szName = widestr.c_str();

		_audioFiles.insert(std::make_pair(s.first, std::make_unique<DirectX::SoundEffect>(audioEngine.get(), szName)));
	}
}

AudioSoundFileManager::~AudioSoundFileManager()
{
	/*for (auto file : _audioFiles)
	{
		file.second = nullptr;
	}*/
}

void AudioSoundFileManager::PlaySoundEffect(std::string fileName)
{
	_audioFiles.at(fileName)->Play();
}
