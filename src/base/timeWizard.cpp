#include "base/timeWizard.h"

TimeWizard::TimeWizard(){ prevTime = SDL_GetTicks(); }

void TimeWizard::getCurTime(){
		curTime = SDL_GetTicks();
		deltaTime = static_cast<double>(curTime-prevTime);
		prevTime = curTime;
}
void TimeWizard::frameCap(){
		Uint64 frameTime = SDL_GetTicks() - curTime;
		if (frameTime < TARGET_FRAME_TIME){
			double delay = TARGET_FRAME_TIME - frameTime;
			SDL_Delay(static_cast<Uint64>(delay));
		}
	}

