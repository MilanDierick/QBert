#include "CoilyEggMovementController.h"

CoilyEggMovementController::CoilyEggMovementController(const MovementControllerData data,
													   const TileState preferredTileState,
													   const Heirloom::WeakRef<Heirloom::GameObject> parent)
	: MovementController(data, preferredTileState, parent.lock()->GetTransform()), m_Parent(parent)
{
	SetTicksSinceLastMove(0);
}

Heirloom::WeakRef<Heirloom::GameObject> CoilyEggMovementController::GetParent() const
{
	return m_Parent;
}

void CoilyEggMovementController::SetParent(Heirloom::Ref<Heirloom::GameObject> gameObject)
{
	m_Parent = gameObject;
}

void CoilyEggMovementController::Update(Heirloom::Timestep ts)
{
	UNREFERENCED_PARAMETER(ts);

	MovementController::Update(false);
	
	if (GetCurrentHex().R == 0)
	{
		if (GetTicksSinceLastMove() >= GetTicksBetweenMoves() * 2)
		{
			SpawnCoily();
		}
		
		return;
	}
	
	if (GetCurrentHex().Q == GetTargetHex().Q && GetCurrentHex().R == GetTargetHex().R)
	{
		DesignateNextHexTarget();
	}
}

void CoilyEggMovementController::Render()
{
}

void CoilyEggMovementController::SpawnCoily()
{
	m_Parent.lock()->SetActive(false);

	const CoilyEggDestroyedEventArgs args = CoilyEggDestroyedEventArgs(GetCurrentHex());
	CoilyEggDestroyedEvent.Invoke(args);
}

void CoilyEggMovementController::DesignateNextHexTarget()
{
	if (std::rand() % 2 == 1)
	{
		SetTargetHexInDirection(MovementDirection::SouthEast);
	}
	else
	{
		SetTargetHexInDirection(MovementDirection::SouthWest);
	}
}
