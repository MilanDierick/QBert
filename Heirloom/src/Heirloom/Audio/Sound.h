// Author: Milan Dierick
// Created: 28/03/2021 7:17 PM
// Solution: HeirloomEngine

#pragma once

namespace Heirloom
{
	struct HL_API Sound
	{
		std::string FileName;
		float Volume;
		bool ShouldLoop;

		[[nodiscard]] explicit Sound(const std::string& fileName,
									 const float volume    = 1.0f,
									 const bool shouldLoop = false)
			: FileName(fileName), Volume(volume), ShouldLoop(shouldLoop)
		{
		}
	};
}
