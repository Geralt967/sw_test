#pragma once
#include "GameState.hpp"

namespace sw::io
{
	struct  SimulationManager
	{
		static bool shouldContinue(GameState& s);
		static void runOneTurn(GameState& s);
	};
}

