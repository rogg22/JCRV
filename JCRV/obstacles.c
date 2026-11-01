#include "cprocessing.h"
#include "obstacles.h"

//Trap
void draw_obstacle_trap(float trap_x, float trap_y, float trapWidth, float trapHeight) {
	CP_Color trapColor = CP_Color_Create(150, 110, 110, 255); //Trap color
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(trapColor);
	CP_Graphics_DrawRect(trap_x, trap_y, trapWidth, trapHeight);
}

//Printer
void draw_obstacle_printer(float printer_x, float printer_y, float printerWidth, float printerHeight) {
	CP_Color printerColor = CP_Color_Create(50, 200, 100, 255); //Trap color
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(printerColor);
	CP_Graphics_DrawRect(printer_x, printer_y, printerWidth, printerHeight);
}

//Printer
void draw_printer_ammo(float printer_x, float printer_y, float printerWidth, float printerHeight) {
	CP_Color printerColor = CP_Color_Create(50, 200, 100, 255); //Trap color
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(printerColor);
	CP_Graphics_DrawRect(printer_x + printerWidth, printer_y, printerWidth, printerHeight);
}

//Main menu buttons
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	float half_width = area_width / 2.0f;
	float half_height = area_height / 2.0f;

	float left = area_center_x - half_width;
	float right = area_center_x + half_width;
	float up = area_center_y - half_height;
	float down = area_center_y + half_height;

	if (click_x >= left && click_x <= right && click_y >= up && click_y <= down)
	{
		return 1;
	}
	return 0;
}

//Stapler trap hitbox
int AreBoxesIntersecting(float box_center_x, float box_center_y, float box_width, float box_height, float trap_center_x, float trap_center_y, float trap_width, float trap_height)
{
	float half_width = box_width / 2.0f;
	float half_height = box_height / 2.0f;

	float half_width2 = trap_width / 2.0f;
	float half_height2 = trap_height / 2.0f;

	float dx = box_center_x - trap_center_x;
	float dy = box_center_y - trap_center_y;

	if (dx < 0) {
		dx = -dx;
	}
	if (dy < 0) {
		dy = -dy;
	}

	if (dx <= half_width + half_width2 && dy <= half_height + half_height2) {
		return 1;
	}
	return 0;
}

//Printer hitbox
int PrinterIntersecting(float box_center_x, float box_center_y, float box_width, float box_height, float printer_center_x, float printer_center_y, float printer_width, float printer_height)
{
	float half_width = box_width / 2.0f;
	float half_height = box_height / 2.0f;

	float half_width2 = printer_width / 2.0f;
	float half_height2 = printer_height / 2.0f;

	float dx = box_center_x - printer_center_x;
	float dy = box_center_y - printer_center_y;

	if (dx < 0) {
		dx = -dx;
	}
	if (dy < 0) {
		dy = -dy;
	}

	if (dx <= half_width + half_width2 && dy <= half_height + half_height2) {
		return 1;
	}
	return 0;
}