#include "cprocessing.h"
#include "obstacles.h"
#include "Mainmenu.h"
#include "instruction.h"

CP_Font Font;

void Instruction_Init(void) {
	Font = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(Font);
}

void Instruction_Update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(150, 150, 150, 255));
	//rectangle
	CP_Settings_Fill(CP_Color_Create(255, 127, 127, 255));
	CP_Graphics_DrawRect(1200, 130, 240, 80);
	CP_Graphics_DrawRect(1200, 230, 240, 80);
	CP_Graphics_DrawRect(1200, 330, 240, 80);
	CP_Graphics_DrawRect(1200, 430, 240, 80);
	CP_Graphics_DrawRect(800, 450, 860, 800);
	CP_Graphics_DrawRect(185, 780, 190, 120);//back
	CP_Settings_Fill(CP_Color_Create(127, 255, 127, 255));
	CP_Graphics_DrawRectAdvanced(1010, 200, 330, 330, 167, 0);//illust

	//illust
	CP_Graphics_DrawRect(580, 500, 60, 60);
	CP_Graphics_DrawRect(580, 580, 60, 60);
	CP_Graphics_DrawRect(660, 580, 60, 60);
	CP_Graphics_DrawRect(500, 580, 60, 60);
	CP_Settings_Fill(CP_Color_Create(144, 238, 144, 255));
	CP_Graphics_DrawEllipse(830, 770, 100, 100);

	//text
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_TextSize(72.0f);
	CP_Font_DrawText("Back", CP_System_GetWindowWidth() / 8.5f, CP_System_GetWindowHeight() / 1.156f);
	//instructions
	CP_Settings_TextSize(45.0f);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("3. Use WASD to move!", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 1.97f);
	CP_Font_DrawText("4. Use P to pause!", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 1.59f);
	CP_Font_DrawText("Use Q to return to", CP_System_GetWindowWidth() / 1.9f, CP_System_GetWindowHeight() / 1.46f);
	CP_Font_DrawText("the main menu !", CP_System_GetWindowWidth() / 1.9f, CP_System_GetWindowHeight() / 1.35f);
	CP_Font_DrawText("1. Avoid your boss", CP_System_GetWindowWidth() / 3.7f, CP_System_GetWindowHeight() / 5.67f);
	CP_Font_DrawText("   and obstacles!", CP_System_GetWindowWidth() / 3.7f, CP_System_GetWindowHeight() / 4.30f);
	CP_Font_DrawText("2. Collect keys to", CP_System_GetWindowWidth() / 3.7f, CP_System_GetWindowHeight() / 2.8f);
	CP_Font_DrawText("leave", CP_System_GetWindowWidth() / 3.4f, CP_System_GetWindowHeight() / 2.42f);
	CP_Font_DrawText("5. Leave the office", CP_System_GetWindowWidth() / 3.7f, CP_System_GetWindowHeight() / 1.24f);
	CP_Font_DrawText("in time!", CP_System_GetWindowWidth() / 3.4f, CP_System_GetWindowHeight() / 1.17f);

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		float click_x = CP_Input_GetMouseX();
		float click_y = CP_Input_GetMouseY();
		if (IsAreaClicked(185.0f, 780.0f, 190.0f, 120.0f, click_x, click_y))
		{
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		}

	}
}
void Instruction_Exit(void) {
	CP_Font_Free(Font);
}