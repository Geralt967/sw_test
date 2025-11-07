#pragma once
#include "ICommand.hpp"

namespace sw::io
{
	struct CreateMap: public ICommand
	{

		constexpr static const char* Name = "CREATE_MAP";

		void execute(GameState& s) override
		{
			s.InitMap(width, height);
		};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("width", width);
			visitor.visit("height", height);
		}

	private:
		int width{};
		int height{};
	};
}
