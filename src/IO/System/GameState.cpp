#include "GameState.hpp"
#include "EventLog.hpp"
#include "IO/Constants.hpp"
#include "IO/Events/MapCreated.hpp"
#include "IO/Events/UnitDied.hpp"
#include "IO/Events/UnitSpawned.hpp"
#include "IO/Units/Unit.hpp"

namespace sw::io
{

	bool GameState::AddUnit(std::unique_ptr<Unit> u) {
		if (!u) return false;

		if (map.width <= 0 || map.height <= 0) return false;
		if (!map.inBounds(u->pos)) return false;
		bool occupies = u->getStat(OccupiesTile, 1) != 0;


		int id = u->id;
		if (id < 0) return false;
		if (units.count(id)) return false;

		if (occupies) map.setOccupied(u->pos, true);

		EventLog& eventLog = EventLog::Get();
		eventLog.log(turn, UnitSpawned{id, u->name, u->pos.x, u->pos.y});

		units[id] = std::move(u);
		return true;
	}

	Unit* GameState::FindUnit(int id) {
		auto it = units.find(id);
		return it==units.end()? nullptr : it->second.get();
	}

	void GameState::RemoveDeadImmediate() {
		std::vector<int> dead;

		for (auto &kv : units) {
			if (!kv.second || !kv.second->isAlive()) dead.push_back(kv.first);
		}

		EventLog& eventLog = EventLog::Get();

		for (int id : dead) {
			auto it = units.find(id);
			if (it != units.end() && it->second) {
				auto& u = it->second;

				bool occupies = u->getStat(OccupiesTile, 1) != 0;
				if (occupies) map.setOccupied(u->pos, false);

				eventLog.log(turn, UnitDied{id});
				units.erase(it);
			}
		}
	}

	void GameState::MoveUnit(Unit& u, Pos to) {
		bool occupies = u.getStat(OccupiesTile,1)!=0;
		if (occupies) {
			map.setOccupied(u.pos, false);
		}
		u.pos = to;
		if (occupies) {
			map.setOccupied(to, true);
		}
	}

	void GameState::InitMap(int width, int height) {
		map = Map(width, height);
		EventLog& eventLog = EventLog::Get();
		eventLog.log(turn, MapCreated{width, height});
	}

	std::unordered_map<int, Unit*> GameState::GetUnits() const
	{
		std::unordered_map<int, Unit*> result;
		for (auto& [id, uPtr] : units)
			result[id] = uPtr.get();
		return result;
	}
}
