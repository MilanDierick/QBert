#include "hlpch.h"
#include "SoundService.h"

#include "NullSoundEngine.h"

namespace Heirloom
{
	SoundEngine* SoundService::m_SoundEngine = new NullSoundEngine();

	void SoundService::Provide(SoundEngine* soundEngine)
	{
		delete m_SoundEngine;
		m_SoundEngine = soundEngine;
	}
}
