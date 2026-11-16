#include <math.h>
#include "cprocessing.h"
#include "obstacles.h"
#include "utils.h"

static float degree = 0.0f;

int ScreenCheck(float x, float y, float wallx, float wally, float buffer) {
	if (x >= wallx - buffer) {
		return 1;
	}
	else if (x <= 0 + buffer) {
		return 1;
	}
	else if (y - buffer <= wally) {
		return 1;
	}
	else if (0 + buffer >= y) {
		return 1;
	}
	else {
		return 0;
	}
}

void draw_key(CP_Image key, float key_x, float key_y) {
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Image_Draw(key, key_x, key_y, KEY_SIZE, KEY_SIZE, 255);
}

//Printer
void draw_obstacle_printer(CP_Image printer, float printer_x, float printer_y) {
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	if (degree < 0.f) {
		degree = 0.f;
	}
	if (degree >= 0.f && degree <= 360.f) {
		degree += 1.5f;
	}
	if (degree >= 360.f) {
		degree = 0.f;
	}
	CP_Image_DrawAdvanced(printer, printer_x, printer_y, PRINTER_SIZE, PRINTER_SIZE, 255, degree);
	CP_Settings_ImageMode(CP_POSITION_CORNER);
}

float return_degree(void) {
	return degree;
}

float return_radian_x(void) {
	float radian = (degree * (3.14159f / 180.f));
	return cosf(radian);
}

float return_radian_y(void) {
	//y angle
	float radian = 90 - (degree * (3.14159f / 180.f));
	return cosf(radian);
}

//Printer ammo
void draw_printer_ammo(float printerAmmo_x, float printerAmmo_y, float printerAmmoWidth, float printerAmmoHeight) {
	CP_Color printerColor = CP_Color_Create(50, 200, 100, 255); //Trap color
	CP_Settings_Fill(printerColor);
	CP_Graphics_DrawRect(printerAmmo_x, printerAmmo_y, printerAmmoWidth, printerAmmoHeight);
	CP_Settings_RectMode(CP_POSITION_CORNER);
}

//Stapler trap hitbox with player
int AreBoxesIntersecting(float player_x, float player_y, float trap_x, float trap_y)
{
	if (player_x < trap_x + 25.0f && player_x + 50.0f > trap_x && player_y < trap_y + 30.0f && player_y + 45.0f > trap_y) {
		return 1;
	}
	return 0;
}

int PrinterIntersecting(float player_x, float player_y, float printer_x, float printer_y)
{
	if (player_x < printer_x + 55.0f && player_x + PLAYER_SIZE > printer_x && player_y < printer_y + 50.0f && player_y + PLAYER_SIZE > printer_y) {
		return 1;
	}
	return 0;
}

int KeyIntersecting(float player_x, float player_y, float heal_x, float heal_y)
{
	if (player_x < heal_x + 45.0f && player_x + 45.0f > heal_x && player_y < heal_y + 50.0f && player_y + 50.0f > heal_y) {
		return 1;
	}
	return 0;
}