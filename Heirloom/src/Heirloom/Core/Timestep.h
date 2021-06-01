// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once

namespace Heirloom
{
	class Timestep
	{
	public:
		explicit Timestep(const float time = 0.0f)
			: m_Time(time)
		{
		}

		/**
		 * \brief Returns the time in seconds
		 */
		// ReSharper disable once CppNonExplicitConversionOperator
		operator float() const { return m_Time; }

		[[nodiscard]] float GetSeconds() const { return m_Time; }
		[[nodiscard]] float GetMilliseconds() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};
}
