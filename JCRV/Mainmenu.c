#include "cprocessing.h"
#include "mainmenu.h"
#include "obstacles.h"
#include "Instruction.h"
#include "difficultySelection.h"

CP_Font Font;
CP_Image BG;
CP_Image Button;

void Main_Menu_Init(void)
{
	Font = CP_Font_Load("Assets/BoldsPixels.ttf");
	BG = CP_Image_Load("Assets/BG_Title.png");
	Button = CP_Image_Load("Assets/Button.png");
	CP_Font_Set(Font);
}

void Main_Menu_Update(void)
{
	//rectangle
	float click_x = CP_Input_GetMouseX();
	float click_y = CP_Input_GetMouseY();
	float size_w = 1600.0f;
	float size_h = 900.0f;
	CP_Graphics_ClearBackground(CP_Color_Create(150, 150, 150, 255));
	CP_Image_Draw(BG, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, 1600, 900, 255);
	CP_Image_Draw(Button, 794.0f, 740.0f, size_w, size_h, 255); //bottom rect
	CP_Image_Draw(Button, 794.0f, 600.0f, size_w, size_h, 255); //middle rect 
	CP_Image_Draw(Button, 794.0f, 460.0f, size_w, size_h, 255);//top rect

	if (IsAreaClicked(800.0f, 772.0f, 360.0f, 80.0f, click_x, click_y)) {
		CP_Image_Draw(Button, 794.0f, 740.0f, 1660, 960, 255);
	}
	if (IsAreaClicked(800.0f, 632.0f, 360.0f, 80.0f, click_x, click_y))
	{
		CP_Image_Draw(Button, 794.0f, 600.0f, 1660, 960, 255);
	}
	if (IsAreaClicked(800.0f, 492.0f, 360.0f, 80.0f, click_x, click_y))
	{
		CP_Image_Draw(Button, 794.0f, 460.0f, 1660, 960, 255);
	}
	//text
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("Start", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 1.83f);
	CP_Font_DrawText("Intructions", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 1.42f);
	CP_Font_DrawText("Exit", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 1.1646f);

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		if (IsAreaClicked(800.0f, 772.0f, 360.0f, 80.0f, click_x, click_y)) {
			CP_Engine_Terminate();
		}
		
		if (IsAreaClicked(800.0f, 632.0f, 360.0f, 80.0f, click_x, click_y))
		{
			CP_Engine_SetNextGameState(Instruction_Init, Instruction_Update, Instruction_Exit);
		}

		if (IsAreaClicked(800.0f, 492.0f, 360.0f, 80.0f, click_x, click_y))
		{
			CP_Engine_SetNextGameState(Difficulty_Init, Difficulty_Update, Difficulty_Exit);
		}
	}
}

void Main_Menu_Exit(void)
{
	CP_Font_Free(Font);
	CP_Image_Free(BG);
}