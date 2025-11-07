#include "IO/System/SimulationManager.hpp"
#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/System/CommandParser.hpp>
#include <IO/System/EventLog.hpp>
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
	using namespace sw;

	io::GameState& state = io::GameState::Get();;
	if (argc != 2)
	{
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	std::ifstream file(argv[1]);
	if (!file)
	{
		throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
	}


	std::cout << "Commands:\n";
	io::CommandParser parser;
	parser.add<io::CreateMap>([&](auto command) { command.execute(state); })
		.add<io::SpawnSwordsman>([&](auto command) { command.execute(state); })
		.add<io::SpawnHunter>([&](auto command) { command.execute(state); })
		.add<io::March>([&](auto command) { command.execute(state); });

	parser.parse(file);

	std::cout << "\n\nEvents:\n";

	const int MAX_TURNS = 10000;
	int turns = 0;

	while (turns < MAX_TURNS && io::SimulationManager::shouldContinue(state)) {
		io::SimulationManager::runOneTurn(state);
		state.RemoveDeadImmediate();
		++turns;
	}

	std::cout << "Simulation finished after " << turns << " turns.\n";

	return 0;
}
