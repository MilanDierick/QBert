// Author: Milan Dierick
// Created: 02/06/2021 10:37 PM
// Solution: QBert

#pragma once
#include "Heirloom.h"
#include "MovementController.h"

enum class QBertMovementState
{
	Idle,
	Moving,
	Disk,
	Floating
};

class QBertMovementController final : public Heirloom::Component,
									  public MovementController,
									  public std::enable_shared_from_this<QBertMovementController>
{
public:
	[[nodiscard]] explicit QBertMovementController(MovementControllerData data,
												   Heirloom::WeakRef<Heirloom::GameObject> parent);

	Heirloom::Event<DamageTakenEventArgs> DamageTakenEvent;
	
	[[nodiscard]] QBertMovementState GetCurrentState() const;
	void SetCurrentState(QBertMovementState currentState);
	Heirloom::WeakRef<Heirloom::GameObject> GetParent() const override;
	void SetParent(Heirloom::Ref<Heirloom::GameObject> gameObject) override;

	void Update(Heirloom::Timestep ts) override;
	void Render() override;

	void Collide();

private:
	QBertMovementState m_CurrentState;

	Heirloom::WeakRef<Heirloom::GameObject> m_Parent;

	bool CheckIfOnDisk();
	void RegisterMovableHexPositionChangedEventForAllTiles();
	void OnKeyPressedEvent(Heirloom::KeyPressedEventArgs args);
};
