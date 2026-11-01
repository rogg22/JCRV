#include "game.h"
#include "mainmenu.h"
#include "obstacles.h"
#include "cprocessing.h"
#include "difficultySelection.h"

CP_Font Font;
CP_BOOL TimerState = FALSE;


void Difficulty_Init(void) {
	Font = CP_Font_Load("Assets/BoldsPixels.ttf");
	CP_Font_Set(Font);
	CP_Settings_TextSize(52.0f);
	CP_Settings_RectMode(CP_POSITION_CENTER);
}

void Difficulty_Update(void) {

	CP_Graphics_ClearBackground(CP_Color_Create(150, 150, 150, 255));

	CP_Settings_StrokeWeight(8.0f);
	CP_Settings_Fill(CP_Color_Create(255, 127, 127, 255));
	CP_Graphics_DrawRect(800.0f, 490.0f, 400.0f, 130.0f);//bottom

	CP_Settings_Fill(CP_Color_Create(255, 255, 220, 255));
	CP_Graphics_DrawRect(800.0f, 330.0f, 400.0f, 130.0f);//middle 

	CP_Settings_Fill(CP_Color_Create(127, 255, 127, 255));
	CP_Graphics_DrawRect(800.0f, 170.0f, 400.0f, 130.0f);//top

	CP_Graphics_DrawRect(800.0f, 650.0f, 300.0f, 110.0f);// timer select

	CP_Settings_Fill(CP_Color_Create(255, 127, 127, 255));
	CP_Graphics_DrawRect(185, 780, 190, 120);//back
	CP_Graphics_DrawRect(185, 780, 190, 120);

	CP_Settings_StrokeWeight(3.0f);

	//text
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("Back", CP_System_GetWindowWidth() / 8.5f, CP_System_GetWindowHeight() / 1.156f);
	CP_Font_DrawText("Easy", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 5.2f);
	CP_Font_DrawText("Medium", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.8f);
	CP_Font_DrawText("Hard", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 1.86f);

	float click_x = CP_Input_GetMouseX();
	float click_y = CP_Input_GetMouseY();
	//back
	if (IsAreaClicked(185.0f, 780.0f, 190.0f, 120.0f, click_x, click_y) && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
	//easy level select(EDIT HERE)
	if (IsAreaClicked(800.0f, 170.0f, 400.0f, 130.0f, click_x, click_y) && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		CP_Engine_SetNextGameState(Game_Init_Easy, Game_Update, Game_Exit);
	}
	//medium level select(EDIT HERE)
	if (IsAreaClicked(800.0f, 330.0f, 400.0f, 130.0f, click_x, click_y) && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		CP_Engine_SetNextGameState(Game_Init_Medium, Game_Update, Game_Exit);
	}
	//hard level select(EDIT HERE)
	if (IsAreaClicked(800.0f, 490.0f, 400.0f, 130.0f, click_x, click_y) && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		CP_Engine_SetNextGameState(Game_Init_Hard, Game_Update, Game_Exit);
	}

	//Timer State on off
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) && IsAreaClicked(800.0f, 650.0f, 300.0f, 110.0f, click_x, click_y)) {
		TimerState = !TimerState;
	}

	if (TimerState == FALSE) {
		CP_Font_DrawText("Timer: OFF", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 1.4f);
	}
	else {
		CP_Font_DrawText("Timer: ON", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 1.4f);
	}
}

void Difficulty_Exit(void) {
	CP_Font_Free(Font);
}