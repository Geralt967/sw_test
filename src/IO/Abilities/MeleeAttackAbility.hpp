#pragma once
#include "IAbility.hpp"

namespace sw::io
{
	class MeleeAttackAbility: public IAbility
	{
	public:
		MeleeAttackAbility(const int priority, int power)
			: Priority(priority), Power(power){};
		int priority() const override { return Priority; }
		bool canExecute(GameState& state, const Unit& self) override;
		void execute(GameState& state, Unit& currentUnit) override;

		~MeleeAttackAbility() override = default;
	private:
		const int Priority;
		int Power;
	};
}



