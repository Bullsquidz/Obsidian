#ifndef OBSIDIAN_H
#define OBSIDIAN_H

const int ScreenWidth = 800, ScreenHeight = 600;

struct vec2{
		int x = 0;
		int y = 0;
};

struct fvec2{
		float x = 0;
float y = 0;
};

inline constexpr double OPI = 3.14159;
inline constexpr double OEPSI = 0.01;
const int cScale = 1;
inline constexpr int cSize = 12 * cScale;
inline constexpr int hCSize = cSize / 2;

float CalcDist( fvec2 a, fvec2 b);

#endif
