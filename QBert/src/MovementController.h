// Author: Milan Dierick
// Created: 06/06/2021 1:36 AM
// Solution: QBert

#pragma once
#include "Heirloom.h"

#include "EventArgs.h"
#include "glm/vec3.hpp"
#include "Heirloom/Core/Core.h"
#include "HexagonalGrid/Hexagon.h"
#include "HexagonalGrid/Layout.h"

namespace Heirloom
{
	class Transform;
}

enum class MovementDirection
{
	NorthEast = 5,
	East = 0,
	SouthEast = 1,
	SouthWest = 2,
	West = 3,
	NorthWest = 4
};

struct MovementControllerData
{
	Hex CurrentHex;
	Hex TargetHex;
	int TicksBetweenMoves;
	int TicksPerMove;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(MovementControllerData, CurrentHex, TargetHex, TicksBetweenMoves, TicksPerMove);
};

class MovementController
{
public:
	virtual ~MovementController() = default;
	[[nodiscard]] MovementController(MovementControllerData data,
									 TileState preferredTileState,
									 Heirloom::WeakRef<Heirloom::Transform> transform);

	Heirloom::Event<HexChangedEventArgs> HexChangedEvent;
	Heirloom::Event<OutOfBoundsEventArgs> OutOfBoundsEvent;

	[[nodiscard]] Hex GetCurrentHex() const;
	[[nodiscard]] Hex GetTargetHex() const;
	[[nodiscard]] Layout GetHexagonalGridLayout() const;
	[[nodiscard]] size_t GetTicksBetweenMoves() const;
	[[nodiscard]] size_t GetTicksSinceLastMove() const;
	[[nodiscard]] size_t GetTicksPerMove() const;
	[[nodiscard]] glm::vec3 GetDistanceAlreadyMoved() const;
	[[nodiscard]] Heirloom::WeakRef<Heirloom::Transform> GetTransform() const;
	void SetCurrentHex(Hex currentHex);
	void SetTargetHex(Hex targetHex);
	void SetTicksBetweenMoves(size_t ticksBetweenMoves);
	void SetTicksSinceLastMove(size_t ticksSinceLastMove);
	void SetTicksPerMove(size_t ticksPerMove);
	void SetDistanceAlreadyMoved(glm::vec3 distanceAlreadyMoved);
	void SetTransform(Heirloom::WeakRef<Heirloom::Transform> transform);

	virtual void Update(bool updateTransformPositionOnly);

	static Hex GetHexInDirection(Hex origin, MovementDirection direction);
	void SetTargetHexInDirection(MovementDirection direction);
	bool CheckIfWithinBounds(Hex hexagon) const;

private:
	Hex m_CurrentHex;
	Hex m_TargetHex;
	Layout m_HexagonalGridLayout;
	size_t m_TicksBetweenMoves;
	size_t m_TicksSinceLastMove;
	size_t m_TicksPerMove;
	glm::vec3 m_DistanceAlreadyMoved;

	TileState m_PreferredTileState;

	Heirloom::WeakRef<Heirloom::Transform> m_Transform;

	void UpdateTransformPosition() const;
	void MoveTowardsTargetHex();
};
