﻿// Author: Milan Dierick
// Created: 03/06/2021 1:38 AM
// Solution: QBert

#pragma once
#include "Heirloom.h"
#include "QBertMovementController.h"

struct HealthDepletedEventArgs : Heirloom::EventArgs
{
	[[nodiscard]] HealthDepletedEventArgs(const int maximumLives, const int currentLives)
		: MaximumLives(maximumLives), CurrentLives(currentLives)
	{
	}

	int MaximumLives;
	int CurrentLives;
};

class HealthComponent final : public Heirloom::Component
{
public:
	[[nodiscard]] HealthComponent(int maximumLives, int currentLives);

	Heirloom::Event<HealthDepletedEventArgs> HealthDepletedEvent;

	Heirloom::WeakRef<Heirloom::GameObject> GetParent() const override { return m_Parent; }
	void SetParent(Heirloom::Ref<Heirloom::GameObject> gameObject) override { m_Parent = gameObject; }
	
	void Update(Heirloom::Timestep ts) override;
	void Render() override;

	void RegisterOutOfBoundsEventHandler(Heirloom::Ref<QBertMovementController> controller);

private:
	int m_MaximumLives;
	int m_CurrentLives;

	Heirloom::WeakRef<Heirloom::GameObject> m_Parent;

	void OnOutOfBoundsEvent(OutOfBoundsEventArgs args);
	void OnDamageTakenEvent(DamageTakenEventArgs args);
};
