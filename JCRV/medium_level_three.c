#include <stdio.h>
#include "cprocessing.h"
#include "game.h"
#include "mainmenu.h"
#include "utils.h"
#include "obstacles.h"
#include "timer.h"
#include "difficultySelection.h"
#include "FOV.h"

CP_Font myFont;
CP_Image playerFrontIcon;
CP_Image playerBackIcon;
CP_Image playerLeftIcon;
CP_Image playerRightIcon;

CP_Image bossFrontIcon;
CP_Image bossBackIcon;
CP_Image bossLeftIcon;
CP_Image bossRightIcon;

CP_Image heal;
CP_Image printer;
CP_Image heal_inventory;
CP_Image key_inventory;
CP_Image energybar_icon;
CP_Image Key;
CP_Image Trap;
CP_Image Water;

//change player start
float mediumthree_pixelX = 240.0f;
float mediumthree_pixelY = 220.0f;

int mediumthree_LevelVisible = 0;
int mediumthree_IconVisible = 0;

//player can move
int mediumthree_player_move = 0;
float mediumthree_playerspeed = 250.0f;

//direction
int mediumthree_direction;
int mediumthree_guarddirection;
int mediumthree_guardtwodirection;
int mediumthree_guardthreedirection;
int mediumthree_guardturn = 0;
int mediumthree_guardtwoturn = 0;
int mediumthree_guardthreeturn = 0;

float mediumthree_guardpixelX = 760;
float mediumthree_guardpixelY = 200;

float mediumthree_guardtwopixelX = 240;
float mediumthree_guardtwopixelY = 500;

float mediumthree_guard_speed = 200.0f;
int mediumthree_guardone_move = 0;
int mediumthree_guardtwo_move = 0;
int mediumthree_guardthree_move = 0;
int mediumthree_guardIconVisible = 0;

int mediumthree_key_id = 6;
int mediumthree_key = 0;

int mediumthree_alpha1 = 100;
int mediumthree_alpha2 = 100;
int mediumthree_alpha3 = 100;
int is_mediumthreekey_active = 1;
int is_mediumthreekey_active2 = 1;
int is_mediumthreekey_active3 = 1;

CP_Vector mediumthree_keyone = { 260.0f, 400.0f };
CP_Vector mediumthree_keytwo = { 920.0f, 360.0f };
CP_Vector mediumthree_keythree = { 1260.0f, 740.0f };

CP_Vector mediumthree_printer_one = { 1200.0f, 500.0f };
CP_BOOL AmmoAlive; //(Added)
float mediumthree_ammoSpawnTimer; //(Added)
static CP_Vector mediumthree_ammoPosition; //(Added)
float mediumthree_radian_x;
float mediumthree_radian_y;
float mediumthree_degree;
float mediumthree_a;
float mediumthree_b;

//energybar
float mediumthree_max_energy_width = 800.0f;
float mediumthree_min_energy_width = 0.0f;
float mediumthree_energy_amount;
float mediumthree_energybar_x = 145.0f;
float mediumthree_energybar_y = 30.0f;
float mediumthree_energybar_h = 40.0f;

//inventory
int mediumthree_selected_slot;
#define MAX_INVENTORY_SIZE 3
int mediumthree_healingfood_id = 8;
int mediumthree_speedfood_id = 5;
int mediumthree_inventoryid[MAX_INVENTORY_SIZE] = { 0 };

int mediumthree_is_heal_active = 1;

CP_BOOL Paused;

int mediumthree_level[ROWS][COLS] =
{
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,6,5,5,5,5,7,5,5,5,6,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,6,5,5,5,5,5,5,5,5,6,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,0,5,1,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,0,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,11,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,1,5,5,5,5,10,10,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,1,1,1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,0,5,5,1,5,5,5,5.5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,0,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,0,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,1,8,8,8,8,8,1,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,1,1,1,5,5,10,10,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,2,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,0,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,0,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }

};

static void MediumThree_Timer(CP_BOOL TimerState)
{
    CP_System_SetFrameRate(60.0f);
    if (TimerState == TRUE)
    {
        timer_init(30.0f);
    }
    Paused = FALSE;
}

static void Mediumthree_ResetStage()
{
    mediumthree_is_heal_active = 1;

    for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
        mediumthree_inventoryid[i] = 0;
    }

    mediumthree_pixelX = 240.0f;
    mediumthree_pixelY = 220.0f;
    mediumthree_direction = 0;

    mediumthree_key = 0;
    mediumthree_alpha1 = 100;
    mediumthree_alpha2 = 100;
    mediumthree_alpha3 = 100;
    is_mediumthreekey_active = 1;
    is_mediumthreekey_active2 = 1;
    is_mediumthreekey_active3 = 1;

    AmmoAlive = FALSE;
    mediumthree_ammoSpawnTimer = 0.0f;
    Paused = FALSE;
}

