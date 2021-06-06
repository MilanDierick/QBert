// Author: Milan Dierick
// Created: 05/06/2021 6:14 PM
// Solution: QBert

#pragma once
#include "Heirloom.h"
#include "MovementController.h"
#include "SandboxScene.h"
#include "HexagonalGrid/Hexagon.h"
#include "HexagonalGrid/Layout.h"

class CoilyEggMovementController final : public Heirloom::Component, public MovementController
{
public:
	[[nodiscard]] CoilyEggMovementController(MovementControllerData data,
											 TileState preferredTileState,
											 Heirloom::WeakRef<Heirloom::GameObject> parent);

	Heirloom::Event<CoilyEggDestroyedEventArgs> CoilyEggDestroyedEvent;
	
	Heirloom::WeakRef<Heirloom::GameObject> GetParent() const override;
	void SetParent(Heirloom::Ref<Heirloom::GameObject> gameObject) override;

	void Update(Heirloom::Timestep ts) override;
	void Render() override;

private:
	Heirloom::WeakRef<Heirloom::GameObject> m_Parent;

	void SpawnCoily();
	void DesignateNextHexTarget();
};
