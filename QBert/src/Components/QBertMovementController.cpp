#include "QBertMovementController.h"

#include "SandboxScene.h"
#include "HexagonalGrid/HexagonalGrid.h"

QBertMovementController::QBertMovementController(const size_t ticksBetweenMoves,
												 size_t ticksPerMove,
												 Hex currentHex,
												 Heirloom::GameObject* parent,
												 const Heirloom::Ref<std::unordered_set<Hex>> hexagons)
	: m_CurrentHex(currentHex),
	  m_TargetHex(currentHex),
	  m_HexagonalGridLayout({ORIENTATION_POINTY, {1.0f, 0.85f}, {0.0f, 0.0f}}),
	  m_TicksBetweenMoves(ticksBetweenMoves),
	  m_TicksSinceLastMove(0),
	  m_TicksPerMove(ticksPerMove),
	  m_Parent(parent)
{
	m_Hexagons             = hexagons;
	OutOfBoundsEvent       = Heirloom::Event<OutOfBoundsEventArgs>();
	m_DistanceAlreadyMoved = glm::vec3(0.0f);
	UpdateTransformPosition();
	Heirloom::Input::KeyPressedEvent += HL_BIND_EVENT_FN(QBertMovementController::OnKeyPressedEvent);
}

void QBertMovementController::Update(Heirloom::Timestep ts)
{
	UNREFERENCED_PARAMETER(ts);

	if (m_CurrentState == QBertMovementState::Disk)
	{
		UpdateTransformPosition();
		return;
	}

	if (m_CurrentHex != m_TargetHex)
	{
		m_CurrentState = QBertMovementState::Moving;
		MoveTowardsTargetHex(m_TicksPerMove);
	}

	++m_TicksSinceLastMove;
}

void QBertMovementController::Render()
{
}

Hex& QBertMovementController::GetCurrentHex() { return m_CurrentHex; }

void QBertMovementController::SetCurrentHex(const Hex& currentHex) { m_CurrentHex = currentHex; }

bool QBertMovementController::CheckIfOnDisk()
{
	// std::vector<Heirloom::Ref<Heirloom::GameObject>> gameObjects = m_Parent->GetCurrentScene()->GetGameObjects();
	//
	// for (Heirloom::Ref<Heirloom::GameObject> gameObject : gameObjects)
	// {
	// 	Heirloom::Ref<DiskMovementController> diskController = gameObject->GetComponent<DiskMovementController>();
	// 	
	// 	if (diskController)
	// 	{
	// 		if (diskController->GetCurrentHex().Q == m_CurrentHex.Q && diskController->GetCurrentHex().R == m_CurrentHex.R)
	// 		{
	// 			diskController->SetQBertMovementController(this);
	// 			return true;
	// 		}
	// 	}
	// }

	return false;
}

void QBertMovementController::MoveTowardsTargetHex(const size_t totalTicksForMove)
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

		if (!CheckIfWithinBounds())
		{
			// TODO: Check if we landed on a disk
			if (!CheckIfOnDisk())
			{
				const OutOfBoundsEventArgs outOfBoundsEventArgs = OutOfBoundsEventArgs();
				OutOfBoundsEvent.Invoke(outOfBoundsEventArgs);
			}
		}
	}

	currentPosition.x += totalDistanceToMove.x / totalTicksForMove;
	currentPosition.y += totalDistanceToMove.y / totalTicksForMove;

	m_DistanceAlreadyMoved.x += totalDistanceToMove.x / totalTicksForMove;
	m_DistanceAlreadyMoved.y += totalDistanceToMove.y / totalTicksForMove;

	m_Parent->GetTransform()->SetPosition(currentPosition);
}

void QBertMovementController::UpdateTransformPosition() const
{
	const glm::vec3 alignedPosition = {HexagonalGrid::HexToPixel(m_HexagonalGridLayout, m_CurrentHex), 1.0f};
	m_Parent->GetTransform()->SetPosition(alignedPosition);
}

bool QBertMovementController::CheckIfWithinBounds() const
{
	if (std::abs(m_CurrentHex.Q - -m_CurrentHex.R) > SandboxScene::Configuration.PyramidWidth - 1 || m_CurrentHex.Q < 0
		|| m_CurrentHex.R < 0) return false;
	return true;
}

void QBertMovementController::OnKeyPressedEvent(const Heirloom::KeyPressedEventArgs args)
{
	if (m_TicksSinceLastMove < m_TicksBetweenMoves) return;

	if (args.KeyCode == HL_KEY_KP_1)
	{
		m_TargetHex = HexNeighbor(m_CurrentHex, 2);
		UpdateTransformPosition();
	}
	else if (args.KeyCode == HL_KEY_KP_3)
	{
		m_TargetHex = HexNeighbor(m_CurrentHex, 1);
		UpdateTransformPosition();
	}
	else if (args.KeyCode == HL_KEY_KP_7)
	{
		m_TargetHex = HexNeighbor(m_CurrentHex, 4);
		UpdateTransformPosition();
	}
	else if (args.KeyCode == HL_KEY_KP_9)
	{
		m_TargetHex = HexNeighbor(m_CurrentHex, 5);
		UpdateTransformPosition();
	}

	m_TicksSinceLastMove = 0;
}
