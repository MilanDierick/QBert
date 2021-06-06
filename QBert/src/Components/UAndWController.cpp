#include "UAndWController.h"

#include "QBertMovementController.h"

UAndWController::UAndWController(const MovementControllerData data,
								 const TileState preferredTileState,
								 const UAndWMovementDirection movementDirection,
								 const Heirloom::WeakRef<Heirloom::GameObject> parent)
	: MovementController(data, preferredTileState, parent.lock()->GetTransform()),
	  m_MovementDirection(movementDirection),
	  m_Parent(parent) { SetChaseTargetController(); }

Heirloom::WeakRef<Heirloom::GameObject> UAndWController::GetParent() const { return m_Parent; }

void UAndWController::SetParent(const Heirloom::Ref<Heirloom::GameObject> gameObject) { m_Parent = gameObject; }

void UAndWController::Update(Heirloom::Timestep ts)
{
	UNREFERENCED_PARAMETER(ts);

	if (m_ChaseTargetController.lock())
	{
		if (GetCurrentHex() == m_ChaseTargetController.lock()->GetCurrentHex())
		{
			m_ChaseTargetController.lock()->Collide();
		}
	}

	if (m_MovementDirection == UAndWMovementDirection::EastToWest)
	{
		if (!CheckIfWithinBounds(GetHexInDirection(GetCurrentHex(), MovementDirection::NorthWest)) && !
			CheckIfWithinBounds(GetHexInDirection(GetCurrentHex(), MovementDirection::West)) && !CheckIfWithinBounds(
				GetHexInDirection(GetCurrentHex(), MovementDirection::SouthWest)))
		{
			m_Parent.lock()->SetActive(false);
		}
	}
	else
	{
		if (!CheckIfWithinBounds(GetHexInDirection(GetCurrentHex(), MovementDirection::NorthEast)) && !
			CheckIfWithinBounds(GetHexInDirection(GetCurrentHex(), MovementDirection::East)) && !CheckIfWithinBounds(
				GetHexInDirection(GetCurrentHex(), MovementDirection::SouthEast)))
		{
			m_Parent.lock()->SetActive(false);
		}
	}

	MovementController::Update(false);

	if (GetCurrentHex() == GetTargetHex()) { DesignateNextHexTarget(); }
}

void UAndWController::Render()
{
}

void UAndWController::DesignateNextHexTarget()
{
	if (GetCurrentHex().R == 0)
	{
		const int direction = std::rand() % 2;

		if (m_MovementDirection == UAndWMovementDirection::EastToWest)
		{
			if (direction == 0) { SetTargetHexInDirection(MovementDirection::West); }
			else { SetTargetHexInDirection(MovementDirection::NorthWest); }
		}
		else
		{
			if (direction == 0) { SetTargetHexInDirection(MovementDirection::East); }
			else { SetTargetHexInDirection(MovementDirection::NorthEast); }
		}
	}
	else
	{
		const int direction = std::rand() % 3;

		if (m_MovementDirection == UAndWMovementDirection::EastToWest)
		{
			if (direction == 0) { SetTargetHexInDirection(MovementDirection::SouthWest); }
			if (direction == 1) { SetTargetHexInDirection(MovementDirection::West); }
			else { SetTargetHexInDirection(MovementDirection::NorthWest); }
		}
		else
		{
			if (direction == 0) { SetTargetHexInDirection(MovementDirection::SouthEast); }
			if (direction == 1) { SetTargetHexInDirection(MovementDirection::East); }
			else { SetTargetHexInDirection(MovementDirection::NorthEast); }
		}
	}
}

void UAndWController::SetChaseTargetController()
{
	std::vector<Heirloom::Ref<Heirloom::GameObject>> gameObjects = m_Parent.lock()->GetCurrentScene()->GetGameObjects();

	for (Heirloom::Ref<Heirloom::GameObject> gameObject : gameObjects)
	{
		Heirloom::Ref<QBertMovementController> qBertMovementController = gameObject->GetComponent<
			QBertMovementController>();

		if (qBertMovementController) { m_ChaseTargetController = qBertMovementController; }
	}
}
