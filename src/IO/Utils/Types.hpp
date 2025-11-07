#pragma once
#include <cstdint>
#include <cmath>

namespace sw::io {

struct Pos {
    int x = 0;
    int y = 0;
    bool operator==(Pos const& o) const noexcept { return x==o.x && y==o.y; }
};

}
