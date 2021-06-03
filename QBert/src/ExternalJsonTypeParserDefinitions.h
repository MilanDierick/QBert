// Author: Milan Dierick
// Created: 03/06/2021 4:13 AM
// Solution: QBert

#pragma once
#include "Heirloom.h"

namespace glm
{
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(glm::vec2, g, r, s, t, x, y)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(glm::vec3, b, g, p, r, s, t, x, y, z)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(glm::vec4, a, b, g, p, q, r, s, t, w, x, y, z)
}