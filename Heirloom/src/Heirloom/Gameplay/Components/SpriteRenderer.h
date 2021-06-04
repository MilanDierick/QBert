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
		~SpriteRenderer() override;

		SpriteRenderer(const SpriteRenderer& other)                = delete;
		SpriteRenderer(SpriteRenderer&& other) noexcept            = delete;
		SpriteRenderer& operator=(const SpriteRenderer& other)     = delete;
		SpriteRenderer& operator=(SpriteRenderer&& other) noexcept = delete;

		[[nodiscard]] Ref<Sprite> GetSprite() const { return m_Sprite; }
		void SetSprite(const Ref<Sprite> sprite) { m_Sprite = sprite; }
		[[nodiscard]] glm::vec3& GetSpriteOffset() { return m_SpriteOffset; }
		void SetSpriteOffset(const glm::vec3& spriteOffset) { m_SpriteOffset = spriteOffset; }
		GameObject* GetParent() const override { return m_Parent; }
		void SetParent(GameObject* gameObject) override { m_Parent = gameObject; }

		void Update(Timestep ts) override;
		void Render() override;

	private:
		Ref<Sprite> m_Sprite;
		glm::vec3 m_SpriteOffset;
		GameObject* m_Parent;
	};
}
