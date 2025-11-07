#pragma once

#include <cstdint>

namespace sw::io
{
	struct MarchStarted
	{
		constexpr static const char* Name = "MARCH_STARTED";

		int unitId{};
		int x{};
		int y{};
		int targetX{};
		int targetY{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
			visitor.visit("targetX", targetX);
			visitor.visit("targetY", targetY);
		}
	};
}
