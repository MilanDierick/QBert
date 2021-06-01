// Author: Milan Dierick
// Created: 03/03/2021 2:41 AM
// Solution: HeirloomEngine

#pragma once
#include "Event.h"

namespace Heirloom
{
	struct HL_API KeyEventArgs : EventArgs
	{
		[[nodiscard]] explicit KeyEventArgs(const int keyCode)
			: KeyCode(keyCode)
		{
		}

		int KeyCode;
	};

	struct HL_API KeyPressedEventArgs : EventArgs
	{
		[[nodiscard]] KeyPressedEventArgs(const int keyCode, const int repeatCount)
			: KeyCode(keyCode), RepeatCount(repeatCount)
		{
		}

		int KeyCode;
		int RepeatCount;
	};

	struct HL_API KeyReleasedEventArgs : EventArgs
	{
		[[nodiscard]] explicit KeyReleasedEventArgs(const int keyCode)
			: KeyCode(keyCode)
		{
		}

		int KeyCode;
	};

	struct HL_API KeyTypedEventArgs : EventArgs
	{
		[[nodiscard]] explicit KeyTypedEventArgs(const int keyCode)
			: KeyCode(keyCode)
		{
		}

		int KeyCode;
	};
}
