#pragma once

float return_degree(void);
float return_radian_x(void);
float return_radian_y(void);
int ScreenCheck(float x, float y, float wallx, float wally, float buffer);
void draw_obstacle_trap(CP_Image trap, float trap_x, float trap_y);
void draw_obstacle_printer(CP_Image printer, float printer_x, float printer_y);
void draw_heal(CP_Image heal, float heal_x, float heal_y);
void draw_printer_ammo(float printerAmmo_x, float printerAmmo_y, float printerAmmoWidth, float printerAmmoHeight);
void draw_key(CP_Image key, float key_x, float key_y);
int PrinterIntersecting(float player_x, float player_y, float printer_x, float printer_y);
int AreBoxesIntersecting(float player_x, float player_y, float trap_x, float trap_y);
int HealIntersecting(float player_x, float player_y, float heal_x, float heal_y);
int KeyIntersecting(float player_x, float player_y, float key_x, float key_y);