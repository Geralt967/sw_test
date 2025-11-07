#pragma once
#include <memory>

namespace sw::io {

struct Unit;
struct GameState;

class IAbility {
public:
	virtual ~IAbility() = default;

	virtual int priority() const = 0;
	virtual bool canExecute(GameState& state, const Unit& self) = 0;
	virtual void execute(GameState& state, Unit& self) = 0;
};

using IAbilityPtr = std::unique_ptr<IAbility>;

}
