#include "base/obsidian.h"
#include <cmath>
float CalcDist( fvec2 a, fvec2 b) {
		return std::sqrt( std::pow((b.x - a.x),2) + std::pow((b.y - a.y),2) );
}

