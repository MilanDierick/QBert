// Author: Milan Dierick
// Created: 05/06/2021 3:16 AM
// Solution: QBert

#pragma once
#include "Heirloom.h"

struct ScoreSourceEventArgs;

enum class ScoreSource
{
	Tile,
};

class ScoreComponent final : public Heirloom::Component
{
public:
	[[nodiscard]] explicit ScoreComponent(Heirloom::WeakRef<Heirloom::GameObject> parent, unsigned int initialScore = 0);

	Heirloom::WeakRef<Heirloom::GameObject> GetParent() const override;
	void SetParent(Heirloom::Ref<Heirloom::GameObject> gameObject) override;

	void Update(Heirloom::Timestep ts) override;
	void Render() override;

private:
	unsigned int m_Score;

	Heirloom::WeakRef<Heirloom::GameObject> m_Parent;

	void RegisterToAllScoreSourceEvents();
	void OnScoreSourceEvent(ScoreSourceEventArgs args);
};
