#pragma once

#include "IO/Abilities/MeleeAttackAbility.hpp"
#include "IO/Abilities/MoveToAbility.hpp"
#include "IO/Abilities/RangedAttackAbility.hpp"
#include "IO/Constants.hpp"
#include "IO/Units/Unit.hpp"

#include <cstdint>
#include <iosfwd>

namespace sw::io
{
	struct SpawnHunter: public ICommand
	{
		constexpr static const char* Name = "SPAWN_HUNTER";

		SpawnHunter(int Id=0,int x=0,int y=0,int hp=0, int unitStrength=0, int range=3)
			: unitId(Id),x(x),y(y),hp(hp),strength(unitStrength),range(range){}

		void execute(GameState& s) override
		{
			auto u = std::make_unique<Unit>();
			u->id = unitId;
			u->name = "Hunter";
			u->pos = {x,y};
			u->setStat(HP, hp);
			u->setStat(Strength, strength);
			u->setStat(Agility, agility);
			u->setStat(MoveRange, 1);
			u->setStat(Range, range);

			u->abilities.push_back(std::make_unique<RangedAttackAbility>(100, range, agility));
			u->abilities.push_back(std::make_unique<MeleeAttackAbility>(50, strength));
			u->abilities.push_back(std::make_unique<MoveToAbility>(10));

			s.AddUnit(std::move(u));
		};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
			visitor.visit("hp", hp);
			visitor.visit("agility", agility);
			visitor.visit("strength", strength);
			visitor.visit("range", range);
		}

	private:
		int unitId;
		int x;
		int y;
		int hp;
		int agility;
		int strength;
		int range;
	};
}
