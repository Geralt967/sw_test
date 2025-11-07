#pragma once
#include "IO/Events/MarchEnded.hpp"
#include "IO/Events/MarchStarted.hpp"
#include "IO/System/EventLog.hpp"
#include "IO/Units/Unit.hpp"

namespace sw::io
{
	struct March: public ICommand
	{
		constexpr static const char* Name = "MARCH";

		March(int id=0,int x=0,int y=0):unitId(id),targetX(x),targetY(y){}
		void execute(GameState& s) override
		{
			if (auto* u = s.FindUnit(unitId)) {
				if (u->isAlive()) {
					Pos target{targetX, targetY};
					EventLog& eventLog = EventLog::Get();
					eventLog.log(s.GetTurn(), MarchStarted{u->id, u->pos.x, u->pos.y, target.x, target.y});
					Map* map = s.GetMap();
					if (map->inBounds(target) && !map->isOccupied(target)) {
						s.MoveUnit(*u, target);
					}
					eventLog.log(s.GetTurn(), MarchEnded{u->id, u->pos.x, u->pos.y});
				}
			}
		};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("targetX", targetX);
			visitor.visit("targetY", targetY);
		}
	private:
		int unitId;
		int targetX;
		int targetY;
	};
}
