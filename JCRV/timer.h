#pragma once

void timer_init(float seconds);
void timer_reset(void);
void timer_countdown(float deltaTime);
void timer_print(void);
float remainingTime(void);