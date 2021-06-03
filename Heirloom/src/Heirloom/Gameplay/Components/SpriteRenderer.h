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

		[[nodiscard]] Ref<Sprite> GetSprite() const { return m_Sprite; }
		void SetSprite(const Ref<Sprite> sprite) { m_Sprite = sprite; }
		[[nodiscard]] glm::vec2& GetSpriteOffset() { return m_SpriteOffset; }
		void SetSpriteOffset(const glm::vec2& spriteOffset) { m_SpriteOffset = spriteOffset; }

		void Update(Timestep ts) override;
		void Render() override;

	private:
		Ref<Sprite> m_Sprite;
		glm::vec2 m_SpriteOffset;
	};
}
