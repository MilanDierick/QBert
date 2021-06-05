#include "TileComponent.h"

#include "EventArgs.h"

TileComponent::TileComponent(const Hex currentHex,
							 const Heirloom::WeakRef<Heirloom::GameObject> parent,
							 const Heirloom::Ref<Heirloom::Sprite> sprite,
							 const Heirloom::Ref<Heirloom::Sprite> alternateSprite,
							 const bool firstOccupation)
	: TileOccupiedEvent(Heirloom::Event<TileStateChangedEventArgs>()),
	  m_FirstOccupation(firstOccupation),
	  m_CurrentHex(currentHex),
	  m_TileState(TileState::Clear),
	  m_Parent(parent),
	  m_Sprite(sprite),
	  m_AlternateSprite(alternateSprite)
{
}

Heirloom::WeakRef<Heirloom::GameObject> TileComponent::GetParent() const { return m_Parent; }

void TileComponent::SetParent(const Heirloom::Ref<Heirloom::GameObject> gameObject) { m_Parent = gameObject; }

void TileComponent::Update(Heirloom::Timestep ts)
{
	UNREFERENCED_PARAMETER(ts);
}

void TileComponent::Render()
{
}

void TileComponent::RegisterMovableObjectHexPositionChangedEvent(Heirloom::Event<HexPositionChangedEventArgs>& event)
{
	event += HL_BIND_EVENT_FN(TileComponent::OnMovableObjectHexPositionChanged);
}

void TileComponent::OnMovableObjectHexPositionChanged(const HexPositionChangedEventArgs args)
{
	if (!(args.NewHex.Q == m_CurrentHex.Q && args.NewHex.R == m_CurrentHex.R)) return;

	ChangeTileState(args.RequestedTileState);
}

void TileComponent::ChangeTileState(const TileState newState)
{
	if (newState == m_TileState) return;

	m_FirstOccupation = false;
	m_TileState       = newState;

	ChangeTileSprite();

	const TileStateChangedEventArgs args = TileStateChangedEventArgs(m_FirstOccupation, m_CurrentHex);
	
	TileOccupiedEvent.Invoke(args);
}

void TileComponent::ChangeTileSprite()
{
	m_Parent.lock()->GetComponent<Heirloom::SpriteRenderer>()->SetSprite(
		m_TileState == TileState::Clear ? m_Sprite : m_AlternateSprite);
}
