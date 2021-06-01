#include "hlpch.h"
#include "SimpleSoundEngine.h"

namespace Heirloom
{
	SimpleSoundEngine::SimpleSoundEngine()
		: SoundEngine()
	{
		HL_PROFILE_FUNCTION()

		m_SoundEngine = irrklang::createIrrKlangDevice();

		m_SoundsQueue       = new LockFreeStack<Ref<Sound>>();
		m_SoundsQueueBuffer = new LockFreeStack<Ref<Sound>>();
	}

	SimpleSoundEngine::~SimpleSoundEngine()
	{
		HL_PROFILE_FUNCTION()

		m_SoundEngine->drop();

		delete m_SoundsQueue;
		delete m_SoundsQueueBuffer;
	}

	void SimpleSoundEngine::Update()
	{
		SwapBuffers();
		PlayBufferedSounds();
	}

	void SimpleSoundEngine::Play(std::string filePath)
	{
		HL_PROFILE_FUNCTION()

		m_SoundsQueue->Push(CreateRef<Sound>(filePath, 1.0f, false));
	}

	void SimpleSoundEngine::Play(const Ref<Sound> sound)
	{
		HL_PROFILE_FUNCTION()

		m_SoundsQueue->Push(sound);
	}

	void SimpleSoundEngine::Stop(const Ref<Sound> sound)
	{
		HL_PROFILE_FUNCTION()

		for (std::vector<irrklang::ISoundSource*>::value_type soundSource : m_CachedSoundSources)
		{
			if (sound->FileName == soundSource->getName()) m_SoundEngine->stopAllSoundsOfSoundSource(soundSource);
		}
	}

	void SimpleSoundEngine::StopAll()
	{
		HL_PROFILE_FUNCTION()

		m_SoundEngine->stopAllSounds();
	}

	void SimpleSoundEngine::SwapBuffers() { std::swap(m_SoundsQueue, m_SoundsQueueBuffer); }

	void SimpleSoundEngine::CacheSound(irrklang::ISoundSource* soundSource)
	{
		bool soundSourceFound = false;

		for (std::vector<irrklang::ISoundSource*>::value_type cachedSoundSource : m_CachedSoundSources)
		{
			if (soundSource->getName() == cachedSoundSource->getName()) soundSourceFound = true;
		}

		if (!soundSourceFound) { m_CachedSoundSources.push_back(soundSource); }
	}

	void SimpleSoundEngine::PlayBufferedSounds()
	{
		if (m_SoundsQueueBuffer->Size() == 0) return;

		// TODO: Spawning a new thread every time we want to play a new sound is quite ridiculous, consider spawning a single thread that keeps on emptying the sound buffer
		std::thread thread([this]()
		{
			while (m_SoundsQueueBuffer->Size() != 0)
			{
				Node<Ref<Sound>>* node = m_SoundsQueueBuffer->Pop();

				irrklang::ISoundSource* result = m_SoundEngine->play2D(node->Value->FileName.c_str(),
																	   node->Value->ShouldLoop,
																	   false,
																	   true)->getSoundSource();

				CacheSound(result);
				delete node;
			}
		});

		thread.detach();
	}
}
