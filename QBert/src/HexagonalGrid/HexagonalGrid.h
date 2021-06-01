// Author: Milan Dierick
// Created: 01/06/2021 8:51 PM
// Solution: QBert

#pragma once

#include "Hexagon.h"
#include "Layout.h"
#include "glm/glm.hpp"
#include "glm/ext/scalar_constants.hpp"

// https://www.redblobgames.com/grids/hexagons/implementation.html
namespace HexagonalGrid
{
	inline glm::vec2 HexToPixel(const Layout layout, const Hex h)
	{
		const Orientation& m = layout.LayoutOrientation;
		const double x       = (m.F0 * h.Q + m.F1 * h.R) * layout.Size.x;
		const double y       = (m.F2 * h.Q + m.F3 * h.R) * layout.Size.y;
		return glm::vec2(x + layout.Origin.x, y + layout.Origin.y);
	}

	inline FractionalHex PixelToHex(const Layout layout, const glm::vec2 p)
	{
		const Orientation& m = layout.LayoutOrientation;
		const glm::vec2 pt   = glm::vec2((p.x - layout.Origin.x) / layout.Size.x,
										 (p.y - layout.Origin.y) / layout.Size.y);
		const double q = m.B0 * pt.x + m.B1 * pt.y;
		const double r = m.B2 * pt.x + m.B3 * pt.y;
		return FractionalHex(q, r, -q - r);
	}

	inline glm::vec2 HexCornerOffset(const Layout layout, const int corner)
	{
		const glm::vec2 size = layout.Size;
		const double angle   = 2.0 * glm::pi<double>() * (layout.LayoutOrientation.StartAngle + corner) / 6;
		return glm::vec2(size.x * cos(angle), size.y * sin(angle));
	}

	inline std::vector<glm::vec2> PolygonCorners(const Layout layout, const Hex h)
	{
		std::vector<glm::vec2> corners = {};
		const glm::vec2 center         = HexToPixel(layout, h);
		for (int i = 0; i < 6; i++)
		{
			const glm::vec2 offset = HexCornerOffset(layout, i);
			corners.push_back(glm::vec2(center.x + offset.x, center.y + offset.y));
		}
		return corners;
	}
}