static int Mediumthree_CheckWallCollision(float player_x, float player_y)
{
    int left = (int)player_x / CELL_SIZE;
    int right = (int)(player_x + PLAYER_SIZE - 1) / CELL_SIZE;

    int top = (int)player_y / CELL_SIZE;
    int bottom = (int)(player_y + PLAYER_SIZE - 1) / CELL_SIZE;

    for (int row = top; row <= bottom; row++)
    {
        for (int col = left; col <= right; col++)
        {
            if (col < 0 || col >= COLS || row < 0 || row >= ROWS)
            {
                return 1;
            }

            if (mediumthree_level[row][col] == WALL)
            {
                return 1;
            }

            if (mediumthree_level[row][col] == GUARDWALL)
            {
                if (mediumthree_key < 2)
                {
                    return 1;
                }
            }

            if (mediumthree_level[row][col] == EXITWALL)
            {
                if (mediumthree_key != 3)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

static int Mediumthree_Obstacles_Collision(float player_x, float player_y)
{
    int left = (int)player_x / CELL_SIZE;
    int right = (int)(player_x + PLAYER_SIZE - 1) / CELL_SIZE;

    int top = (int)player_y / CELL_SIZE;
    int bottom = (int)(player_y + PLAYER_SIZE - 1) / CELL_SIZE;

    for (int row = top; row <= bottom; row++)
    {
        for (int col = left; col <= right; col++)
        {

            if (col < 0 || col >= COLS || row < 0 || row >= ROWS)
            {
                return 1;
            }
            if (mediumthree_level[row][col] == TRAP)
            {
                return 1;
            }
        }
    }
    return 0;
}

static int Mediumthree_CheckGuardPlayerCollision(float pixelX, float pixelY, float guardX, float guardY, float guardtwoX, float guardtwoY)
{
    if (pixelX < guardX + GUARD_SIZE && pixelX + PLAYER_SIZE > guardX && pixelY < guardY + GUARD_SIZE && pixelY + PLAYER_SIZE > guardY)
    {
        return 1;
    }
    else if (pixelX < guardtwoX + GUARD_SIZE && pixelX + PLAYER_SIZE > guardtwoX && pixelY < guardtwoY + GUARD_SIZE && pixelY + PLAYER_SIZE > guardtwoY)
    {
        return 1;
    }
    return 0;
}

static int Mediumthree_PlayerPrinter_Collision(float playerX, float playerY, float printerX, float printerY)
{
    float printer_left = printerX - (PRINTER_SIZE / 2.0f);
    float printer_top = printerY - (PRINTER_SIZE / 2.0f);
    if (PrinterIntersecting(playerX, playerY, printer_left, printer_top)) {
        return 1;
    }
    return 0;
}

static int Mediumthree_AmmoWall_Collision(float ammo_x, float ammo_y)
{
    int left = (int)ammo_x / CELL_SIZE;
    int right = (int)(ammo_x + AMMO_SIZE - 1) / CELL_SIZE;

    int top = (int)ammo_y / CELL_SIZE;
    int bottom = (int)(ammo_y + AMMO_SIZE - 1) / CELL_SIZE;

    for (int row = top; row <= bottom; row++)
    {
        for (int col = left; col <= right; col++)
        {
            if (col < 0 || col >= COLS || row < 0 || row >= ROWS)
            {
                return 1;
            }
            if (mediumthree_level[row][col] == WALL)
            {
                return 1;
            }
        }
    }
    return 0;
}

static int Mediumthree_Key_Collision(float player_x, float player_y, float keyX, float keyY)
{
    if (KeyIntersecting(player_x, player_y, keyX, keyY)) {
        return 1;
    }
    return 0;
}

static int Mediumthree_PowerUp_Collision(float player_x, float player_y)
{
    int left = (int)player_x / CELL_SIZE;
    int right = (int)(player_x + PLAYER_SIZE - 1) / CELL_SIZE;

    int top = (int)player_y / CELL_SIZE;
    int bottom = (int)(player_y + PLAYER_SIZE - 1) / CELL_SIZE;

    for (int row = top; row <= bottom; row++)
    {
        for (int col = left; col <= right; col++)
        {
            if (col < 0 || col >= COLS || row < 0 || row >= ROWS)
            {
                return 1;
            }
            if (mediumthree_level[row][col] == HEAL)
            {
                return 1;
            }
        }
    }
    return 0;
}

static int Mediumthree_Water_Collision(float player_x, float player_y)
{
    int left = (int)player_x / CELL_SIZE;
    int right = (int)(player_x + PLAYER_SIZE - 1) / CELL_SIZE;

    int top = (int)player_y / CELL_SIZE;
    int bottom = (int)(player_y + PLAYER_SIZE - 1) / CELL_SIZE;

    for (int row = top; row <= bottom; row++)
    {
        for (int col = left; col <= right; col++)
        {

            if (col < 0 || col >= COLS || row < 0 || row >= ROWS)
            {
                return 1;
            }
            if (mediumthree_level[row][col] == WATER)
            {
                return 1;
            }
        }
    }
    return 0;
}
static int Mediumthree_Exit_Collision(float player_x, float player_y)
{
    int left = (int)player_x / CELL_SIZE;
    int right = (int)(player_x + PLAYER_SIZE - 1) / CELL_SIZE;

    int top = (int)player_y / CELL_SIZE;
    int bottom = (int)(player_y + PLAYER_SIZE - 1) / CELL_SIZE;

    for (int row = top; row <= bottom; row++)
    {
        for (int col = left; col <= right; col++)
        {
            if (col < 0 || col >= COLS || row < 0 || row >= ROWS)
            {
                return 1;
            }
            if (mediumthree_level[row][col] == EXIT)
            {
                return 1;
            }
        }
    }
    return 0;
}
static void MediumThree_EnergyBar(void)
{
    if (mediumthree_energy_amount < mediumthree_min_energy_width) mediumthree_energy_amount = mediumthree_min_energy_width;
    if (mediumthree_energy_amount > mediumthree_max_energy_width) mediumthree_energy_amount = mediumthree_max_energy_width;

    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_StrokeWeight(2.0f);

    CP_Settings_Fill(CP_Color_Create(80, 80, 80, 255));
    CP_Graphics_DrawRect(mediumthree_energybar_x, mediumthree_energybar_y, mediumthree_max_energy_width, mediumthree_energybar_h);

    if (mediumthree_energy_amount < 600.0f && mediumthree_energy_amount > 200.0f) {
        CP_Settings_Fill(CP_Color_Create(255, 165, 0, 255));
        CP_Graphics_DrawRect(mediumthree_energybar_x, mediumthree_energybar_y, mediumthree_energy_amount, mediumthree_energybar_h);
    }
    else if (mediumthree_energy_amount < 200.0f) {
        CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
        CP_Graphics_DrawRect(mediumthree_energybar_x, mediumthree_energybar_y, mediumthree_energy_amount, mediumthree_energybar_h);
    }
    else {
        CP_Settings_Fill(CP_Color_Create(50, 200, 50, 255));
        CP_Graphics_DrawRect(mediumthree_energybar_x, mediumthree_energybar_y, mediumthree_energy_amount, mediumthree_energybar_h);
    }
}

static void MediumThree_Inventory(void)
{
    if (CP_Input_KeyTriggered(KEY_1)) {
        mediumthree_selected_slot = 0;
    }
    if (CP_Input_KeyTriggered(KEY_2)) {
        mediumthree_selected_slot = 1;
    }
    if (CP_Input_KeyTriggered(KEY_3)) {
        mediumthree_selected_slot = 2;
    }

    if ((mediumthree_is_heal_active == 1) && Mediumthree_PowerUp_Collision(mediumthree_pixelX, mediumthree_pixelY)) {
        int item_placed = 0;
        //remove item after item gets picked up
        for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
            if (mediumthree_inventoryid[i] == mediumthree_healingfood_id) {

                mediumthree_is_heal_active = 0;
                item_placed = 1;
                break;
            }
        }
        //check for empty slot in inventory. if found, put item in empty slot
        if (!item_placed) {
            for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
                if (mediumthree_inventoryid[i] == 0) {
                    mediumthree_inventoryid[i] = mediumthree_healingfood_id;

                    mediumthree_is_heal_active = 0;
                    break;
                }
            }
        }
    }

    CP_Settings_RectMode(CP_POSITION_CENTER);
    CP_Settings_StrokeWeight(2.0f);

    //draw inventory
    for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
        float slot_x = 170.0f + (i * 50.0f);
        float slot_y = 110.0f;

        //highlight if selected
        if (i == mediumthree_selected_slot) {
            CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
        }
        else {
            CP_Settings_Fill(CP_Color_Create(200, 200, 200, 255));
        }
        CP_Graphics_DrawRect(slot_x, slot_y, 50.0f, 45.0f);
    }

    //draw items inside inventory slots
    for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
        float slot_x = 170.0f + (i * 50.0f);
        float slot_y = 110.0f;

        if (mediumthree_inventoryid[i] == mediumthree_healingfood_id) {
            CP_Settings_ImageMode(CP_POSITION_CENTER);
            CP_Image_Draw(heal_inventory, slot_x, slot_y, 200.0f, 200.0f, 255);
            CP_Settings_ImageMode(CP_POSITION_CORNER);
        }
    }
    if (CP_Input_KeyTriggered(KEY_R)) {

        if (mediumthree_inventoryid[mediumthree_selected_slot] == mediumthree_healingfood_id) {
            mediumthree_energy_amount += 100.0f;
            if (mediumthree_energy_amount > mediumthree_max_energy_width)
            {
                mediumthree_energy_amount = mediumthree_max_energy_width;
            }
            mediumthree_inventoryid[mediumthree_selected_slot] = 0;
        }
        //else if (inventoryid[selected_slot] == speedfood_id) {
        //    player_velocity += 20.0f;
        //    inventoryid[selected_slot] = 0;
        //}

    }
}

