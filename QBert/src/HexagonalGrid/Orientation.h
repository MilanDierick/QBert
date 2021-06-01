// Author: Milan Dierick
// Created: 01/06/2021 8:44 PM
// Solution: QBert

#pragma once

#include "glm/glm.hpp"

// https://www.redblobgames.com/grids/hexagons/implementation.html
struct Orientation
{
	const double F0, F1, F2, F3;
	const double B0, B1, B2, B3;
	const double StartAngle; // in multiples of 60°

	Orientation(const double f0,
				const double f1,
				const double f2,
				const double f3,
				const double b0,
				const double b1,
				const double b2,
				const double b3,
				const double startAngle)
		: F0(f0), F1(f1), F2(f2), F3(f3), B0(b0), B1(b1), B2(b2), B3(b3), StartAngle(startAngle)
	{
	}
};

static const Orientation ORIENTATION_POINTY = Orientation(sqrt(3.0),
														  sqrt(3.0) / 2.0,
														  0.0,
														  3.0 / 2.0,
														  sqrt(3.0) / 3.0,
														  -1.0 / 3.0,
														  0.0,
														  2.0 / 3.0,
														  0.5);
static const Orientation ORIENTATION_FLAT = Orientation(3.0 / 2.0,
														0.0,
														sqrt(3.0) / 2.0,
														sqrt(3.0),
														2.0 / 3.0,
														0.0,
														-1.0 / 3.0,
														sqrt(3.0) / 3.0,
														0.0);
