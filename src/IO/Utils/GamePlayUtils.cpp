#include "GamePlayUtils.hpp"

namespace sw::io
{
	int GamePlayUtils::GetDistanceToTarget(const Pos& a,const Pos& b)
	{
		int dx = std::abs(a.x - b.x);
		int dy = std::abs(a.y - b.y);
		int d = std::max(dx, dy);
		return d;
	}
}

