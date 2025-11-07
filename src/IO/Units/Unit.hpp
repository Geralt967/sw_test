#pragma once
#include "../Abilities/IAbility.hpp"
#include "../Utils/Types.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace sw::io {

	struct GameState;

	struct Unit {
		int id=-1;
		std::string name;
		Pos pos{};
		std::unordered_map<std::string,int> stats;
		std::vector<std::unique_ptr<IAbility>> abilities;

		bool isAlive() const noexcept;
		int getStat(const std::string& name, int def=0) const noexcept;
		void setStat(const std::string& name, int v);
		void addStat(const std::string& name, int delta);
		bool canAct(GameState& state) const;
		void executeTurn(GameState& state);
	};
}
