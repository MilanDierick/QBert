// Author: Milan Dierick
// Created: 04/04/2021 9:26 PM
// Solution: HeirloomEngine

#pragma once
#include "SoundEngine.h"

namespace Heirloom
{
	class HL_API NullSoundEngine final : public SoundEngine
	{
	public:
		void Update() override;
		void Play(Ref<Sound> sound) override;
		void Play(std::string filePath) override;
		void Stop(Ref<Sound> sound) override;
		void StopAll() override;
	};
}
