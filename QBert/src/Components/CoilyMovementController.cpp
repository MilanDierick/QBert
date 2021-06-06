#include "CoilyMovementController.h"

#include "ScoreComponent.h"

CoilyMovementController::CoilyMovementController(const MovementControllerData data,
												 const TileState preferredTileState,
												 const Heirloom::WeakRef<Heirloom::GameObject> parent)
	: MovementController(data, preferredTileState, parent.lock()->GetTransform()), m_Parent(parent) { SetChaseTargetController(); }

Heirloom::WeakRef<Heirloom::GameObject> CoilyMovementController::GetParent() const { return m_Parent; }

void CoilyMovementController::SetParent(const Heirloom::Ref<Heirloom::GameObject> gameObject) { m_Parent = gameObject; }

void CoilyMovementController::Update(Heirloom::Timestep ts)
{
	UNREFERENCED_PARAMETER(ts);

	if (!m_ChaseTargetController.lock()) { return; }

	if (GetCurrentHex() == m_ChaseTargetController.lock()->GetCurrentHex())
	{
		if (!CheckIfWithinBounds(GetCurrentHex()))
		{
			const ScoreSourceEventArgs args = ScoreSourceEventArgs(ScoreSource::Coily);
			ScoreSourceEvent.Invoke(args);
			
			m_Parent.lock()->SetActive(false);
			return;
		}
		
		m_ChaseTargetController.lock()->Collide();
	}
	
	MovementController::Update(false);

	if (GetCurrentHex() == GetTargetHex()) { DesignateNextHexTarget(); }
}

void CoilyMovementController::Render()
{
}

void CoilyMovementController::DesignateNextHexTarget()
{
	const Hex chaseTargetHex = m_ChaseTargetController.lock()->GetCurrentHex();

	if (chaseTargetHex.Q < GetCurrentHex().Q && chaseTargetHex.R >= GetCurrentHex().R)
	{
		SetTargetHexInDirection(MovementDirection::NorthWest);
	}
	else if (chaseTargetHex.Q <= GetCurrentHex().Q && chaseTargetHex.R < GetCurrentHex().R)
	{
		if (GetCurrentHex().R == 0)
		{
			SetTargetHexInDirection(MovementDirection::NorthWest);
		}
		else
		{
			SetTargetHexInDirection(MovementDirection::SouthWest);
		}
	}
	else if (chaseTargetHex.Q >= GetCurrentHex().Q && chaseTargetHex.R > GetCurrentHex().R)
	{
		SetTargetHexInDirection(MovementDirection::NorthEast);
	}
	else if (chaseTargetHex.Q > GetCurrentHex().Q && chaseTargetHex.R <= GetCurrentHex().R)
	{
		if (GetCurrentHex().R == 0)
		{
			SetTargetHexInDirection(MovementDirection::NorthEast);
		}
		else
		{
			SetTargetHexInDirection(MovementDirection::SouthEast);
		}
	}
}

void CoilyMovementController::SetChaseTargetController()
{
	std::vector<Heirloom::Ref<Heirloom::GameObject>> gameObjects = m_Parent.lock()->GetCurrentScene()->GetGameObjects();

	for (Heirloom::Ref<Heirloom::GameObject> gameObject : gameObjects)
	{
		Heirloom::Ref<QBertMovementController> qBertMovementController = gameObject->GetComponent<QBertMovementController>();

		if (qBertMovementController)
		{
			m_ChaseTargetController = qBertMovementController;
		}
	}
}
