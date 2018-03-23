#include "AudioSystem.h"

#include "PlayAudioMessage.h"

AudioSystem::AudioSystem(std::shared_ptr<SystemMessageDispatcher> dispatcher)
	: ISystem(SystemType::eEditor, dispatcher)
{
	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | DirectX::AudioEngine_Debug;
#endif

	_audioEngine = std::make_unique<DirectX::AudioEngine>(eflags);
	_audioFileManager = std::make_unique<AudioSoundFileManager>(_audioEngine);
	_retryAudio = false;

	if (!_audioEngine->IsAudioDevicePresent())
	{
		// we are in 'silent' mode
	}
}

AudioSystem::~AudioSystem()
{
	if (_audioEngine)
	{
		_audioEngine->Suspend();
	}
}

void AudioSystem::InitaliseListeners()
{
	SubscribeToMessageType(SystemMessageType::ePlaySound);
	SubscribeToMessageType(SystemMessageType::eSuspendAudio);
	SubscribeToMessageType(SystemMessageType::eResumeAudio);
}

void AudioSystem::RecieveMessage(ISystemMessage & message)
{
	switch (message.Type)
	{
	case SystemMessageType::eSuspendAudio:
		Suspend();
		break;

	case SystemMessageType::eResumeAudio:
		Resume();
		break;

	case SystemMessageType::ePlaySound:
		PlayAudioMessage & msg = static_cast<PlayAudioMessage&>(message);
		_audioFileManager->PlaySoundEffect(msg.FileName);
		break;
	}
}

void AudioSystem::PlaySoundEffect(std::string fileName)
{
}

void AudioSystem::Suspend()
{
	_audioEngine->Suspend();
}

void AudioSystem::Resume()
{
	_audioEngine->Resume();
}
