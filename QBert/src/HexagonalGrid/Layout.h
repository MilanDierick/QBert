// Author: Milan Dierick
// Created: 01/06/2021 8:48 PM
// Solution: QBert

#pragma once
#include "Orientation.h"

// https://www.redblobgames.com/grids/hexagons/implementation.html
struct Layout
{
	const Orientation LayoutOrientation;
	const glm::vec2 Size;
	const glm::vec2 Origin;

	Layout(const Orientation orientation, const glm::vec2 size, const glm::vec2 origin)
		: LayoutOrientation(orientation), Size(size), Origin(origin)
	{
	}
};
