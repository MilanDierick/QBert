// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once
#include "Component.h"
#include "Heirloom/Renderer/Sprite.h"

namespace Heirloom
{
	class SpriteRenderer final : public Component
	{
	public:
		explicit SpriteRenderer();
		~SpriteRenderer() override = default;

		SpriteRenderer(const SpriteRenderer& other)                = delete;
		SpriteRenderer(SpriteRenderer&& other) noexcept            = delete;
		SpriteRenderer& operator=(const SpriteRenderer& other)     = delete;
		SpriteRenderer& operator=(SpriteRenderer&& other) noexcept = delete;

		[[nodiscard]] Sprite& GetSprite() { return m_Sprite; }
		void SetSprite(const Sprite& sprite) { m_Sprite = sprite; }

		void Update(Timestep ts) override;
		void Render() override;
	
	private:
		Sprite m_Sprite;
	};
}
