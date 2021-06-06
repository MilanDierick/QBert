#include "DiskMovementController.h"

#include "QBertMovementController.h"
#include "SandboxScene.h"

DiskMovementController::DiskMovementController(const MovementControllerData data,
											   const TileState preferredTileState,
											   const Heirloom::Ref<std::unordered_set<Hex>> hexagons,
											   const Heirloom::WeakRef<Heirloom::Transform> transform,
											   const Heirloom::WeakRef<Heirloom::GameObject> parent)
	: MovementController(data, preferredTileState, transform),
	  m_CurrentState(DiskMovementState::Idle),
	  m_Hexagons(hexagons),
	  m_Parent(parent)
{
}

Heirloom::WeakRef<Heirloom::GameObject> DiskMovementController::GetParent() const { return m_Parent; }

void DiskMovementController::SetParent(Heirloom::Ref<Heirloom::GameObject> const parent) { m_Parent = parent; }

void DiskMovementController::SetQBertMovementController(
	const Heirloom::WeakRef<QBertMovementController> qBertMovementController)
{
	m_QBertMovementController = qBertMovementController;
}

void DiskMovementController::Update(Heirloom::Timestep ts)
{
	HL_PROFILE_FUNCTION()

	UNREFERENCED_PARAMETER(ts);

	if (m_QBertMovementController.lock() == nullptr) return;
	if (m_QBertMovementController.lock()->GetCurrentHex().Q != GetCurrentHex().Q && m_QBertMovementController.lock()->
		GetCurrentHex().R != GetCurrentHex().R) { return; }

	switch (m_CurrentState)
	{
		case DiskMovementState::Idle: StartMovingDisk();
			break;
		case DiskMovementState::Moving: MoveDisk();
			break;
		default: break;
	}

	if (GetCurrentHex().Q == GetTargetHex().Q && GetCurrentHex().R == GetTargetHex().R)
	{
		m_CurrentState = DiskMovementState::Destination;
		FinishedMovingDisk();
	}
}

void DiskMovementController::Render()
{
}

void DiskMovementController::StartMovingDisk()
{
	HL_PROFILE_FUNCTION()

	m_CurrentState = DiskMovementState::Moving;
	m_QBertMovementController.lock()->SetCurrentState(QBertMovementState::Disk);
}

void DiskMovementController::MoveDisk()
{
	MovementController::Update(false);
	m_QBertMovementController.lock()->GetTransform().lock()->SetPosition(GetTransform().lock()->GetPosition());
}

void DiskMovementController::FinishedMovingDisk()
{
	HL_PROFILE_FUNCTION()

	const Hex dropOffHex = GetHexInDirection(GetHexInDirection(GetCurrentHex(), MovementDirection::SouthWest),
											 MovementDirection::SouthEast);

	m_CurrentState = DiskMovementState::Destination;
	m_QBertMovementController.lock()->SetCurrentState(QBertMovementState::Moving);

	m_QBertMovementController.lock()->SetCurrentHex(GetCurrentHex());
	m_QBertMovementController.lock()->SetTargetHex(dropOffHex);

	m_Parent.lock()->SetActive(false);
}
