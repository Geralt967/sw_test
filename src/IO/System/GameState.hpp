#pragma once
#include "Map.hpp"
#include "Singleton.hpp"
#include <memory>
#include <unordered_map>

namespace sw::io
{
	struct Unit;

	class GameState: public Singleton<GameState>
	{
	public:
		bool AddUnit(std::unique_ptr<Unit> u);
		Unit* FindUnit(int id);
		void RemoveDeadImmediate();
		void MoveUnit(Unit& u, Pos to);
		void InitMap(int width, int height);
		Map* GetMap() { return &map; }
		std::unordered_map<int, Unit*> GetUnits() const;
		int GetTurn() const { return turn; }
		void IncrementTurn() {turn++;};

	private:
		Map map;
		std::unordered_map<int,std::unique_ptr<Unit>> units;
		int turn = 0;
	};
}