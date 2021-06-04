// Author: Milan Dierick
// Created: 03/06/2021 11:35 PM
// Solution: QBert

#pragma once
#include <unordered_set>

#include "Heirloom.h"
#include "HexagonalGrid/Hexagon.h"
#include "HexagonalGrid/HexagonalGrid.h"
#include "HexagonalGrid/Layout.h"

class QBertMovementController;

enum class DiskMovementState
{
	Idle,
	Moving,
	Destination
};

class DiskMovementController final : public Heirloom::Component
{
public:
	[[nodiscard]] DiskMovementController(Hex currentHex,
										 Layout hexagonalGridLayout,
										 size_t ticksBetweenMoves,
										 size_t ticksSinceLastMove,
										 size_t ticksPerMove,
										 Heirloom::Ref<std::unordered_set<Hex>> hexagons,
										 Heirloom::GameObject* parent);

	[[nodiscard]] Heirloom::GameObject* GetParent() const override { return m_Parent; }
	void SetParent(Heirloom::GameObject* const parent) override { m_Parent = parent; }
	[[nodiscard]] Hex GetCurrentHex() const { return m_CurrentHex; }

	void SetQBertMovementController(QBertMovementController* qBertMovementController)
	{
		m_QBertMovementController = qBertMovementController;
	}

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
	DiskMovementState m_CurrentState;

	QBertMovementController* m_QBertMovementController = nullptr;
	Heirloom::Ref<std::unordered_set<Hex>> m_Hexagons;

	Heirloom::GameObject* m_Parent;

	void StartMovingDisk();
	void MoveDisk();
	void FinishedMovingDisk();
	void UpdateTransformPosition() const;
	void MoveTowardsTargetHex(size_t totalTicksForMove);
};
