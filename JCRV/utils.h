#pragma once
#define ROWS 45
#define COLS 80
#define CELL_SIZE 20
#define PLAYER_SIZE 80
#define PLAYER_CELLS (PLAYER_SIZE / CELL_SIZE)
#define EMPTY 0
#define WALL 1
#define TRAP 2
#define KEY 3
#define PRINTER 4
#define HEAL 5
#define EXITWALL 6
#define EXIT 7

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int IsPlayerInRange(float ai_x, float ai_y, float detect_range, float player_x, float player_y);
int Player_WallCollision(float player_x, float player_y, float player_height, float player_width, float wall_one_x, float wall_one_y, float wall_height, float wall_thickness);
int AI_WallCollision(float ai_x, float ai_y, float ai_height, float ai_width, float wall_x, float wall_y, float wall_height, float wall_thickness);
int PlayerExit(float player_x, float player_y, float player_height, float player_width, float exit_x, float exit_y, float exit_height, float exit_width);
int AreCirclesIntersecting(float c1_x, float c1_y, float r1, float c2_x, float c2_y, float r2);
float collidex(float x, int direction, float rectx, float rectw, float s, float delt);
float collidey(float y, int direction, float recty, float recth, float s, float delt);

//void WallCreation(int easytwo_level[ROWS][COLS], int is_easytwokey_active, int easytwo_is_heal_active, int easytwo_key);
int Easyone_CheckWallCollision(int player_x, int player_y);
int Easytwo_CheckWallCollision(int player_x, int player_y);

int Easyone_Obstacles_Collision(int player_x, int player_y);
int Easytwo_Obstacles_Collision(int player_x, int player_y);

int Easyone_Key_Collision(int player_x, int player_y);
int Easytwo_Key_Collision(int player_x, int player_y);

int Easyone_Exit_Collision(int player_x, int player_y);
int Easytwo_Exit_Collision(int player_x, int player_y);

int Easyone_PowerUp_Collision(int player_x, int player_y);
int Easytwo_PowerUp_Collision(int player_x, int player_y);