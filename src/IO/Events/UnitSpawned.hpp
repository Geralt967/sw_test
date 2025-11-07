#pragma once

#include <string>

namespace sw::io
{
	struct UnitSpawned
	{
		constexpr static const char* Name = "UNIT_SPAWNED";

		int unitId;
		std::string unitType;
		int x;
		int y;

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("unitType", unitType);
			visitor.visit("x", x);
			visitor.visit("y", y);
		}
	};
}
