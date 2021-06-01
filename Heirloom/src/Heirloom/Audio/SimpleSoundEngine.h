// Author: Milan Dierick
// Created: 28/03/2021 7:21 PM
// Solution: HeirloomEngine

#pragma once
#include "Heirloom/Audio/SoundEngine.h"
#include "Heirloom/Core/LockFreeStack.h"
#include <irrKlang.h>

namespace Heirloom
{
	class HL_API SimpleSoundEngine final : public SoundEngine
	{
	public:
		[[nodiscard]] SimpleSoundEngine();
		~SimpleSoundEngine() override;

		void Update() override;
		void Play(std::string filePath) override;
		void Play(Ref<Sound> sound) override;
		void Stop(Ref<Sound> sound) override;
		void StopAll() override;

	private:
		void SwapBuffers();
		void CacheSound(irrklang::ISoundSource* soundSource);
		void PlayBufferedSounds();

		irrklang::ISoundEngine* m_SoundEngine;

		// TODO: Consider if this actually needs to be thread-safe
		LockFreeStack<Ref<Sound>>* m_SoundsQueue;
		LockFreeStack<Ref<Sound>>* m_SoundsQueueBuffer;
		std::vector<irrklang::ISoundSource*> m_CachedSoundSources;
	};
}
