#include "Unit.hpp"
#include "IO/Constants.hpp"
#include "IO/System/GameState.hpp"
#include <algorithm>
#include <cmath>
#include <optional>

namespace sw::io {

bool Unit::isAlive() const noexcept { return getStat(HP,0) > 0; }
int Unit::getStat(const std::string& name,int def) const noexcept {
    auto it = stats.find(name); return it==stats.end()?def:it->second;
}
void Unit::setStat(const std::string& name,int v){ stats[name]=v;}
void Unit::addStat(const std::string& name,int delta){ stats[name]=getStat(name,0)+delta; }

bool Unit::canAct(GameState& state) const {
	if(!isAlive()) return false;
	for(auto const& a: abilities)
		if(a->canExecute(state,*this)) return true;
	return false;
}

void Unit::executeTurn(GameState& state) {
	if (!isAlive()) return;

	std::vector<IAbility*> tmp;
	tmp.reserve(abilities.size());
	for (auto& p : abilities) {
		if (p) {
			tmp.push_back(p.get());
		}
	}

	if (tmp.empty()) return;

	std::ranges::sort(tmp, [](IAbility* a, IAbility* b) {
		if (!a) return false;
		if (!b) return true;
		return a->priority() > b->priority();
	});

	for (auto ab : tmp) {
		if (!ab) continue;
		if (ab->canExecute(state, *this)) {
			ab->execute(state, *this);
			return;
		}
	}
}

}