static void NextStageHard(void)
{
    CP_Color text = CP_Color_Create(0, 0, 0, 255);
    CP_Color button = CP_Color_Create(255, 123, 123, 255);
    CP_Graphics_ClearBackground(CP_Color_Create(115, 147, 179, 255));
    CP_Settings_TextSize(72.0f);
    CP_Settings_StrokeWeight(10.0f);
    CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER; CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
    CP_Settings_TextAlignment(horizontal, vertical);

    //Dimming system for pause
    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 80));
    CP_Graphics_DrawRect(0.0f, 0.0f, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight());

    CP_Settings_StrokeWeight(10.0f);
    CP_Settings_TextSize(150.0f);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("You Have Won", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.15f);

    CP_Settings_TextSize(72.0f);
    CP_Settings_RectMode(CP_POSITION_CENTER);
    CP_Settings_Fill(CP_Color_Create(255, 123, 123, 255));
    CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 160.0f, 400.0f, 130.0f);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Next Level", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 160.0f);

    //Exit button when pause
    CP_Settings_Fill(CP_Color_Create(255, 123, 123, 255));
    CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 320.0f, 400.0f, 130.0f);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Main Menu", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 320.0f);

    CP_Settings_StrokeWeight(3.0f);

    if (CP_Input_MouseClicked()) {
        float mouseX = CP_Input_GetMouseX();
        float mouseY = CP_Input_GetMouseY();

        if (IsAreaClicked(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 160.0f, 400.0f, 130.0f, mouseX, mouseY))
        {
            CP_Engine_SetNextGameState(Hard_Level_One_Init, Hard_Level_One_Update, Hard_Level_One_Exit);
        }
        else if (IsAreaClicked(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 320.0f, 400.0f, 130.0f, mouseX, mouseY)) {
            CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
        }
    }
}

