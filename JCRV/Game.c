#include "math.h"
#include "timer.h"
#include "Mainmenu.h"
#include "obstacles.h"
#include "cprocessing.h"
#include "difficultySelection.h"

CP_Font font;
CP_BOOL Paused;
CP_BOOL Alive;
static CP_Vector box = { 800, 450 };
static float rectWidth; //Health bar reduction

void Game_Init_Easy(void)
{
	CP_System_SetFrameRate(60.0f);
	CP_System_SetWindowSize(1600, 900);
	if (TimerState == TRUE) {
		timer_init(30.0f);
	}

	Paused = FALSE;
	box.x = 800;
	box.y = 450;
	rectWidth = 1200.0f;
	font = CP_Font_Load("Assets/BoldPixels.ttf");
}

void Game_Init_Medium(void)
{
	CP_System_SetFrameRate(60.0f);
	CP_System_SetWindowSize(1600, 900);
	if (TimerState == TRUE) {
		timer_init(20.0f);
	}
	Paused = FALSE;

	box.x = 800;
	box.y = 450;
	rectWidth = 1200.0f;
	font = CP_Font_Load("Assets/BoldPixels.ttf");
}

void Game_Init_Hard(void)
{
	CP_System_SetFrameRate(60.0f);
	CP_System_SetWindowSize(1600, 900);
	if (TimerState == TRUE) {
		timer_init(10.0f);
	}
	Paused = FALSE;
	box.x = 800;
	box.y = 450;
	rectWidth = 1200.0f;
	font = CP_Font_Load("Assets/BoldPixels.ttf");
}

