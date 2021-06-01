// Author: Milan Dierick
// Created: 04/04/2021 9:10 PM
// Solution: HeirloomEngine

#pragma once
#include "SoundEngine.h"

namespace Heirloom
{
	class HL_API SoundService
	{
	public:
		~SoundService() { delete m_SoundEngine; }

		static SoundEngine* GetSoundEngine() { return m_SoundEngine; }

		static void Provide(SoundEngine* soundEngine);

	private:
		static SoundEngine* m_SoundEngine;
	};
}
