#include "QBertMovementController.h"

#include "DiskMovementController.h"
#include "TileComponent.h"
#include "HexagonalGrid/HexagonalGrid.h"

QBertMovementController::QBertMovementController(const MovementControllerData data,
												 const Heirloom::WeakRef<Heirloom::GameObject> parent)
	: MovementController(data, TileState::Occupied, parent.lock()->GetTransform()), m_Parent(parent)
{
	HL_PROFILE_FUNCTION()

	OutOfBoundsEvent = Heirloom::Event<OutOfBoundsEventArgs>();
	RegisterMovableHexPositionChangedEventForAllTiles();
	Heirloom::Input::KeyPressedEvent += HL_BIND_EVENT_FN(QBertMovementController::OnKeyPressedEvent);
}

QBertMovementState QBertMovementController::GetCurrentState() const
{
	return m_CurrentState;
}

void QBertMovementController::SetCurrentState(const QBertMovementState currentState)
{
	m_CurrentState = currentState;
}

Heirloom::WeakRef<Heirloom::GameObject> QBertMovementController::GetParent() const { return m_Parent; }

void QBertMovementController::SetParent(const Heirloom::Ref<Heirloom::GameObject> gameObject)
{
	m_Parent = gameObject;
}

void QBertMovementController::Update(const Heirloom::Timestep ts)
{
	HL_PROFILE_FUNCTION()

	UNREFERENCED_PARAMETER(ts);

	if (m_CurrentState == QBertMovementState::Disk)
	{
		MovementController::Update(true);
		return;
	}

	m_CurrentState = QBertMovementState::Moving;
	MovementController::Update(false);

	CheckIfOnDisk();
}

void QBertMovementController::Render()
{
}

void QBertMovementController::Collide()
{
	const DamageTakenEventArgs args = DamageTakenEventArgs(GetCurrentHex());
	DamageTakenEvent.Invoke(args);
}

bool QBertMovementController::CheckIfOnDisk()
{
	HL_PROFILE_FUNCTION()

	std::vector<Heirloom::Ref<Heirloom::GameObject>> gameObjects = m_Parent.lock()->GetCurrentScene()->GetGameObjects();

	for (Heirloom::Ref<Heirloom::GameObject> gameObject : gameObjects)
	{
		Heirloom::Ref<DiskMovementController> diskController = gameObject->GetComponent<DiskMovementController>();

		if (diskController)
		{
			if (diskController->GetCurrentHex().Q == GetCurrentHex().Q && diskController->GetCurrentHex().R ==
				GetCurrentHex().R)
			{
				diskController->SetQBertMovementController(shared_from_this());
				return true;
			}
		}
	}

	return false;
}

void QBertMovementController::RegisterMovableHexPositionChangedEventForAllTiles()
{
	std::vector<Heirloom::Ref<Heirloom::GameObject>> gameObjects = m_Parent.lock()->GetCurrentScene()->GetGameObjects();

	for (Heirloom::Ref<Heirloom::GameObject> gameObject : gameObjects)
	{
		Heirloom::Ref<TileComponent> tileComponent = gameObject->GetComponent<TileComponent>();

		if (tileComponent) { tileComponent->RegisterMovableObjectHexPositionChangedEvent(HexChangedEvent); }
	}
}

void QBertMovementController::OnKeyPressedEvent(const Heirloom::KeyPressedEventArgs args)
{
	HL_PROFILE_FUNCTION()

	if (GetTicksSinceLastMove() < GetTicksBetweenMoves()) return;

	if (args.KeyCode == HL_KEY_KP_1)
	{
		SetTargetHexInDirection(MovementDirection::SouthWest);
	}
	else if (args.KeyCode == HL_KEY_KP_3)
	{
		SetTargetHexInDirection(MovementDirection::SouthEast);
	}
	else if (args.KeyCode == HL_KEY_KP_7)
	{
		SetTargetHexInDirection(MovementDirection::NorthWest);
	}
	else if (args.KeyCode == HL_KEY_KP_9)
	{
		SetTargetHexInDirection(MovementDirection::NorthEast);
	}
}
