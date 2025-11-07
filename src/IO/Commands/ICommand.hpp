#pragma once
#include "IO/System/GameState.hpp"

namespace sw::io
{
	struct ICommand
	{
		virtual ~ICommand() = default;
		virtual void execute(GameState& s) = 0;
		constexpr static const char* Name  = nullptr;
	};
}


