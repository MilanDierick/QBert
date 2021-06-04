// Author: Milan Dierick
// Created: 02/06/2021 10:37 PM
// Solution: QBert

#pragma once
#include <unordered_set>

// #include "DiskMovementController.h"
#include "Heirloom.h"

#include "HexagonalGrid/Hexagon.h"
#include "HexagonalGrid/Layout.h"

enum class QBertMovementState
{
	Idle,
	Moving,
	Disk,
	Floating
};

struct OutOfBoundsEventArgs : Heirloom::EventArgs
{
};

class QBertMovementController final : public Heirloom::Component
{
public:
	[[nodiscard]] explicit QBertMovementController(size_t ticksBetweenMoves,
												   size_t ticksPerMove,
												   Hex currentHex,
												   Heirloom::GameObject* parent,
												   Heirloom::Ref<std::unordered_set<Hex>> hexagons);

	Heirloom::Event<OutOfBoundsEventArgs> OutOfBoundsEvent;

	[[nodiscard]] Hex& GetCurrentHex();
	void SetCurrentHex(const Hex& currentHex);
	Heirloom::GameObject* GetParent() const override { return m_Parent; }
	void SetParent(Heirloom::GameObject* gameObject) override { m_Parent = gameObject; }
	[[nodiscard]] QBertMovementState& GetCurrentState() { return m_CurrentState; }
	void SetCurrentState(const QBertMovementState currentState) { m_CurrentState = currentState; }
	[[nodiscard]] Hex GetTargetHex() const { return m_TargetHex; }
	void SetTargetHex(const Hex targetHex) { m_TargetHex = targetHex; }

	void Update(Heirloom::Timestep ts) override;
	void Render() override;

private:
	Hex m_CurrentHex;
	Hex m_TargetHex;
	Layout m_HexagonalGridLayout;
	size_t m_TicksBetweenMoves;
	size_t m_TicksSinceLastMove;
	size_t m_TicksPerMove;
	glm::vec3 m_DistanceAlreadyMoved;
	QBertMovementState m_CurrentState;

	Heirloom::Ref<std::unordered_set<Hex>> m_Hexagons;

	Heirloom::GameObject* m_Parent;

	bool CheckIfOnDisk();
	void MoveTowardsTargetHex(size_t totalTicksForMove);
	void UpdateTransformPosition() const;
	bool CheckIfWithinBounds() const;
	void OnKeyPressedEvent(Heirloom::KeyPressedEventArgs args);
};
