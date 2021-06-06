// Author: Milan Dierick
// Created: 04/06/2021 6:13 PM
// Solution: QBert

#pragma once
#include "Heirloom.h"
#include "HexagonalGrid/Hexagon.h"

enum class ScoreSource;
enum class TileState;

struct ScoreSourceEventArgs : Heirloom::EventArgs
{
	[[nodiscard]] explicit ScoreSourceEventArgs(const ScoreSource scoreSource)
		: ScoreSource(scoreSource)
	{
	}

	ScoreSource ScoreSource;
};

struct HexChangedEventArgs : Heirloom::EventArgs
{
	[[nodiscard]] explicit HexChangedEventArgs(const Hex newHex, const TileState requestedTileState)
		: NewHex(newHex), RequestedTileState(requestedTileState)
	{
	}

	Hex NewHex;
	TileState RequestedTileState;
};

struct OutOfBoundsEventArgs : Heirloom::EventArgs
{
	[[nodiscard]] explicit OutOfBoundsEventArgs(const Hex hexagon)
		: Hexagon(hexagon)
	{
	}

	Hex Hexagon;
};

struct TileStateChangedEventArgs : Heirloom::EventArgs
{
	[[nodiscard]] TileStateChangedEventArgs(const bool firstOccupation, const Hex& tileHex)
		: FirstOccupation(firstOccupation), TileHex(tileHex)
	{
	}

	bool FirstOccupation;
	Hex TileHex;
};
