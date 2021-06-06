#include "MovementController.h"

#include "EventArgs.h"
#include "SandboxScene.h"
#include "Components/TileComponent.h"
#include "HexagonalGrid/HexagonalGrid.h"

MovementController::MovementController(const MovementControllerData data,
									   TileState preferredTileState,
									   const Heirloom::WeakRef<Heirloom::Transform> transform)
	: m_CurrentHex(data.CurrentHex),
	  m_TargetHex(data.TargetHex),
	  m_HexagonalGridLayout({ORIENTATION_POINTY, {1.0f, 0.85f}, {0.0f, 0.0f}}),
	  m_TicksBetweenMoves(data.TicksBetweenMoves),
	  m_TicksSinceLastMove(data.TicksBetweenMoves),
	  m_TicksPerMove(data.TicksPerMove),
	  m_DistanceAlreadyMoved(0.0f),
	  m_PreferredTileState(preferredTileState),
	  m_Transform(transform)
{
	HexChangedEvent  = Heirloom::Event<HexChangedEventArgs>();
	OutOfBoundsEvent = Heirloom::Event<OutOfBoundsEventArgs>();

	m_Transform.lock()->SetPosition({HexagonalGrid::HexToPixel(m_HexagonalGridLayout, m_CurrentHex), 0.0f});
}

Hex MovementController::GetCurrentHex() const { return m_CurrentHex; }

Hex MovementController::GetTargetHex() const { return m_TargetHex; }

Layout MovementController::GetHexagonalGridLayout() const { return m_HexagonalGridLayout; }

size_t MovementController::GetTicksBetweenMoves() const { return m_TicksBetweenMoves; }

size_t MovementController::GetTicksSinceLastMove() const { return m_TicksSinceLastMove; }

size_t MovementController::GetTicksPerMove() const { return m_TicksPerMove; }

glm::vec3 MovementController::GetDistanceAlreadyMoved() const { return m_DistanceAlreadyMoved; }

Heirloom::WeakRef<Heirloom::Transform> MovementController::GetTransform() const { return m_Transform; }

void MovementController::SetCurrentHex(const Hex currentHex) { m_CurrentHex = currentHex; }

void MovementController::SetTargetHex(const Hex targetHex) { m_TargetHex = targetHex; }

void MovementController::SetTicksBetweenMoves(const size_t ticksBetweenMoves)
{
	m_TicksBetweenMoves = ticksBetweenMoves;
}

void MovementController::SetTicksSinceLastMove(const size_t ticksSinceLastMove)
{
	m_TicksSinceLastMove = ticksSinceLastMove;
}

void MovementController::SetTicksPerMove(const size_t ticksPerMove) { m_TicksPerMove = ticksPerMove; }

void MovementController::SetDistanceAlreadyMoved(const glm::vec3 distanceAlreadyMoved)
{
	m_DistanceAlreadyMoved = distanceAlreadyMoved;
}

void MovementController::SetTransform(const Heirloom::WeakRef<Heirloom::Transform> transform)
{
	m_Transform = transform;
}

void MovementController::Update(const bool updateTransformPositionOnly = false)
{
	m_TicksSinceLastMove += 1;

	if (updateTransformPositionOnly)
	{
		UpdateTransformPosition();
		return;
	}

	if (GetCurrentHex() != GetTargetHex()) { MoveTowardsTargetHex(); }
}

Hex MovementController::GetHexInDirection(const Hex origin, MovementDirection direction)
{
	return HexNeighbor(origin, static_cast<int>(direction));
}

void MovementController::SetTargetHexInDirection(const MovementDirection direction)
{
	if (m_TicksSinceLastMove < m_TicksBetweenMoves) { return; };
	
	m_TargetHex = GetHexInDirection(m_CurrentHex, direction);

	m_TicksSinceLastMove = 0;
}

bool MovementController::CheckIfWithinBounds(const Hex hexagon) const
{
	HL_PROFILE_FUNCTION()

	if (std::abs(hexagon.Q - -hexagon.R) > SandboxScene::Configuration.PyramidWidth - 1 || hexagon.Q < 0 || hexagon.R <
		0) { return false; }
	return true;
}

void MovementController::UpdateTransformPosition() const
{
	HL_PROFILE_FUNCTION()

	const glm::vec3 alignedPosition = {HexagonalGrid::HexToPixel(m_HexagonalGridLayout, m_CurrentHex), 1.0f};
	m_Transform.lock()->SetPosition(alignedPosition);
}

void MovementController::MoveTowardsTargetHex()
{
	HL_PROFILE_FUNCTION()

	const glm::vec3 currentHexPosition = {HexagonalGrid::HexToPixel(m_HexagonalGridLayout, m_CurrentHex), 0.0f};
	const glm::vec3 targetHexPosition  = {HexagonalGrid::HexToPixel(m_HexagonalGridLayout, m_TargetHex), 0.0f};
	glm::vec3 currentPosition          = m_Transform.lock()->GetPosition();

	const glm::vec3 totalDistanceToMove = targetHexPosition - currentHexPosition;

	if (std::abs(m_DistanceAlreadyMoved.x) >= std::abs(totalDistanceToMove.x) && std::abs(m_DistanceAlreadyMoved.y) >=
		std::abs(totalDistanceToMove.y))
	{
		m_CurrentHex           = m_TargetHex;
		m_DistanceAlreadyMoved = glm::vec3(0.0f);
		UpdateTransformPosition();

		const HexChangedEventArgs args = HexChangedEventArgs(m_CurrentHex, m_PreferredTileState);

		HexChangedEvent.Invoke(args);

		if (!CheckIfWithinBounds(m_CurrentHex))
		{
			const OutOfBoundsEventArgs outOfBoundsEventArgs = OutOfBoundsEventArgs(m_CurrentHex);
			OutOfBoundsEvent.Invoke(outOfBoundsEventArgs);
		}
	}

	currentPosition.x += totalDistanceToMove.x / m_TicksPerMove;
	currentPosition.y += totalDistanceToMove.y / m_TicksPerMove;

	m_DistanceAlreadyMoved.x += totalDistanceToMove.x / m_TicksPerMove;
	m_DistanceAlreadyMoved.y += totalDistanceToMove.y / m_TicksPerMove;

	m_Transform.lock()->SetPosition(currentPosition);
}
