#include "QBertMovementController.h"

#include "HexagonalGrid/HexagonalGrid.h"

QBertMovementController::QBertMovementController(const size_t ticksBetweenMoves,
												 size_t ticksPerMove,
												 Hex currentHex,
												 const Heirloom::Ref<std::unordered_set<Hex>> hexagons)
	: m_CurrentHex(currentHex),
	  m_TargetHex(currentHex),
	  m_HexagonalGridLayout({ORIENTATION_POINTY, {1.0f, 0.85f}, {0.0f, 0.0f}}),
	  m_TicksBetweenMoves(ticksBetweenMoves),
	  m_TicksSinceLastMove(0),
	  m_TicksPerMove(ticksPerMove)
{
	m_Hexagons             = hexagons;
	OutOfBoundsEvent       = Heirloom::Event<OutOfBoundsEventArgs>();
	m_DistanceAlreadyMoved = glm::vec3(0.0f);
	Heirloom::Input::KeyPressedEvent += HL_BIND_EVENT_FN(QBertMovementController::OnKeyPressedEvent);
}

void QBertMovementController::Update(Heirloom::Timestep ts)
{
	UNREFERENCED_PARAMETER(ts);

	if (m_CurrentHex != m_TargetHex)
	{
		// Move towards the target hex over 100 ticks
		MoveTowardsTargetHex(m_TicksPerMove);
	}

	++m_TicksSinceLastMove;
}

void QBertMovementController::Render()
{
}

Hex& QBertMovementController::GetCurrentHex() { return m_CurrentHex; }

void QBertMovementController::SetCurrentHex(const Hex& currentHex) { m_CurrentHex = currentHex; }

Heirloom::Ref<Heirloom::SpriteRenderer> QBertMovementController::GetSpriteRenderer() const { return m_SpriteRenderer; }

void QBertMovementController::SetSpriteRenderer(const Heirloom::Ref<Heirloom::SpriteRenderer> spriteRenderer)
{
	m_SpriteRenderer = spriteRenderer;
	AlignQBertSpritePosition();
}

void QBertMovementController::MoveTowardsTargetHex(const size_t totalTicksForMove)
{
	const glm::vec3 currentHexPosition = {HexagonalGrid::HexToPixel(m_HexagonalGridLayout, m_CurrentHex), 0.0f};
	const glm::vec3 targetHexPosition  = {HexagonalGrid::HexToPixel(m_HexagonalGridLayout, m_TargetHex), 0.0f};
	glm::vec3 currentSpritePosition    = m_SpriteRenderer->GetSprite()->Position;

	const glm::vec3 totalDistanceToMove = targetHexPosition - currentHexPosition;
	
	if (std::abs(m_DistanceAlreadyMoved.x) >= std::abs(totalDistanceToMove.x) && std::abs(m_DistanceAlreadyMoved.y) >=
		std::abs(totalDistanceToMove.y))
	{
		m_CurrentHex           = m_TargetHex;
		m_DistanceAlreadyMoved = glm::vec3(0.0f);
		AlignQBertSpritePosition();

		if (!CheckIfWithinBounds())
		{
			const OutOfBoundsEventArgs outOfBoundsEventArgs = OutOfBoundsEventArgs();
			OutOfBoundsEvent.Invoke(outOfBoundsEventArgs);
		}
	}

	currentSpritePosition.x += totalDistanceToMove.x / totalTicksForMove;
	currentSpritePosition.y += totalDistanceToMove.y / totalTicksForMove;
	
	m_DistanceAlreadyMoved.x += totalDistanceToMove.x / totalTicksForMove;
	m_DistanceAlreadyMoved.y += totalDistanceToMove.y / totalTicksForMove;

	m_SpriteRenderer->GetSprite()->Position = currentSpritePosition;
}

void QBertMovementController::AlignQBertSpritePosition() const
{
	glm::vec3 alignedPosition = {HexagonalGrid::HexToPixel(m_HexagonalGridLayout, m_CurrentHex), 1.0f};

	alignedPosition.x += m_HexagonalGridLayout.Size.x - 0.75f;
	alignedPosition.y += m_HexagonalGridLayout.Size.y * 1.5f;

	// TODO: Move this to the SpriteRenderer, would need events in the transform though to make sure the SpriteRenderer can update the position of the sprite
	m_SpriteRenderer->GetSprite()->Position = alignedPosition;
}

bool QBertMovementController::CheckIfWithinBounds() const
{
	// TODO: Get rid of these magic numbers, these are the pyramid dimensions
	if (std::abs(m_CurrentHex.Q - -m_CurrentHex.R) > 6 || m_CurrentHex.Q < 0 || m_CurrentHex.R < 0) return false;
	return true;
}

void QBertMovementController::OnKeyPressedEvent(const Heirloom::KeyPressedEventArgs args)
{
	if (m_TicksSinceLastMove < m_TicksBetweenMoves) return;

	if (args.KeyCode == HL_KEY_KP_1)
	{
		m_TargetHex = HexNeighbor(m_CurrentHex, 2);
		AlignQBertSpritePosition();
	}
	else if (args.KeyCode == HL_KEY_KP_3)
	{
		m_TargetHex = HexNeighbor(m_CurrentHex, 1);
		AlignQBertSpritePosition();
	}
	else if (args.KeyCode == HL_KEY_KP_7)
	{
		m_TargetHex = HexNeighbor(m_CurrentHex, 4);
		AlignQBertSpritePosition();
	}
	else if (args.KeyCode == HL_KEY_KP_9)
	{
		m_TargetHex = HexNeighbor(m_CurrentHex, 5);
		AlignQBertSpritePosition();
	}

	m_TicksSinceLastMove = 0;
}
