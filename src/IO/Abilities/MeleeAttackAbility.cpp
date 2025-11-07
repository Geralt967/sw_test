#include "MeleeAttackAbility.hpp"
#include "IO/Constants.hpp"
#include "IO/Events/UnitAttacked.hpp"
#include "IO/System/EventLog.hpp"
#include "IO/System/GameState.hpp"
#include "IO/Units/Unit.hpp"
#include "IO/Utils/GamePlayUtils.hpp"

namespace sw::io
{
	bool MeleeAttackAbility::canExecute(GameState& state, const Unit& self)
	{
		if (!self.isAlive()) return false;
		for (auto &kv : state.GetUnits()) {
			Unit* tgt = kv.second;
			if (!tgt || !tgt->isAlive() || tgt->id==self.id) continue;
			int d = GamePlayUtils::GetDistanceToTarget(self.pos, tgt->pos);
			if (d == 1) return true;
		}
		return false;
	}

	void MeleeAttackAbility::execute(GameState& state, Unit& currentUnit) {
		Unit* bestTarget = nullptr;
		int bestDistance = std::numeric_limits<int>::max();

		for (auto &kv : state.GetUnits()) {
			Unit* tgt = kv.second;
			if (!tgt || !tgt->isAlive() || tgt->id == currentUnit.id) continue;

			int d = GamePlayUtils::GetDistanceToTarget(currentUnit.pos, tgt->pos);

			if (d == 1 && d < bestDistance) {
				bestTarget = tgt;
				bestDistance = d;
			}
		}

		if (!bestTarget) return;

		int dmg = (Power > 0 ? Power : currentUnit.getStat(Strength, 0));
		bestTarget->addStat(HP, -dmg);
		EventLog& eventLog = EventLog::Get();
		eventLog.log(state.GetTurn(), UnitAttacked{currentUnit.id, bestTarget->id, dmg, bestTarget->getStat(HP)});
		state.RemoveDeadImmediate();
	}
}


