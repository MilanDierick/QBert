// Author: Milan Dierick
// Created: 04/06/2021 6:02 PM
// Solution: QBert

#pragma once
#include "Heirloom.h"
#include "IScoreSource.h"
#include "HexagonalGrid/Hexagon.h"

struct HexPositionChangedEventArgs;
struct TileStateChangedEventArgs;

enum class TileState
{
	Clear,
	Occupied
};

class TileComponent final : public Heirloom::Component, public IScoreSource
{
public:
	[[nodiscard]] explicit TileComponent(Hex currentHex,
										 Heirloom::WeakRef<Heirloom::GameObject> parent,
										 Heirloom::Ref<Heirloom::Sprite> sprite,
										 Heirloom::Ref<Heirloom::Sprite> alternateSprite,
										 bool firstOccupation = true);

	Heirloom::Event<TileStateChangedEventArgs> TileOccupiedEvent;

	Heirloom::WeakRef<Heirloom::GameObject> GetParent() const override;
	void SetParent(Heirloom::Ref<Heirloom::GameObject> gameObject) override;

	void Update(Heirloom::Timestep ts) override;
	void Render() override;

	void RegisterMovableObjectHexPositionChangedEvent(Heirloom::Event<HexPositionChangedEventArgs>& event);

private:
	bool m_FirstOccupation;

	Hex m_CurrentHex;
	TileState m_TileState;

	Heirloom::WeakRef<Heirloom::GameObject> m_Parent;

	Heirloom::Ref<Heirloom::Sprite> m_Sprite;
	Heirloom::Ref<Heirloom::Sprite> m_AlternateSprite;

	void OnMovableObjectHexPositionChanged(HexPositionChangedEventArgs args);
	void ChangeTileState(TileState newState);
	void ChangeTileSprite();
};
