#include "DiskMovementController.h"

#include "QBertMovementController.h"
#include "SandboxScene.h"

DiskMovementController::DiskMovementController(const Hex currentHex,
											   const Layout hexagonalGridLayout,
											   const size_t ticksBetweenMoves,
											   const size_t ticksSinceLastMove,
											   const size_t ticksPerMove,
											   const Heirloom::Ref<std::unordered_set<Hex>> hexagons,
											   Heirloom::GameObject* const parent)
	: m_CurrentHex(currentHex),
	  m_TargetHex(Hex(static_cast<int>(SandboxScene::Configuration.InitialQBertPosition.x - 1),
					  static_cast<int>(SandboxScene::Configuration.InitialQBertPosition.y + 2),
					  -static_cast<int>(SandboxScene::Configuration.InitialQBertPosition.z))),
	  m_HexagonalGridLayout(hexagonalGridLayout),
	  m_TicksBetweenMoves(ticksBetweenMoves),
	  m_TicksSinceLastMove(ticksSinceLastMove),
	  m_TicksPerMove(ticksPerMove),
	  m_DistanceAlreadyMoved(0.0f),
	  m_CurrentState(DiskMovementState::Idle),
	  m_Hexagons(hexagons),
	  m_Parent(parent) { UpdateTransformPosition(); }

DiskMovementController::~DiskMovementController()
{
	HL_TRACE("DiskMovementController being destroyed!");
}

void DiskMovementController::Update(Heirloom::Timestep ts)
{
	UNREFERENCED_PARAMETER(ts);

	if (m_QBertMovementController == nullptr) return;
	if (m_QBertMovementController->GetCurrentHex().Q != m_CurrentHex.Q && m_QBertMovementController->GetCurrentHex().R
		!= m_CurrentHex.R) { return; }

	switch (m_CurrentState)
	{
		case DiskMovementState::Idle: StartMovingDisk();
			break;
		case DiskMovementState::Moving: MoveDisk();
			break;
		case DiskMovementState::Destination: FinishedMovingDisk();
			break;
	}
}

void DiskMovementController::Render()
{
}

void DiskMovementController::StartMovingDisk()
{
	m_CurrentState = DiskMovementState::Moving;
	m_QBertMovementController->SetCurrentState(QBertMovementState::Disk);
	MoveDisk();
}

void DiskMovementController::MoveDisk() { MoveTowardsTargetHex(m_TicksPerMove); }

void DiskMovementController::FinishedMovingDisk()
{
	Hex dropOffHex = HexNeighbor(m_CurrentHex, 2);
	dropOffHex     = HexNeighbor(dropOffHex, 1);

	m_CurrentState = DiskMovementState::Destination;
	m_QBertMovementController->SetCurrentState(QBertMovementState::Moving);

	m_QBertMovementController->SetCurrentHex(m_CurrentHex);
	m_QBertMovementController->SetTargetHex(dropOffHex);

	m_Parent->SetActive(false);
}

void DiskMovementController::UpdateTransformPosition() const
{
	const glm::vec3 alignedPosition = {HexagonalGrid::HexToPixel(m_HexagonalGridLayout, m_CurrentHex), 1.0f};
	m_Parent->GetTransform()->SetPosition(alignedPosition);
}

void DiskMovementController::MoveTowardsTargetHex(const size_t totalTicksForMove)
{
	const glm::vec3 currentHexPosition = {HexagonalGrid::HexToPixel(m_HexagonalGridLayout, m_CurrentHex), 0.0f};
	const glm::vec3 targetHexPosition  = {HexagonalGrid::HexToPixel(m_HexagonalGridLayout, m_TargetHex), 0.0f};
	glm::vec3 currentPosition          = m_Parent->GetTransform()->GetPosition();

	const glm::vec3 totalDistanceToMove = targetHexPosition - currentHexPosition;

	if (std::abs(m_DistanceAlreadyMoved.x) >= std::abs(totalDistanceToMove.x) && std::abs(m_DistanceAlreadyMoved.y) >=
		std::abs(totalDistanceToMove.y))
	{
		m_CurrentHex           = m_TargetHex;
		m_DistanceAlreadyMoved = glm::vec3(0.0f);
		UpdateTransformPosition();
		FinishedMovingDisk();
	}

	currentPosition.x += totalDistanceToMove.x / totalTicksForMove;
	currentPosition.y += totalDistanceToMove.y / totalTicksForMove;

	m_DistanceAlreadyMoved.x += totalDistanceToMove.x / totalTicksForMove;
	m_DistanceAlreadyMoved.y += totalDistanceToMove.y / totalTicksForMove;

	m_Parent->GetTransform()->SetPosition(currentPosition);
	m_QBertMovementController->GetParent()->GetTransform()->SetPosition(currentPosition);
}