static void MediumThree_PauseScreen(void)
{
    CP_Color text = CP_Color_Create(0, 0, 0, 255);
    CP_Color button = CP_Color_Create(255, 123, 123, 255);
    if (Paused == TRUE) {
        CP_Graphics_ClearBackground(CP_Color_Create(115, 147, 179, 255));
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
                Paused = !Paused;
                CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
            }
        }
    }
}

static void MediumThree_DeathScreen(void)
{
    CP_Graphics_ClearBackground(CP_Color_Create(115, 147, 179, 255));
    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_Fill(CP_Color_Create(135, 206, 250, 255));
    CP_Graphics_DrawRect(0.0f, 0.0f, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight());

    CP_Settings_StrokeWeight(10.0f);
    CP_Settings_TextSize(150.0f);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Game Over", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.15f);

    CP_Settings_TextSize(72.0f);
    CP_Settings_RectMode(CP_POSITION_CENTER);
    CP_Settings_Fill(CP_Color_Create(255, 123, 123, 255));
    CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 160.0f, 400.0f, 130.0f);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Try again", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 160.0f);

    //Exit button when pause
    CP_Settings_Fill(CP_Color_Create(255, 123, 123, 255));
    CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 320.0f, 400.0f, 130.0f);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Main Menu", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 320.0f);

    CP_Settings_StrokeWeight(3.0f);

    if (CP_Input_MouseClicked()) {
        float mouseX = CP_Input_GetMouseX();
        float mouseY = CP_Input_GetMouseY();

        if (IsAreaClicked(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 160.0f, 400.0f, 130.0f, mouseX, mouseY)) {
            timer_reset();
            mediumthree_energy_amount = mediumthree_max_energy_width;
            for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
                mediumthree_inventoryid[i] = 0;
            }
            Mediumthree_ResetStage();
        }
        else if (IsAreaClicked(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 320.0f, 400.0f, 130.0f, mouseX, mouseY)) {
            CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
        }
    }
}

void Medium_Level_Three_Init(void)
{
    myFont = CP_Font_Load("Assets/BoldsPixels.ttf");
    CP_Font_Set(myFont);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_TextSize(40.0f);
    playerFrontIcon = CP_Image_Load("Assets/playerFrontIcon.PNG");
    playerBackIcon = CP_Image_Load("Assets/playerBackIcon.PNG");
    playerLeftIcon = CP_Image_Load("Assets/playerLeftIcon.PNG");
    playerRightIcon = CP_Image_Load("Assets/playerRightIcon.PNG");

    bossFrontIcon = CP_Image_Load("Assets/Boss_Front.PNG");
    bossBackIcon = CP_Image_Load("Assets/Boss_Back.PNG");
    bossLeftIcon = CP_Image_Load("Assets/Boss_Left.PNG");
    bossRightIcon = CP_Image_Load("Assets/Boss_Right.PNG");

    Key = CP_Image_Load("Assets/key.PNG");
    Trap = CP_Image_Load("Assets/trap.PNG");
    Water = CP_Image_Load("Assets/water.png");
    printer = CP_Image_Load("Assets/Printer.PNG");
    heal = CP_Image_Load("Assets/Heal.PNG");
    energybar_icon = CP_Image_Load("Assets/Energybar_icon.PNG");
    heal_inventory = CP_Image_Load("Assets/Heal_inventory_icon.PNG");
    key_inventory = CP_Image_Load("Assets/key_inventory_icon.PNG");

    mediumthree_energy_amount = currenthealthamount;

    startFOV();
    MediumThree_Timer(TimerState);
    Mediumthree_ResetStage();
}

