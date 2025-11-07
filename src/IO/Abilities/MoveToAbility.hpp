#pragma once
#include "IAbility.hpp"
#include "IO/Utils/Types.hpp"

namespace sw::io
{
	class MoveToAbility: public IAbility
	{
	public:
		MoveToAbility(int priority)
			: Priority(priority){}
		bool canExecute(GameState& state, const Unit& currentUnit) override;
		void execute(GameState& state, Unit& currentUnit) override;
		int priority() const override { return Priority; }
		~MoveToAbility() override = default;
	private:
		const int Priority;
		bool ChooseTargetForUnit(const Unit& self, GameState& state, Pos& outTarget);
		bool CalculateNextStep(const Unit& self, GameState& state, const Pos& target, Pos& outStep);
	};
}


