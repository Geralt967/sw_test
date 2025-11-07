#pragma once
#include "IAbility.hpp"

namespace sw::io
{
	class RangedAttackAbility: public IAbility
	{
	public:
		RangedAttackAbility(int priority, int range, int power)
			: Priority(priority), Range(range), Power(power) {}

		~RangedAttackAbility() override = default;

		int priority() const override { return Priority; }

		bool canExecute(GameState& state, const Unit& self) override;
		void execute(GameState& state, Unit& currentUnit) override;

	private:
		const int Priority;
		int Range;
		int Power;
	};
}


