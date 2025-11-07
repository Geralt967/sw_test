#include "SimulationManager.hpp"
#include "IO/Units/Unit.hpp"

namespace sw::io {
	bool SimulationManager::shouldContinue(GameState& s) {
		int alive = 0;
		for (auto const &kv : s.GetUnits()) {
			auto const &uPtr = kv.second;
			if (uPtr && uPtr->isAlive()) ++alive;
		}
		if (alive <= 1) return false;

		for (auto const &kv : s.GetUnits()) {
			auto const &uPtr = kv.second;
			if (!uPtr || !uPtr->isAlive()) continue;
			if (uPtr->canAct(s)) return true;
		}

		return false;
	}

	void SimulationManager::runOneTurn(GameState& s) {
		s.IncrementTurn();
		std::unordered_map<int, Unit*> units = s.GetUnits();
		std::vector<int> ids;
		ids.reserve(units.size());
		for (auto &kv : units)
			ids.push_back(kv.first);

		for (int id : ids)
		{
			auto it = units.find(id);
			if (it == units.end()) continue;
			Unit* u = it->second;
			if (!u || !u->isAlive()) continue;

			u->executeTurn(s);
			s.RemoveDeadImmediate();
		}
	}
}