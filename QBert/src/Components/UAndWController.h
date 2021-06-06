// Author: Milan Dierick
// Created: 07/06/2021 12:09 AM
// Solution: QBert

#pragma once
#include "Heirloom.h"
#include "MovementController.h"

class QBertMovementController;

enum class UAndWMovementDirection
{
	WestToEast,
	EastToWest
};

class UAndWController final : public Heirloom::Component, public MovementController
{
public:
	[[nodiscard]] UAndWController(MovementControllerData data,
								  TileState preferredTileState,
								  UAndWMovementDirection movementDirection,
								  Heirloom::WeakRef<Heirloom::GameObject> parent);

	Heirloom::WeakRef<Heirloom::GameObject> GetParent() const override;
	void SetParent(Heirloom::Ref<Heirloom::GameObject> gameObject) override;

	void Update(Heirloom::Timestep ts) override;
	void Render() override;

private:
	UAndWMovementDirection m_MovementDirection;

	Heirloom::WeakRef<Heirloom::GameObject> m_Parent;
	Heirloom::WeakRef<QBertMovementController> m_ChaseTargetController;

	void DesignateNextHexTarget();
	void SetChaseTargetController();
};
