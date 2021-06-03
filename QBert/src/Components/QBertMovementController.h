// Author: Milan Dierick
// Created: 02/06/2021 10:37 PM
// Solution: QBert

#pragma once
#include <unordered_set>

#include "Heirloom.h"

#include "HexagonalGrid/Hexagon.h"
#include "HexagonalGrid/Layout.h"

struct OutOfBoundsEventArgs : Heirloom::EventArgs
{
};

class QBertMovementController final : public Heirloom::Component
{
public:
	[[nodiscard]] explicit QBertMovementController(size_t ticksBetweenMoves,
												   size_t ticksPerMove,
												   Hex currentHex,
												   Heirloom::Ref<std::unordered_set<Hex>> hexagons);

	Heirloom::Event<OutOfBoundsEventArgs> OutOfBoundsEvent;

	void Update(Heirloom::Timestep ts) override;
	void Render() override;

	[[nodiscard]] Hex& GetCurrentHex();
	void SetCurrentHex(const Hex& currentHex);
	[[nodiscard]] Heirloom::Ref<Heirloom::SpriteRenderer> GetSpriteRenderer() const;
	void SetSpriteRenderer(Heirloom::Ref<Heirloom::SpriteRenderer> spriteRenderer);

private:
	Hex m_CurrentHex;
	Hex m_TargetHex;
	Layout m_HexagonalGridLayout;
	size_t m_TicksBetweenMoves;
	size_t m_TicksSinceLastMove;
	size_t m_TicksPerMove;
	glm::vec3 m_DistanceAlreadyMoved;

	Heirloom::Ref<Heirloom::SpriteRenderer> m_SpriteRenderer;
	Heirloom::Ref<std::unordered_set<Hex>> m_Hexagons;

	void MoveTowardsTargetHex(size_t totalTicksForMove);
	void AlignQBertSpritePosition() const;
	bool CheckIfWithinBounds() const;
	void OnKeyPressedEvent(Heirloom::KeyPressedEventArgs args);
};
