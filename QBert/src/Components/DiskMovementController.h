// Author: Milan Dierick
// Created: 03/06/2021 11:35 PM
// Solution: QBert

#pragma once
#include <unordered_set>

#include "Heirloom.h"
#include "MovementController.h"
#include "HexagonalGrid/Hexagon.h"

class QBertMovementController;

enum class DiskMovementState
{
	Idle,
	Moving,
	Destination
};

class DiskMovementController final : public Heirloom::Component, public MovementController
{
public:
	[[nodiscard]] DiskMovementController(MovementControllerData data,
										 TileState preferredTileState,
										 Heirloom::Ref<std::unordered_set<Hex>> hexagons,
										 Heirloom::WeakRef<Heirloom::Transform> transform,
										 Heirloom::WeakRef<Heirloom::GameObject> parent);

	[[nodiscard]] Heirloom::WeakRef<Heirloom::GameObject> GetParent() const override;
	void SetParent(Heirloom::Ref<Heirloom::GameObject> parent) override;
	void SetQBertMovementController(Heirloom::WeakRef<QBertMovementController> qBertMovementController);

	void Update(Heirloom::Timestep ts) override;
	void Render() override;

private:
	DiskMovementState m_CurrentState;

	Heirloom::WeakRef<QBertMovementController> m_QBertMovementController;
	Heirloom::Ref<std::unordered_set<Hex>> m_Hexagons;

	Heirloom::WeakRef<Heirloom::GameObject> m_Parent;

	void StartMovingDisk();
	void MoveDisk();
	void FinishedMovingDisk();
};
