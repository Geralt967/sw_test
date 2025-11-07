#include "MoveToAbility.hpp"
#include "IO/Events/UnitMoved.hpp"
#include "IO/System/EventLog.hpp"
#include "IO/System/GameState.hpp"
#include "IO/Units/Unit.hpp"
#include <array>

namespace sw::io
{
	bool MoveToAbility::canExecute(GameState& state, const Unit& currentUnit) {
		return currentUnit.isAlive();
	}

	void MoveToAbility::execute(GameState& state, Unit& currentUnit) {
		if (!currentUnit.isAlive()) return;

		Pos target;
		if (!ChooseTargetForUnit(currentUnit, state, target)) return;

		Pos step;
		if (!CalculateNextStep(currentUnit, state, target, step)) return;

		state.MoveUnit(currentUnit, step);

		EventLog& eventLog = EventLog::Get();
		eventLog.log(state.GetTurn(), UnitMoved{currentUnit.id, currentUnit.pos.x, currentUnit.pos.y});
	}

	bool MoveToAbility::ChooseTargetForUnit(const Unit& self, GameState& state, Pos& outTarget)
	{
		Unit* best = nullptr;
		int bestDist = std::numeric_limits<int>::max();

		for (auto& kv : state.GetUnits()) {
			Unit* other = kv.second;
			if (!other || !other->isAlive() || other->id == self.id) continue;

			int dx = std::abs(other->pos.x - self.pos.x);
			int dy = std::abs(other->pos.y - self.pos.y);
			int dist = std::max(dx, dy);

			if (dist < bestDist) {
				bestDist = dist;
				best = other;
			}
		}

		if (!best) return false;
		outTarget = best->pos;
		return true;
	}

	bool MoveToAbility::CalculateNextStep(const Unit& self, GameState& state, const Pos& target, Pos& outStep)
	{
		int dx = target.x - self.pos.x;
		int dy = target.y - self.pos.y;
		if (dx == 0 && dy == 0) return false;

		int stepX = (dx > 0) - (dx < 0);
		int stepY = (dy > 0) - (dy < 0);

		Pos candidates[3] = {
			{self.pos.x + stepX, self.pos.y + stepY},
			{self.pos.x + stepX, self.pos.y},
			{self.pos.x, self.pos.y + stepY}
		};

		const Map* map = state.GetMap();
		for (auto& next : candidates) {
			if (!map->inBounds(next)) continue;
			if (map->isOccupied(next)) continue;
			outStep = next;
			return true;
		}
		return false;
	}
}

