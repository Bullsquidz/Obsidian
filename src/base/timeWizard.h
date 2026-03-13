#ifndef TIMEWIARD_H
#define TIMEWIARD_H
#include <cstdint> 
#include "SDL3/SDL_timer.h"

inline double deltaTime = 0;
const int TARGET_FPS = 60;
const double TARGET_FRAME_TIME = 1.0 / TARGET_FPS;
class TimeWizard{
	public:
			uint64_t prevTime;
			uint64_t curTime;

	TimeWizard();
	
	void getCurTime();
	void frameCap();

};

#endif
