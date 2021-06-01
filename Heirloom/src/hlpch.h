// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "Heirloom/Core/Core.h"
#include "Heirloom/Core/Log.h"

// TODO: Consider excluding this in distribution builds
#include "Heirloom/Profiler/Instrumentation.h"

#ifdef HL_PLATFORM_WINDOWS
#include <Windows.h>
#endif
