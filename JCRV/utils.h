#pragma once
#define ROWS 45
#define COLS 80
#define CELL_SIZE 20
#define PLAYER_SIZE 60
#define GUARD_SIZE 60
#define TRAP_SIZE 40
#define KEY_SIZE 40
#define PRINTER_SIZE 60
#define HEAL_SIZE 40
#define AMMO_SIZE 20
#define PLAYER_CELLS (PLAYER_SIZE / CELL_SIZE)
#define GUARD_CELLS (GUARD_SIZE / CELL_SIZE)
#define AMMO_CELLS (AMMO_SIZE / CELL_SIZE)
#define EMPTY 0
#define WALL 1
#define TRAP 2
#define KEY_ONE 3
#define PRINTER 4
#define TILES 5
#define EXITWALL 6
#define EXIT 7
#define GUARDWALL 8
#define WATER 10
#define HEAL 11
#define GUARDWALL_TWO 12
#define GUARDWALL_THREE 13
float currenthealthamount;
int inventorycount;
int inventoryitem_one;
int inventoryitem_two;

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
float collidex(float x, int direction, float rectx, float rectw, float s, float delt);
float collidey(float y, int direction, float recty, float recth, float s, float delt);

int Easyone_CheckWallCollision(float player_x, float player_y);
int Easytwo_CheckWallCollision(int player_x, int player_y);
int Easythree_CheckWallCollision(int player_x, int player_y);

int Hardone_CheckWallCollision(int player_x, int player_y);
int Hardtwo_CheckWallCollision(int player_x, int player_y);
int Hardthree_CheckWallCollision(int player_x, int player_y);

int Easythree_CheckGuardWallCollision(int guard_x, int guard_y);
int Easythree_CheckGuardPlayerCollision(int pixelX, int pixelY, int guardX, int guardY);

int Easyone_Obstacles_Collision(float player_x, float player_y);
int Easytwo_Obstacles_Collision(int player_x, int player_y);
int Easythree_Obstacles_Collision(int player_x, int player_y);

int Hardone_Obstacles_Collision(int player_x, int player_y);
int Hardtwo_Obstacles_Collision(int player_x, int player_y);
int Hardthree_Obstacles_Collision(int player_x, int player_y);

int Easyone_Printerammo_Collision(int ammo_x, int ammo_y);
int Easytwo_Printerammo_Collision(int ammo_x, int ammo_y);
int Easythree_Printerammo_Collision(ammo_x, ammo_y);	

int Easyone_PlayerPrinter_Collision(int pixelX, int pixelY, int ammoX, int ammoY);
int Easytwo_PlayerPrinter_Collision(int pixelX, int pixelY, int ammoX, int ammoY);
int Easythree_PlayerPrinter_Collision(int pixelX, int pixelY, int ammoX, int ammoY);

int Easyone_Key_Collision(float player_x, float player_y);
int Easytwo_Key_Collision(int player_x, int player_y);
int Easythree_Key_Collision(int player_x, int player_y);

int Hardone_Key_Collision(int player_x, int player_y);
int Hardtwo_Key_Collision(int player_x, int player_y);
int Hardthree_Key_Collision(int player_x, int player_y);

int Easyone_Exit_Collision(float player_x, float player_y);
int Easytwo_Exit_Collision(int player_x, int player_y);
int Easythree_Exit_Collision(int player_x, int player_y);

int Hardone_Exit_Collision(int player_x, int player_y);
int Hardtwo_Exit_Collision(int player_x, int player_y);
int Hardthree_Exit_Collision(int player_x, int player_y);

int Easyone_PowerUp_Collision(float player_x, float player_y);
int Easytwo_PowerUp_Collision(int player_x, int player_y);
int Easythree_PowerUp_Collision(int player_x, int player_y);

int Hardone_PowerUp_Collision(int player_x, int player_y);
int Hardtwo_PowerUp_Collision(int player_x, int player_y);
int Hardthree_PowerUp_Collision(int player_x, int player_y);