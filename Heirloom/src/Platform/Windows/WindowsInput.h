// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once
#include "Heirloom/Core/Input.h"

namespace Heirloom
{
	class WindowsInput final : public Input
	{
	protected:
		bool IsKeyPressedImpl(int keycode) override;

		bool IsMouseButtonPressedImpl(int button) override;
		std::pair<float, float> GetMousePositionImpl() override;
		bool GetMouseXImpl() override;
		bool GetMouseYImpl() override;
	};
}
