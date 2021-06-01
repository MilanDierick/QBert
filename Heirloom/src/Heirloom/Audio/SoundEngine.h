// Author: Milan Dierick
// Created: 28/03/2021 6:44 PM
// Solution: HeirloomEngine

#pragma once
#include "Heirloom/Audio/Sound.h"

namespace Heirloom
{
	class HL_API SoundEngine
	{
	public:
		SoundEngine()          = default;
		virtual ~SoundEngine() = default;

		SoundEngine(const SoundEngine& other)                = delete;
		SoundEngine(SoundEngine&& other) noexcept            = delete;
		SoundEngine& operator=(const SoundEngine& other)     = delete;
		SoundEngine& operator=(SoundEngine&& other) noexcept = delete;

		virtual void Update() = 0;
		virtual void Play(Ref<Sound> sound) = 0;
		virtual void Play(std::string filePath) = 0;
		virtual void Stop(Ref<Sound> sound) = 0;
		virtual void StopAll() = 0;
	};
}
