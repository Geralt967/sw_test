#pragma once

#include "IO/Abilities/MeleeAttackAbility.hpp"

#include <cstdint>
#include <iosfwd>

namespace sw::io
{
	struct SpawnSwordsman: public ICommand
	{
	public:
		constexpr static const char* Name = "SPAWN_SWORDSMAN";

		SpawnSwordsman(int id = 0, int x = 0, int y = 0, int hp = 0, int strength = 0)
			:unitId(id),x(x),y(y),hp(hp),strength(strength){}
		void execute(GameState& s) override
		{
			auto u = std::make_unique<Unit>();
			u->id = unitId;
			u->name = "Swordsman";
			u->pos = {x,y};
			u->setStat(HP, hp);
			u->setStat(HP_MAX, hp);
			u->setStat(Strength, strength);
			u->setStat(MoveRange, 1);

			u->abilities.push_back(std::make_unique<MeleeAttackAbility>(100, strength));
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
			visitor.visit("strength", strength);
		}

	private:
		int unitId;
		int x;
		int y;
		int hp;
		int strength;

	};
}
