#pragma once
#include "../Utils/Types.hpp"

#include <string>
#include <vector>

namespace sw::io
{
	class Map {
	public:
		int width=0, height=0;
		std::vector<char> occupied;

		Map() = default;
		Map(int w, int h) { create(w, h); }
		void create(int w, int h) {
			width = w;
			height = h;
			occupied.assign(w * h, 0);
		}
		bool inBounds(const Pos p) const noexcept { return p.x>=0 && p.y>=0 && p.x<width && p.y<height; }
		bool isOccupied(const Pos p) const noexcept {
			if(p.x < 0 || p.y < 0 || p.x >= width || p.y >= height || occupied.empty()) return true;
			return occupied[p.y*width + p.x] != 0;
		}
		void setOccupied(const Pos p, const bool v) {
			if(p.x < 0 || p.y < 0 || p.x >= width || p.y >= height || occupied.empty()) return;
			occupied[p.y*width + p.x] = v ? 1 : 0;
		}

	}; 
}