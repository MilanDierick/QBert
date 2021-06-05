// Author: Milan Dierick
// Created: 04/06/2021 6:13 PM
// Solution: QBert

#pragma once
#include "Heirloom.h"
#include "HexagonalGrid/Hexagon.h"

enum class TileState;

struct HexPositionChangedEventArgs : Heirloom::EventArgs
{
	[[nodiscard]] explicit HexPositionChangedEventArgs(const Hex newHex, const TileState requestTileState)
		: NewHex(newHex), RequestedTileState(requestTileState)
	{
	}

	Hex NewHex;
	TileState RequestedTileState;
};

struct OutOfBoundsEventArgs : Heirloom::EventArgs
{
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