void Game_Update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(120, 120, 120, 255));
	CP_Font_Set(font);
	CP_Color text = CP_Color_Create(0, 0, 0, 255);
	CP_Color button = CP_Color_Create(255, 123, 123, 255);
	CP_Color bg_health = CP_Color_Create(200, 0, 0, 255);
	CP_Color timer = CP_Color_Create(0, 0, 255, 255);
	CP_Color countdown = CP_Color_Create(255, 0, 0, 255);
	CP_Color sliding_health = CP_Color_Create(255, 0, 0, 255);
	CP_Color boxColor = CP_Color_Create(200, 120, 120, 255); //Box color
	CP_Vector health = { 225, 150 }; //Health coordinates
	CP_Vector trap_position1 = { 475, 450 }; // Trap static coordinates
	CP_Vector printer_position1 = { 1000, 450 }; // Trap static coordinates
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_EllipseMode(CP_POSITION_CENTER);
	float speed = 250.0f;
	float healthSpeed = 250.0f;
	float boxWidth = 25.0f;
	float boxHeight = 25.0f;
	float trapWidth = 40.0f;
	float trapHeight = 40.0f;
	float printerWidth = 60.0f;
	float printerHeight = 60.0f;
	float printerAmmoWidth = 80.0f;
	float printerAmmoHeight = 80.0f;
	float maxhealthwidth = 1200.0f; //Background health bar
	float currentElapsedTime = CP_System_GetDt();

	//Key "P" condition to pause
	if (CP_Input_KeyTriggered(KEY_P) && rectWidth > 0) {
		Paused = TRUE;
	}

	//if condition to pause timer + other buttons in pause mode
	if (Paused == TRUE) {
		CP_Settings_TextSize(72.0f);
		CP_Settings_StrokeWeight(10.0f);
		CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER; CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
		CP_Settings_TextAlignment(horizontal, vertical);

		//Dimming system for pause
		CP_Settings_RectMode(CP_POSITION_CORNER);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 80));
		CP_Graphics_DrawRect(0.0f, 0.0f, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight());

		//Continue button when pause
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Settings_Fill(button);
		CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.35f, 400.0f, 130.0f);
		CP_Settings_Fill(text);
		CP_Font_DrawText("Continue", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.35f);

		//Exit button when pause
		CP_Settings_Fill(button);
		CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.35f + 200.0f, 400.0f, 130.0f);
		CP_Settings_Fill(text);
		CP_Font_DrawText("Main Menu", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.35f + 200.0f);

		CP_Settings_StrokeWeight(3.0f);

		if (CP_Input_MouseClicked()) {
			float mouseX = CP_Input_GetMouseX();
			float mouseY = CP_Input_GetMouseY();

			if (IsAreaClicked(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.35f, 400.0f, 130.0f, mouseX, mouseY)) {
				Paused = !Paused;
			}
			else if (IsAreaClicked(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.35f + 200.0f, 400.0f, 130.0f, mouseX, mouseY)) {
				CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
			}
		}
	}
	else {
		timer_countdown(currentElapsedTime);

		if ((TimerState == FALSE && rectWidth > 0) || (TimerState == TRUE && remainingTime() > 0 && rectWidth > 0)) {
			if (CP_Input_KeyDown(KEY_W)) {
				box.y -= currentElapsedTime * speed;
			}
			if (CP_Input_KeyDown(KEY_A)) {
				box.x -= currentElapsedTime * speed;
			}
			if (CP_Input_KeyDown(KEY_S)) {
				box.y += currentElapsedTime * speed;
			}
			if (CP_Input_KeyDown(KEY_D)) {
				box.x += currentElapsedTime * speed;
			}

			if (AreBoxesIntersecting(box.x, box.y, boxWidth, boxHeight, trap_position1.x, trap_position1.y, trapWidth, trapHeight) && rectWidth >= 0) {
				rectWidth -= currentElapsedTime * healthSpeed;
			}

			draw_obstacle_trap(trap_position1.x, trap_position1.y, trapWidth, trapHeight);

			CP_Settings_Fill(boxColor);
			CP_Graphics_DrawRect(box.x, box.y, boxWidth, boxHeight);

			CP_Settings_RectMode(CP_POSITION_CORNER);
			CP_Settings_Fill(bg_health);
			CP_Graphics_DrawRect(health.x, health.y, maxhealthwidth, 50.0f);
			CP_Settings_Fill(sliding_health);
			CP_Graphics_DrawRect(health.x, health.y, rectWidth, 50.0f);

			if (CP_Input_KeyTriggered(KEY_Q)) {
				CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
			}
		}
	}
	if (TimerState == TRUE) {
		timer_print();
	}

	//Death screen
	if ((TimerState == FALSE && rectWidth <= 0) || (TimerState == TRUE && (rectWidth <= 0 || remainingTime() <= 0))) {
		CP_Settings_RectMode(CP_POSITION_CORNER);
		CP_Settings_Fill(CP_Color_Create(135, 206, 250, 255));
		CP_Graphics_DrawRect(0.0f, 0.0f, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight());

		CP_Settings_StrokeWeight(10.0f);
		CP_Settings_TextSize(150.0f);
		CP_Settings_Fill(text);
		CP_Font_DrawText("Game Over", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.15f);

		CP_Settings_TextSize(72.0f);
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Settings_Fill(button);
		CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 160.0f, 400.0f, 130.0f);
		CP_Settings_Fill(text);
		CP_Font_DrawText("Try again", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 160.0f);

		//Exit button when pause
		CP_Settings_Fill(button);
		CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 320.0f, 400.0f, 130.0f);
		CP_Settings_Fill(text);
		CP_Font_DrawText("Main Menu", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 320.0f);

		CP_Settings_StrokeWeight(3.0f);

		if (CP_Input_MouseClicked()) {
			float mouseX = CP_Input_GetMouseX();
			float mouseY = CP_Input_GetMouseY();

			if (IsAreaClicked(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 160.0f, 400.0f, 130.0f, mouseX, mouseY)) {
				timer_reset();
				rectWidth = 1200.0f;
				box.x = 800;
				box.y = 450;
			}
			else if (IsAreaClicked(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 320.0f, 400.0f, 130.0f, mouseX, mouseY)) {
				CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
			}
		}
	}
}

void Game_Exit(void)
{
	CP_Font_Free(font);
}