void Medium_Level_Three_Update(void)
{
    CP_Graphics_ClearBackground(CP_Color_Create(115, 147, 179, 255));

    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_ImageMode(CP_POSITION_CORNER);

    float deltaTime = CP_System_GetDt();

    mediumthree_player_move = 1;
    mediumthree_guardone_move = 1;
    mediumthree_guardtwo_move = 1;
    mediumthree_guardthree_move = 1;
    mediumthree_guardIconVisible = 1;
    mediumthree_IconVisible = 1;
    mediumthree_LevelVisible = 1;

    if (mediumthree_LevelVisible == 1)
    {
        CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
        CP_Color floor_color = CP_Color_Create(115, 147, 179, 255);
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (mediumthree_level[row][col] == WALL)
                {
                    CP_Color wall_color = CP_Color_Create(173, 216, 230, 255);
                    CP_Settings_Fill(wall_color);
                    CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE);
                }
                else if (mediumthree_level[row][col] == TILES)
                {
                    CP_Settings_Fill(floor_color);
                    CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE);
                }
                else if (mediumthree_level[row][col] == TRAP)
                {
                    CP_Settings_Fill(floor_color);
                    CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)TRAP_SIZE, (float)TRAP_SIZE);
                    CP_Image_Draw(Trap, (float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)TRAP_SIZE, (float)TRAP_SIZE, 255);
                }
                else if (mediumthree_level[row][col] == HEAL) {
                    if (mediumthree_is_heal_active) {
                        CP_Settings_Fill(floor_color);
                        CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)HEAL_SIZE, (float)HEAL_SIZE);
                        CP_Image_Draw(heal, (float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)HEAL_SIZE, (float)HEAL_SIZE, 255);
                    }
                    else
                    {
                        CP_Settings_Fill(floor_color);
                        CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)HEAL_SIZE, (float)HEAL_SIZE);
                    }
                }
                else if (mediumthree_level[row][col] == EXITWALL)
                {
                    if (mediumthree_key == 3)
                    {
                        CP_Color exit_green = CP_Color_Create(0, 255, 0, 255);
                        CP_Settings_Fill(exit_green);
                        CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE);
                    }
                    else {
                        CP_Color exit_red = CP_Color_Create(255, 0, 0, 255);
                        CP_Settings_Fill(exit_red);
                        CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE);
                    }
                }
                else if (mediumthree_level[row][col] == GUARDWALL)
                {
                    CP_Color remove = CP_Color_Create(255, 0, 0, 255);
                    CP_Settings_Fill(remove);
                    if (mediumthree_key < 2)
                    {
                        CP_Graphics_DrawRect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                    }
                    else
                    {
                        CP_Settings_Fill(floor_color);
                        CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE);
                    }
                }
                else if (mediumthree_level[row][col] == WATER)
                {
                    CP_Settings_Fill(floor_color);
                    CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE);
                    CP_Image_Draw(Water, (float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE, 255);
                }
            }
        }
    }

    if (Mediumthree_Key_Collision(mediumthree_pixelX, mediumthree_pixelY, mediumthree_keyone.x, mediumthree_keyone.y) && (is_mediumthreekey_active == 1)) {
        is_mediumthreekey_active = 0;
        if (mediumthree_key == 0) {
            mediumthree_alpha1 = 255;
        }
        if (mediumthree_key == 1) {
            mediumthree_alpha2 = 255;
        }
        if (mediumthree_key == 2) {
            mediumthree_alpha3 = 255;
        }
        mediumthree_key++;
    }

    if (Mediumthree_Key_Collision(mediumthree_pixelX, mediumthree_pixelY, mediumthree_keytwo.x, mediumthree_keytwo.y) && (is_mediumthreekey_active2 == 1)) {
        is_mediumthreekey_active2 = 0;
        if (mediumthree_key == 0) {
            mediumthree_alpha1 = 255;
        }
        if (mediumthree_key == 1) {
            mediumthree_alpha2 = 255;
        }
        if (mediumthree_key == 2) {
            mediumthree_alpha3 = 255;
        }
        mediumthree_key++;
    }
    if (Mediumthree_Key_Collision(mediumthree_pixelX, mediumthree_pixelY, mediumthree_keythree.x, mediumthree_keythree.y) && (is_mediumthreekey_active3 == 1)) {
        is_mediumthreekey_active3 = 0;
        if (mediumthree_key == 0) {
            mediumthree_alpha1 = 255;
        }
        if (mediumthree_key == 1) {
            mediumthree_alpha2 = 255;
        }
        if (mediumthree_key == 2) {
            mediumthree_alpha3 = 255;
        }
        mediumthree_key++;
    }

    if (is_mediumthreekey_active == 1) {
        draw_key(Key, mediumthree_keyone.x, mediumthree_keyone.y);
    }
    if (is_mediumthreekey_active2 == 1) {
        draw_key(Key, mediumthree_keytwo.x, mediumthree_keytwo.y);
    }
    if (is_mediumthreekey_active3 == 1) {
        draw_key(Key, mediumthree_keythree.x, mediumthree_keythree.y);
    }

    CP_Image_Draw(key_inventory, 250.0f, 15.0f, 200.0f, 200.0f, mediumthree_alpha1);
    CP_Image_Draw(key_inventory, 300.0f, 15.0f, 200.0f, 200.0f, mediumthree_alpha2);
    CP_Image_Draw(key_inventory, 350.0f, 15.0f, 200.0f, 200.0f, mediumthree_alpha3);

    draw_obstacle_printer(printer, mediumthree_printer_one.x, mediumthree_printer_one.y);

    if (AmmoAlive == FALSE) {
        mediumthree_ammoSpawnTimer += deltaTime;
    }
    if (!AmmoAlive && mediumthree_ammoSpawnTimer >= 1.0f) {   // fires every 3 seconds
        AmmoAlive = TRUE;
        mediumthree_ammoSpawnTimer = 0.0f;
        mediumthree_degree = return_degree();

        //direction cosines(90 half 180)
        mediumthree_radian_x = return_radian_x();
        mediumthree_radian_y = return_radian_y();

        //magnitudes

        mediumthree_a = PRINTER_SIZE / 2.0f;
        mediumthree_b = PRINTER_SIZE / 2.0f;
        //vectors(added printer position so it spawns from there
        mediumthree_ammoPosition.x = mediumthree_printer_one.x + (mediumthree_radian_x * mediumthree_a);
        mediumthree_ammoPosition.y = mediumthree_printer_one.y + (mediumthree_radian_y * mediumthree_b);

    }
    if (AmmoAlive == TRUE) {
        float ammoSpeed = 200.0f;

        mediumthree_ammoPosition.x += (deltaTime * ammoSpeed) * mediumthree_radian_x;
        mediumthree_ammoPosition.y += (deltaTime * ammoSpeed) * mediumthree_radian_y;

        if (AreBoxesIntersecting(mediumthree_pixelX, mediumthree_pixelY, mediumthree_ammoPosition.x, mediumthree_ammoPosition.y))
        {
            mediumthree_energy_amount -= 100.0f;
            if (mediumthree_energy_amount < mediumthree_min_energy_width) {
                mediumthree_energy_amount = 0.0f;
            }
            draw_printer_ammo(mediumthree_ammoPosition.x, mediumthree_ammoPosition.y, AMMO_SIZE, AMMO_SIZE);
            AmmoAlive = FALSE;
        }
        //else if (mediumthree_ammoPosition.x > (float)CP_System_GetWindowWidth() || mediumthree_ammoPosition.x < 0.0f || mediumthree_ammoPosition.y >(float)CP_System_GetWindowHeight() || mediumthree_ammoPosition.y < 0.0f) {
        //    AmmoAlive = FALSE;
        //}
        else if (Mediumthree_AmmoWall_Collision(mediumthree_ammoPosition.x, mediumthree_ammoPosition.y)) {
            AmmoAlive = FALSE;
        }
        else {
            draw_printer_ammo(mediumthree_ammoPosition.x, mediumthree_ammoPosition.y, AMMO_SIZE, AMMO_SIZE);
        }
    }

    if (mediumthree_IconVisible == 1)
    {
        if (mediumthree_direction == 0)
        {
            CP_Image_Draw(playerRightIcon, mediumthree_pixelX, mediumthree_pixelY, (float)PLAYER_SIZE, (float)PLAYER_SIZE, 255);
        }
        else if (mediumthree_direction == 180)
        {
            CP_Image_Draw(playerLeftIcon, mediumthree_pixelX, mediumthree_pixelY, (float)PLAYER_SIZE, (float)PLAYER_SIZE, 255);
        }
        else if (mediumthree_direction == 90)
        {
            CP_Image_Draw(playerFrontIcon, mediumthree_pixelX, mediumthree_pixelY, (float)PLAYER_SIZE, (float)PLAYER_SIZE, 255);
        }
        else if (mediumthree_direction == 270)
        {
            CP_Image_Draw(playerBackIcon, mediumthree_pixelX, mediumthree_pixelY, (float)PLAYER_SIZE, (float)PLAYER_SIZE, 255);
        }
    }

    if (mediumthree_guardIconVisible == 1)
    {
        if (mediumthree_guarddirection == 90)
        {
            CP_Image_Draw(bossFrontIcon, mediumthree_guardpixelX, mediumthree_guardpixelY, GUARD_SIZE, GUARD_SIZE, 255);
        }
        else if (mediumthree_guarddirection == 270)
        {
            CP_Image_Draw(bossRightIcon, mediumthree_guardpixelX, mediumthree_guardpixelY, GUARD_SIZE, GUARD_SIZE, 255);
        }
        if (mediumthree_guardtwodirection == 0)
        {
            CP_Image_Draw(bossRightIcon, mediumthree_guardtwopixelX, mediumthree_guardtwopixelY, GUARD_SIZE, GUARD_SIZE, 255);
        }
        else if (mediumthree_guardtwodirection == 180)
        {
            CP_Image_Draw(bossLeftIcon, mediumthree_guardtwopixelX, mediumthree_guardtwopixelY, GUARD_SIZE, GUARD_SIZE, 255);
        }
    }

    CP_Settings_ImageMode(CP_POSITION_CENTER);

    if (Mediumthree_Obstacles_Collision(mediumthree_pixelX, mediumthree_pixelY))
    {
        if (mediumthree_energy_amount > mediumthree_min_energy_width)
        {
            mediumthree_energy_amount -= 20.0f * deltaTime;
        }
    }

    //FOV(pixelX, pixelY);

    if (TimerState == TRUE)
    {
        timer_print();
    }

    //energybar
    MediumThree_EnergyBar();
    MediumThree_Inventory();

    if (Mediumthree_Exit_Collision(mediumthree_pixelX, mediumthree_pixelY) && mediumthree_key == 3)
    {
        NextStageHard();
    }

    //level wall creation
    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_StrokeWeight(0.1f);

    //Key "P" condition to pause
    if (CP_Input_KeyTriggered(KEY_P) && mediumthree_energy_amount > mediumthree_min_energy_width)
    {
        Paused = TRUE;
    }

    if (Paused)
    {
        MediumThree_PauseScreen();
        mediumthree_player_move = 0;
        mediumthree_guardone_move = 0;
        mediumthree_guardtwo_move = 0;
        mediumthree_guardthree_move = 0;
        mediumthree_guardIconVisible = 0;
        mediumthree_IconVisible = 0;
        mediumthree_LevelVisible = 0;

    }
    else
    {
        timer_countdown(deltaTime);
        CP_Settings_TextSize(40.0f);
    }

    if ((TimerState == FALSE && mediumthree_energy_amount <= mediumthree_min_energy_width) || (TimerState == TRUE && (mediumthree_energy_amount <= mediumthree_min_energy_width || remainingTime() <= 0)))
    {
        MediumThree_DeathScreen();
        mediumthree_player_move = 0;
        mediumthree_guardone_move = 0;
        mediumthree_guardtwo_move = 0;
        mediumthree_guardthree_move = 0;
        mediumthree_guardIconVisible = 0;
        mediumthree_IconVisible = 0;
        mediumthree_LevelVisible = 0;
    }

    float move_amount = mediumthree_playerspeed * deltaTime;
    float speed_scale = 1.0f;
    if (mediumthree_player_move == 1)
    {
        if (Mediumthree_Water_Collision(mediumthree_pixelX, mediumthree_pixelY)) {
            speed_scale = 0.4f;
        }

        if (CP_Input_KeyDown(KEY_W))
        {
            mediumthree_direction = 270;
            if (!Mediumthree_CheckWallCollision(mediumthree_pixelX, mediumthree_pixelY - move_amount) &&
                !Mediumthree_PlayerPrinter_Collision(mediumthree_pixelX, mediumthree_pixelY - move_amount, mediumthree_printer_one.x, mediumthree_printer_one.y))
            {
                mediumthree_pixelY -= move_amount * speed_scale;
            }
        }
        else if (CP_Input_KeyDown(KEY_S))
        {
            mediumthree_direction = 90;
            if (!Mediumthree_CheckWallCollision(mediumthree_pixelX, mediumthree_pixelY + move_amount) &&
                !Mediumthree_PlayerPrinter_Collision(mediumthree_pixelX, mediumthree_pixelY + move_amount, mediumthree_printer_one.x, mediumthree_printer_one.y))
            {
                mediumthree_pixelY += move_amount * speed_scale;
            }
        }
        else if (CP_Input_KeyDown(KEY_A))
        {
            mediumthree_direction = 180;
            if (!Mediumthree_CheckWallCollision(mediumthree_pixelX - move_amount, mediumthree_pixelY) &&
                !Mediumthree_PlayerPrinter_Collision(mediumthree_pixelX - move_amount, mediumthree_pixelY, mediumthree_printer_one.x, mediumthree_printer_one.y))
            {
                mediumthree_pixelX -= move_amount * speed_scale;
            }
        }
        else if (CP_Input_KeyDown(KEY_D))
        {
            mediumthree_direction = 0;
            if (!Mediumthree_CheckWallCollision(mediumthree_pixelX + move_amount, mediumthree_pixelY) &&
                !Mediumthree_PlayerPrinter_Collision(mediumthree_pixelX + move_amount, mediumthree_pixelY, mediumthree_printer_one.x, mediumthree_printer_one.y))
            {
                mediumthree_pixelX += move_amount * speed_scale;
            }
        }
    }

    float guardmove_amount = mediumthree_guard_speed * deltaTime;
    if (mediumthree_guardone_move == 1)
    {
        if (mediumthree_guardpixelY + GUARD_SIZE >= 500)
        {
            mediumthree_guarddirection = 270;
            mediumthree_guardturn = 1;
        }
        else if (mediumthree_guardpixelY <= 200)
        {
            mediumthree_guarddirection = 90;
            mediumthree_guardturn = 0;
        }
        if (mediumthree_guardturn == 0 && !Mediumthree_CheckGuardPlayerCollision(mediumthree_pixelX, mediumthree_pixelY, mediumthree_guardpixelX, mediumthree_guardpixelY,
            mediumthree_guardtwopixelX, mediumthree_guardtwopixelY))
        {
            mediumthree_guardpixelY += guardmove_amount;
        }

        if (mediumthree_guardturn == 1 && !Mediumthree_CheckGuardPlayerCollision(mediumthree_pixelX, mediumthree_pixelY, mediumthree_guardpixelX, mediumthree_guardpixelY,
            mediumthree_guardtwopixelX, mediumthree_guardtwopixelY))
        {
            mediumthree_guardpixelY -= guardmove_amount;
        }
    }

    if (mediumthree_guardtwo_move == 1)
    {
        if (mediumthree_guardtwopixelX + GUARD_SIZE >= 900)
        {
            mediumthree_guardtwodirection = 180;
            mediumthree_guardtwoturn = 1;
        }
        else if (mediumthree_guardtwopixelX <= 240)
        {
            mediumthree_guardtwodirection = 0;
            mediumthree_guardtwoturn = 0;
        }
        if (mediumthree_guardtwoturn == 0)
        {
            mediumthree_guardtwopixelX += guardmove_amount;
        }

        if (mediumthree_guardtwoturn == 1)
        {
            mediumthree_guardtwopixelX -= guardmove_amount;
        }
    }

    if (Mediumthree_CheckGuardPlayerCollision(mediumthree_pixelX + 20, mediumthree_pixelY - 20, mediumthree_guardpixelX,
        mediumthree_guardpixelY, mediumthree_guardtwopixelX, mediumthree_guardtwopixelY))
    {
        if (mediumthree_energy_amount > mediumthree_min_energy_width)
        {
            mediumthree_energy_amount -= 100.0f * deltaTime;
        }
    }
    if (Mediumthree_CheckGuardPlayerCollision(mediumthree_pixelX, mediumthree_pixelY, mediumthree_guardpixelX + 20,
        mediumthree_guardpixelY - 20, mediumthree_guardtwopixelX, mediumthree_guardtwopixelY))
    {
        if (mediumthree_energy_amount > mediumthree_min_energy_width)
        {
            mediumthree_energy_amount -= 100.0f * deltaTime;
        }
    }

    if (Mediumthree_CheckGuardPlayerCollision(mediumthree_pixelX, mediumthree_pixelY, mediumthree_guardpixelX,
        mediumthree_guardpixelY, mediumthree_guardtwopixelX + 20, mediumthree_guardtwopixelY - 20))
    {
        if (mediumthree_energy_amount > mediumthree_min_energy_width)
        {
            mediumthree_energy_amount -= 100.0f * deltaTime;
        }
    }

    if (CP_Input_KeyReleased(KEY_Q))
    {
        CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
    }
}


void Medium_Level_Three_Exit(void)
{
    CP_Font_Free(myFont);
    CP_Image_Free(playerFrontIcon);
    CP_Image_Free(playerBackIcon);
    CP_Image_Free(playerLeftIcon);
    CP_Image_Free(playerRightIcon);

    CP_Image_Free(bossFrontIcon);
    CP_Image_Free(bossBackIcon);
    CP_Image_Free(bossRightIcon);
    CP_Image_Free(bossLeftIcon);

    CP_Image_Free(Key);
    CP_Image_Free(Trap);
    CP_Image_Free(Water);
    CP_Image_Free(heal);
    CP_Image_Free(printer);
    CP_Image_Free(heal_inventory);
    CP_Image_Free(key_inventory);
    CP_Image_Free(energybar_icon);
}