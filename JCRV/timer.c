#include <stdio.h>
#include "math.h"
#include "timer.h"
#include "cprocessing.h"

float totalTime;
static float tickingTime;


void timer_init(float seconds){
	totalTime = seconds;
	tickingTime = seconds;
}

void timer_reset(void) {
	tickingTime = totalTime;
}

void timer_countdown(float deltaTime) {
	tickingTime -= deltaTime;
	if (tickingTime < 0) {
		tickingTime = 0;
	}
}

void timer_print(void) {
	CP_Color timer = CP_Color_Create(0, 0, 255, 255);
	CP_Color countdown = CP_Color_Create(255, 0, 0, 255);

	CP_Settings_Fill(timer);
	if (tickingTime <= totalTime * 0.1f) {
		CP_Settings_Fill(countdown);
	}
	char buffer[16] = { 0 };
	sprintf_s(buffer, 16, "%.0f", ceilf(tickingTime));
	CP_Font_DrawText(buffer, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * .1f);
}


float remainingTime(void) {
	return ceilf(tickingTime);
}

