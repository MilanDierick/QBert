#include "hlpch.h"
#include "NullSoundEngine.h"

namespace Heirloom
{
	void NullSoundEngine::Update()
	{
	}

	void NullSoundEngine::Play(const Ref<Sound> sound)
	{
		HL_CORE_TRACE("NullSoundEngine started playing sound \"{0}\"", sound->FileName);
	}

	void NullSoundEngine::Play(const std::string filePath)
	{
		HL_CORE_TRACE("NullSoundEngine started playing sound \"{0}\"", filePath);
	}

	void NullSoundEngine::Stop(const Ref<Sound> sound)
	{
		HL_CORE_TRACE("NullSoundEngine stopped playing sound \"{0}\"", sound->FileName);
	}

	void NullSoundEngine::StopAll()
	{
		HL_CORE_TRACE("NullSoundEngine stopped playing all sounds");
	}
}
