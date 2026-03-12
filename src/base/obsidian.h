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
inline constexpr double OEPSI = 0.00001;
const int cScale = 2;
inline constexpr int cSize = 12 * cScale;
inline constexpr int hCSize = cSize / 2;






//TIMEWIZARD
inline double deltaTime = 0;
const int TARGET_FPS = 60;
const double TARGET_FRAME_TIME = 1.0 / TARGET_FPS;
class TimeWizard{
	public:
		Uint64 prevTime;
		Uint64 curTime;

	TimeWizard(){
		prevTime = SDL_GetTicks();
	}
	
	void getCurTime(){
		curTime = SDL_GetTicks();
		deltaTime = static_cast<double>(curTime-prevTime);
		prevTime = curTime;
	}

	void frameCap(){
		Uint64 frameTime = SDL_GetTicks() - curTime;
		if (frameTime < TARGET_FRAME_TIME){
			double delay = TARGET_FRAME_TIME - frameTime;
			SDL_Delay(static_cast<Uint64>(delay));
		}
	}

};
//TIMEWIZARD


#endif
