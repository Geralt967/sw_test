#pragma once

#include <cstdint>
#include <string>

namespace sw::io
{
	struct UnitAttacked
	{
		constexpr static const char* Name = "UNIT_ATTACKED";

		int attackerUnitId{};
		int targetUnitId{};
		int damage{};
		int targetHp{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("attackerUnitId", attackerUnitId);
			visitor.visit("targetUnitId", targetUnitId);
			visitor.visit("damage", damage);
			visitor.visit("targetHp", targetHp);
		}
	};
}
