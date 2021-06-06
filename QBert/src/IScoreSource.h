// Author: Milan Dierick
// Created: 05/06/2021 3:20 AM
// Solution: QBert

#pragma once
#include "Heirloom/Events/Event.h"

struct ScoreSourceEventArgs;

class IScoreSource
{
public:
	Heirloom::Event<ScoreSourceEventArgs> ScoreSourceEvent;
};
