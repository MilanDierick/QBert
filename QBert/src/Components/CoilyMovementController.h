// Author: Milan Dierick
// Created: 06/06/2021 10:07 PM
// Solution: QBert

#pragma once
#include "Heirloom.h"
#include "IScoreSource.h"
#include "MovementController.h"
#include "QBertMovementController.h"

class CoilyMovementController final : public Heirloom::Component, public MovementController, public IScoreSource
{
public:
	[[nodiscard]] CoilyMovementController(MovementControllerData data,
										  TileState preferredTileState,
										  Heirloom::WeakRef<Heirloom::GameObject> parent);

	Heirloom::WeakRef<Heirloom::GameObject> GetParent() const override;
	void SetParent(Heirloom::Ref<Heirloom::GameObject> gameObject) override;

	void Update(Heirloom::Timestep ts) override;
	void Render() override;

private:
	Heirloom::WeakRef<Heirloom::GameObject> m_Parent;
	Heirloom::WeakRef<QBertMovementController> m_ChaseTargetController;

	void DesignateNextHexTarget();
	void SetChaseTargetController();
};
