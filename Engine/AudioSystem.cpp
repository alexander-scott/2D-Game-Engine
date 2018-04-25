#include "AudioSystem.h"

#include "PlayAudioMessage.h"
#include "SceneMessage.h"
#include "UpdateSystemMessage.h"

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
	SubscribeToMessageType(SystemMessageType::eSceneSelectedToPlay);
	SubscribeToMessageType(SystemMessageType::ePlayStopped);
	SubscribeToMessageType(SystemMessageType::eUpdateAudio);
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
		{
			PlayAudioMessage & msg = static_cast<PlayAudioMessage&>(message);
			_audioFileManager->PlaySoundEffect(msg.FileName);
			break;
		}

		case SystemMessageType::eSceneSelectedToPlay:
		{
			SceneMessage& msg = static_cast<SceneMessage&>(message);
			auto gameObjects = msg.GetScene()->GetAllGameObjects();
			for (int i = 0; i < gameObjects.size(); i++)
			{
				AddGameObjectToSystem(gameObjects[i]);
			}
			break;
		}

		case SystemMessageType::ePlayStopped:
		{
			_audioSources.clear();
			break;
		}

		case SystemMessageType::eUpdateAudio:
		{
			UpdateSystemMessage& msg = static_cast<UpdateSystemMessage&>(message);
			Update(msg.DeltaTime);
			break;
		}
	}
}

void AudioSystem::Update(float deltaTime)
{
	_audioEngine->Update();

	for (auto audio : _audioSources)
	{
		if (audio->CheckPlayRequests())
		{
			auto soundEffects = audio->GetPlayRequests();
			for (auto effect : soundEffects)
			{
				_audioFileManager->PlaySoundEffect(effect);
			}
		}
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

void AudioSystem::AddGameObjectToSystem(shared_ptr<GameObject> gameObject)
{
	auto components = gameObject->GetAllComponents();
	for (int i = 0; i < components.size(); i++)
	{
		AudioSourceComponent* audioSource = dynamic_cast<AudioSourceComponent*>(components[i]);
		if (audioSource != nullptr)
		{
			_audioSources.push_back(audioSource);
		}
	}
}
