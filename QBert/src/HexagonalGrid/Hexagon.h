// Author: Milan Dierick
// Created: 01/06/2021 8:29 PM
// Solution: QBert

#pragma once

#include <vector>

// https://www.redblobgames.com/grids/hexagons/implementation.html
template <typename Number, int W>
struct Hexagon
{
	Number Q, R, S;

	Hexagon(Number q, Number r)
		: Q(q), R(r), S(-q - r)
	{
	}

	Hexagon(Number q, Number r, Number s)
		: Q(q), R(r), S(s)
	{
	}

	Hexagon() = default;

	Hexagon& operator=(const Hexagon& other)
	{
		if (this == &other) return *this;
		Q = other.Q;
		R = other.R;
		S = other.S;
		return *this;
	}
};

typedef Hexagon<int, 1> Hex;
typedef Hexagon<int, 0> HexDifference;
typedef Hexagon<double, 1> FractionalHex;
typedef Hexagon<double, 0> FractionalHexDifference;

inline bool operator ==(const Hex a, const Hex b) { return a.Q == b.Q && a.R == b.R && a.S == b.S; }
inline bool operator !=(const Hex a, const Hex b) { return !(a == b); }

inline Hex HexagonAdd(const Hex a, const Hex b) { return Hex(a.Q + b.Q, a.R + b.R, a.S + b.S); }

inline Hex HexagonSubtract(const Hex a, const Hex b) { return Hex(a.Q - b.Q, a.R - b.R, a.S - b.S); }

inline Hex HexagonMultiply(const Hex a, const int k) { return Hex(a.Q * k, a.R * k, a.S * k); }

inline int HexagonLength(const Hex hex) { return (abs(hex.Q) + abs(hex.R) + abs(hex.S)) / 2; }

inline int HexagonDistance(const Hex a, const Hex b) { return HexagonLength(HexagonSubtract(a, b)); }

const std::vector HEX_DIRECTIONS = {
	Hex(1, 0, -1),
	Hex(1, -1, 0),
	Hex(0, -1, 1),
	Hex(-1, 0, 1),
	Hex(-1, 1, 0),
	Hex(0, 1, -1)
};

inline Hex HexDirection(const int direction)
{
	assert(0 <= direction && direction < 6);
	return HEX_DIRECTIONS[direction];
}

inline Hex HexNeighbor(const Hex hex, const int direction) { return HexagonAdd(hex, HexDirection(direction)); }

inline Hex HexRound(FractionalHex h)
{
	int q              = static_cast<int>(round(h.Q));
	int r              = static_cast<int>(round(h.R));
	int s              = static_cast<int>(round(h.S));
	const double qDiff = abs(q - h.Q);
	const double rDiff = abs(r - h.R);
	if (const double sDiff = abs(s - h.S); qDiff > rDiff && qDiff > sDiff) { q = -r - s; }
	else if (rDiff > sDiff) { r = -q - s; }
	else { s = -q - r; }
	return Hex(q, r, s);
}

// ReSharper disable once CppInconsistentNaming
namespace std
{
	template <>
	struct hash<Hex>
	{
		size_t operator()(const Hex& h) const noexcept
		{
			const hash<int> intHash;
			const size_t hq = intHash(h.Q);
			const size_t hr = intHash(h.R);
			return hq ^ hr + 0x9e3779b9 + (hq << 6) + (hq >> 2);
		}
	};
}
