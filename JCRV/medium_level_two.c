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

float mediumtwo_pixelX = 1200;
float mediumtwo_pixelY = 180;

int mediumtwo_LevelVisible = 0;
int mediumtwo_IconVisible = 0;

//player can move
int mediumtwo_player_move = 0;
float mediumtwo_playerspeed = 250.0f;

int mediumtwo_direction;
int mediumtwo_guarddirection;
int mediumtwo_guardtwodirection;
int mediumtwo_guardthreedirection;
int mediumtwo_guardturn = 0;
int mediumtwo_guardtwoturn = 0;
int mediumtwo_guardthreeturn = 0;

float mediumtwo_guardpixelX = 1060;
float mediumtwo_guardpixelY = 400;

float mediumtwo_guardtwopixelX = 900;
float mediumtwo_guardtwopixelY = 540;

float mediumtwo_guardthreepixelX = 600;
float mediumtwo_guardthreepixelY = 600;

float mediumtwo_guard_speed = 200.0f;
int mediumtwo_guardone_move = 0;
int mediumtwo_guardtwo_move = 0;
int mediumtwo_guardthree_move = 0;
int mediumtwo_guardIconVisible = 0;

int mediumtwo_key_id = 6;
int mediumtwo_key = 0;

//keys
int mediumtwo_alpha1 = 100;
int mediumtwo_alpha2 = 100;
int mediumtwo_alpha3 = 100;
int is_mediumtwokey_active = 1;
int is_mediumtwokey_active2 = 1;
int is_mediumtwokey_active3 = 1;
CP_Vector mediumtwo_keyone = { 1240.0f, 720.0f };
CP_Vector mediumtwo_keytwo = { 660.0f, 740.0f };
CP_Vector mediumtwo_keythree = { 300.0f, 260.0f };

CP_Vector mediumtwo_printer_one = { 450.0f, 500.0f };
CP_BOOL AmmoAlive; //(Added)
float mediumtwo_ammoSpawnTimer; //(Added)
static CP_Vector mediumtwo_ammoPosition; //(Added)
float mediumtwo_radian_x;
float mediumtwo_radian_y;
float mediumtwo_degree;
float mediumtwo_a;
float mediumtwo_b;

//energybar
float mediumtwo_max_energy_width = 800.0f;
float mediumtwo_min_energy_width = 0.0f;
float mediumtwo_energy_amount;
float mediumtwo_energybar_x = 145.0f;
float mediumtwo_energybar_y = 30.0f;
float mediumtwo_energybar_h = 40.0f;

//inventory
int mediumtwo_selected_slot;
#define MAX_INVENTORY_SIZE 3
int mediumtwo_healingfood_id = 8;
int mediumtwo_speedfood_id = 5;
int mediumtwo_inventoryid[MAX_INVENTORY_SIZE] = { 0 };

int mediumtwo_is_heal_active = 1;

CP_BOOL Paused;

int mediumtwo_level[ROWS][COLS] =
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
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,0,5,5,5,1,5,11,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,0,5,5,5,1,5,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,2,0,5,5,5,5,1,1,1,1,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,0,0,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,0,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,0,5,5,5,5,5,5,5,1,5,5,2,0,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,2,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,1,1,1,1,8,8,8,8,8,8,8,8,1,1,1,1,1,1,1,1,1,1,1,1,5,5,5,5,5,5,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,0,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,0,5,1,1,1,1,1,1,1,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,10,10,5,5,1,1,1,1,1,12,12,12,12,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,12,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,12,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,5,5,5,5,1,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,6,5,5,7,5,5,5,6,5,5,5,5,1,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }

};

static void MediumTwo_Timer(CP_BOOL TimerState)
{
    CP_System_SetFrameRate(60.0f);
    if (TimerState == TRUE)
    {
        timer_init(30.0f);
    }
    Paused = FALSE;
}

static void Mediumtwo_ResetStage()
{

    mediumtwo_is_heal_active = 1;

    for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
        mediumtwo_inventoryid[i] = 0;
    }

    mediumtwo_pixelX = 1200;
    mediumtwo_pixelY = 180;

    mediumtwo_guardpixelX = 1060;
    mediumtwo_guardpixelY = 400;

    mediumtwo_guardtwopixelX = 900;
    mediumtwo_guardtwopixelY = 540;

    mediumtwo_guardthreepixelX = 600;
    mediumtwo_guardthreepixelY = 600;

    mediumtwo_key = 0;
    mediumtwo_alpha1 = 100;
    mediumtwo_alpha2 = 100;
    mediumtwo_alpha3 = 100;
    is_mediumtwokey_active = 1;
    is_mediumtwokey_active2 = 1;
    is_mediumtwokey_active3 = 1;

    AmmoAlive = FALSE;
    mediumtwo_ammoSpawnTimer = 0.0f;
    Paused = FALSE;
}

static int Mediumtwo_CheckWallCollision(float player_x, float player_y)
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

            if (mediumtwo_level[row][col] == WALL)
            {
                return 1;
            }

            if (mediumtwo_level[row][col] == GUARDWALL)
            {
                if (mediumtwo_key < 1)
                {
                    return 1;
                }      
            }

            if (mediumtwo_level[row][col] == GUARDWALL_TWO)
            {
                if (mediumtwo_key < 2)
                {
                    return 1;
                }
            }

            if (mediumtwo_level[row][col] == EXITWALL)
            {
                if (mediumtwo_key != 3)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

static int Mediumtwo_CheckGuardWallCollision(float guard_x, float guard_y)
{
    int left = (int)guard_x / CELL_SIZE;
    int right = (int)(guard_x + GUARD_SIZE - 1) / CELL_SIZE;

    int top = (int)guard_y / CELL_SIZE;
    int bottom = (int)(guard_y + GUARD_SIZE - 1) / CELL_SIZE;

    for (int row = top; row <= bottom; row++)
    {
        for (int col = left; col <= right; col++)
        {

            if (col < 0 || col >= COLS || row < 0 || row >= ROWS)
            {
                return 1;
            }
            if (mediumtwo_level[row][col] == WALL)
            {
                return 1;
            }
        }
    }
    return 0;
}

static int Mediumtwo_CheckGuardPlayerCollision(float pixelX, float pixelY, float guardX, float guardY, float guardtwoX, float guardtwoY, float guardthreeX, float guardthreeY)
{
    if (pixelX < guardX + GUARD_SIZE && pixelX + PLAYER_SIZE > guardX && pixelY < guardY + GUARD_SIZE && pixelY + PLAYER_SIZE > guardY)
    {
        return 1;
    }
    else if (pixelX < guardtwoX + GUARD_SIZE && pixelX + PLAYER_SIZE > guardtwoX && pixelY < guardtwoY + GUARD_SIZE && pixelY + PLAYER_SIZE > guardtwoY)
    {
        return 1;
    }
    else if (pixelX < guardthreeX + GUARD_SIZE && pixelX + PLAYER_SIZE > guardthreeX && pixelY < guardthreeY + GUARD_SIZE && pixelY + PLAYER_SIZE > guardthreeY)
    {
        return 1;
    }
    return 0;
}

static int Mediumtwo_Obstacles_Collision(float player_x, float player_y)
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
            if (mediumtwo_level[row][col] == TRAP)
            {
                return 1;
            }
        }
    }
    return 0;
}

static int Mediumtwo_PlayerPrinter_Collision(float playerX, float playerY, float printerX, float printerY)
{
    float printer_left = printerX - (PRINTER_SIZE / 2.0f);
    float printer_top = printerY - (PRINTER_SIZE / 2.0f);
    if (PrinterIntersecting(playerX, playerY, printer_left, printer_top)) {
        return 1;
    }
    return 0;
}

static int Mediumtwo_AmmoWall_Collision(float ammo_x, float ammo_y)
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
            if (mediumtwo_level[row][col] == WALL)
            {
                return 1;
            }
        }
    }
    return 0;
}

static int Mediumtwo_Key_Collision(float player_x, float player_y, float keyX, float keyY)
{
    if (KeyIntersecting(player_x, player_y, keyX, keyY)) {
        return 1;
    }
    return 0;
}

static int Mediumtwo_Water_Collision(float player_x, float player_y)
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
            if (mediumtwo_level[row][col] == WATER)
            {
                return 1;
            }
        }
    }
    return 0;
}

static int  Mediumtwo_PowerUp_Collision(float player_x, float player_y)
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
            if (mediumtwo_level[row][col] == HEAL)
            {
                return 1;
            }
        }
    }
    return 0;
}

static int Mediumtwo_Exit_Collision(float player_x, float player_y)
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
            if (mediumtwo_level[row][col] == EXIT)
            {
                return 1;
            }
        }
    }
    return 0;
}
static void MediumTwo_EnergyBar(void)
{
    if (mediumtwo_energy_amount < mediumtwo_min_energy_width) mediumtwo_energy_amount = mediumtwo_min_energy_width;
    if (mediumtwo_energy_amount > mediumtwo_max_energy_width) mediumtwo_energy_amount = mediumtwo_max_energy_width;

    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_StrokeWeight(2.0f);

    CP_Settings_Fill(CP_Color_Create(80, 80, 80, 255));
    CP_Graphics_DrawRect(mediumtwo_energybar_x, mediumtwo_energybar_y, mediumtwo_max_energy_width, mediumtwo_energybar_h);

    if (mediumtwo_energy_amount < 600.0f && mediumtwo_energy_amount > 200.0f) {
        CP_Settings_Fill(CP_Color_Create(255, 165, 0, 255));
        CP_Graphics_DrawRect(mediumtwo_energybar_x, mediumtwo_energybar_y, mediumtwo_energy_amount, mediumtwo_energybar_h);
    }
    else if (mediumtwo_energy_amount < 200.0f) {
        CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
        CP_Graphics_DrawRect(mediumtwo_energybar_x, mediumtwo_energybar_y, mediumtwo_energy_amount, mediumtwo_energybar_h);
    }
    else {
        CP_Settings_Fill(CP_Color_Create(50, 200, 50, 255));
        CP_Graphics_DrawRect(mediumtwo_energybar_x, mediumtwo_energybar_y, mediumtwo_energy_amount, mediumtwo_energybar_h);
    }
}

static void MediumTwo_Inventory(void)
{
    if (CP_Input_KeyTriggered(KEY_1)) {
        mediumtwo_selected_slot = 0;
    }
    if (CP_Input_KeyTriggered(KEY_2)) {
        mediumtwo_selected_slot = 1;
    }
    if (CP_Input_KeyTriggered(KEY_3)) {
        mediumtwo_selected_slot = 2;
    }

    if ((mediumtwo_is_heal_active == 1) && Mediumtwo_PowerUp_Collision(mediumtwo_pixelX, mediumtwo_pixelY)) {
        int item_placed = 0;
        //remove item after item gets picked up
        for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
            if (mediumtwo_inventoryid[i] == mediumtwo_healingfood_id) {

                mediumtwo_is_heal_active = 0;
                item_placed = 1;
                break;
            }
        }
        //check for empty slot in inventory. if found, put item in empty slot
        if (!item_placed) {
            for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
                if (mediumtwo_inventoryid[i] == 0) {
                    mediumtwo_inventoryid[i] = mediumtwo_healingfood_id;

                    mediumtwo_is_heal_active = 0;
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
        if (i == mediumtwo_selected_slot) {
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

        if (mediumtwo_inventoryid[i] == mediumtwo_healingfood_id) {
            CP_Settings_ImageMode(CP_POSITION_CENTER);
            CP_Image_Draw(heal_inventory, slot_x, slot_y, 200.0f, 200.0f, 255);
            CP_Settings_ImageMode(CP_POSITION_CORNER);
        }
    }
    if (CP_Input_KeyTriggered(KEY_R)) {

        if (mediumtwo_inventoryid[mediumtwo_selected_slot] == mediumtwo_healingfood_id) {
            mediumtwo_energy_amount += 100.0f;
            if (mediumtwo_energy_amount > mediumtwo_max_energy_width)
            {
                mediumtwo_energy_amount = mediumtwo_max_energy_width;
            }
            mediumtwo_inventoryid[mediumtwo_selected_slot] = 0;
        }
        if (mediumtwo_inventoryid[mediumtwo_selected_slot] == mediumtwo_key_id)
        {
            mediumtwo_key = 1;
            mediumtwo_inventoryid[mediumtwo_selected_slot] = 0;
        }
    }
}

static void MediumTwo_PauseScreen(void)
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

static void MediumTwo_DeathScreen(void)
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
            mediumtwo_energy_amount = mediumtwo_max_energy_width;
            for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
                mediumtwo_inventoryid[i] = 0;
            }
            Mediumtwo_ResetStage();
        }
        else if (IsAreaClicked(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 320.0f, 400.0f, 130.0f, mouseX, mouseY)) {
            CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
        }
    }
}

void Medium_Level_Two_Init(void)
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

    mediumtwo_energy_amount = currenthealthamount;
    startFOV();
    Mediumtwo_ResetStage();
    MediumTwo_Timer(TimerState);
}

void Medium_Level_Two_Update(void)
{
    CP_Graphics_ClearBackground(CP_Color_Create(115, 147, 179, 255));

    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_ImageMode(CP_POSITION_CORNER);

    float deltaTime = CP_System_GetDt();

    mediumtwo_player_move = 1;
    mediumtwo_guardone_move = 1;
    mediumtwo_guardtwo_move = 1;
    mediumtwo_guardthree_move = 1;
    mediumtwo_guardIconVisible = 1;
    mediumtwo_IconVisible = 1;
    mediumtwo_LevelVisible = 1;

    if (mediumtwo_LevelVisible == 1)
    {
        CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
        CP_Color floor_color = CP_Color_Create(115, 147, 179, 255);
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (mediumtwo_level[row][col] == WALL)
                {
                    CP_Color wall_color = CP_Color_Create(173, 216, 230, 255);
                    CP_Settings_Fill(wall_color);
                    CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE);
                }
                else if (mediumtwo_level[row][col] == TILES)
                {
                    CP_Settings_Fill(floor_color);
                    CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE);
                }
                else if (mediumtwo_level[row][col] == TRAP)
                {
                    CP_Settings_Fill(floor_color);
                    CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)TRAP_SIZE, (float)TRAP_SIZE);
                    CP_Image_Draw(Trap, (float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)TRAP_SIZE, (float)TRAP_SIZE, 255);
                }
                else if (mediumtwo_level[row][col] == HEAL) {
                    if (mediumtwo_is_heal_active) {
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
                else if (mediumtwo_level[row][col] == EXITWALL)
                {
                    if (mediumtwo_key == 3)
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
                else if (mediumtwo_level[row][col] == GUARDWALL)
                {
                    CP_Color remove = CP_Color_Create(255, 0, 0, 255);
                    CP_Settings_Fill(remove);
                    if (mediumtwo_key < 1)
                    {
                        CP_Graphics_DrawRect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                    }
                    else
                    {
                        CP_Settings_Fill(floor_color);
                        CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE);
                    }
                }

                else if (mediumtwo_level[row][col] == GUARDWALL_TWO)
                {
                    CP_Color remove = CP_Color_Create(255, 0, 0, 255);
                    CP_Settings_Fill(remove);
                    if (mediumtwo_key < 2)
                    {
                        CP_Graphics_DrawRect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                    }
                    else
                    {
                        CP_Settings_Fill(floor_color);
                        CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE);
                    }
                }
                else if (mediumtwo_level[row][col] == WATER)
                {
                    CP_Settings_Fill(floor_color);
                    CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE);
                    CP_Image_Draw(Water, (float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE, 255);
                }
            }
        }
    }

    if (Mediumtwo_Key_Collision(mediumtwo_pixelX, mediumtwo_pixelY, mediumtwo_keyone.x, mediumtwo_keyone.y) && (is_mediumtwokey_active == 1)) {
        is_mediumtwokey_active = 0;
        if (mediumtwo_key == 0) {
            mediumtwo_alpha1 = 255;
        }
        if (mediumtwo_key == 1) {
            mediumtwo_alpha2 = 255;
        }
        if (mediumtwo_key == 2) {
            mediumtwo_alpha3 = 255;
        }
        mediumtwo_key++;
    }
    if (Mediumtwo_Key_Collision(mediumtwo_pixelX, mediumtwo_pixelY, mediumtwo_keytwo.x, mediumtwo_keytwo.y) && (is_mediumtwokey_active2 == 1)) {
        is_mediumtwokey_active2 = 0;
        if (mediumtwo_key == 0) {
            mediumtwo_alpha1 = 255;
        }
        if (mediumtwo_key == 1) {
            mediumtwo_alpha2 = 255;
        }
        if (mediumtwo_key == 2) {
            mediumtwo_alpha3 = 255;
        }
        mediumtwo_key++;
    }
    if (Mediumtwo_Key_Collision(mediumtwo_pixelX, mediumtwo_pixelY, mediumtwo_keythree.x, mediumtwo_keythree.y) && (is_mediumtwokey_active3 == 1)) {
        is_mediumtwokey_active3 = 0;
        if (mediumtwo_key == 0) {
            mediumtwo_alpha1 = 255;
        }
        if (mediumtwo_key == 1) {
            mediumtwo_alpha2 = 255;
        }
        if (mediumtwo_key == 2) {
            mediumtwo_alpha3 = 255;
        }
        mediumtwo_key++;
    }

    if (is_mediumtwokey_active == 1) {
        draw_key(Key, mediumtwo_keyone.x, mediumtwo_keyone.y);
    }
    if (is_mediumtwokey_active2 == 1) {
       draw_key(Key, mediumtwo_keytwo.x, mediumtwo_keytwo.y);
    }
    if (is_mediumtwokey_active3 == 1) {
        draw_key(Key, mediumtwo_keythree.x, mediumtwo_keythree.y);
    }

    CP_Image_Draw(key_inventory, 250.0f, 15.0f, 200.0f, 200.0f, mediumtwo_alpha1);
    CP_Image_Draw(key_inventory, 300.0f, 15.0f, 200.0f, 200.0f, mediumtwo_alpha2);
    CP_Image_Draw(key_inventory, 350.0f, 15.0f, 200.0f, 200.0f, mediumtwo_alpha3);

    draw_obstacle_printer(printer, mediumtwo_printer_one.x, mediumtwo_printer_one.y);
    if (AmmoAlive == FALSE) {
        mediumtwo_ammoSpawnTimer += deltaTime;
    }

    if (!AmmoAlive && mediumtwo_ammoSpawnTimer >= 1.0f) {   // fires every 3 seconds
        AmmoAlive = TRUE;
        mediumtwo_ammoSpawnTimer = 0.0f;
        mediumtwo_degree = return_degree();

        //direction cosines(90 half 180)
        mediumtwo_radian_x = return_radian_x();
        mediumtwo_radian_y = return_radian_y();

        //magnitudes

        mediumtwo_a = PRINTER_SIZE / 2.0f;
        mediumtwo_b = PRINTER_SIZE / 2.0f;
        //vectors(added printer position so it spawns from there
        mediumtwo_ammoPosition.x = mediumtwo_printer_one.x + (mediumtwo_radian_x * mediumtwo_a);
        mediumtwo_ammoPosition.y = mediumtwo_printer_one.y + (mediumtwo_radian_y * mediumtwo_b);

    }
    if (AmmoAlive == TRUE) {
        float ammoSpeed = 200.0f;

        mediumtwo_ammoPosition.x += (deltaTime * ammoSpeed) * mediumtwo_radian_x;
        mediumtwo_ammoPosition.y += (deltaTime * ammoSpeed) * mediumtwo_radian_y;

        if (AreBoxesIntersecting(mediumtwo_pixelX, mediumtwo_pixelY, mediumtwo_ammoPosition.x, mediumtwo_ammoPosition.y))
        {
            mediumtwo_energy_amount -= 100.0f;
            if (mediumtwo_energy_amount < mediumtwo_min_energy_width) {
                mediumtwo_energy_amount = 0.0f;
            }
            draw_printer_ammo(mediumtwo_ammoPosition.x, mediumtwo_ammoPosition.y, AMMO_SIZE, AMMO_SIZE);
            AmmoAlive = FALSE;
        }
        else if (Mediumtwo_AmmoWall_Collision(mediumtwo_ammoPosition.x, mediumtwo_ammoPosition.y))
        {
            draw_printer_ammo(mediumtwo_ammoPosition.x, mediumtwo_ammoPosition.y, AMMO_SIZE, AMMO_SIZE);
            AmmoAlive = FALSE;
        }
        else {
            draw_printer_ammo(mediumtwo_ammoPosition.x, mediumtwo_ammoPosition.y, AMMO_SIZE, AMMO_SIZE);
        }
    }
    if (mediumtwo_IconVisible == 1)
    {
        if (mediumtwo_direction == 0)
        {
            CP_Image_Draw(playerRightIcon,mediumtwo_pixelX, mediumtwo_pixelY, (float)PLAYER_SIZE, (float)PLAYER_SIZE, 255);
        }
        else if (mediumtwo_direction == 180)
        {
            CP_Image_Draw(playerLeftIcon, mediumtwo_pixelX, mediumtwo_pixelY, (float)PLAYER_SIZE, (float)PLAYER_SIZE, 255);
        }
        else if (mediumtwo_direction == 90)
        {
            CP_Image_Draw(playerFrontIcon, mediumtwo_pixelX, mediumtwo_pixelY, (float)PLAYER_SIZE, (float)PLAYER_SIZE, 255);
        }
        else if (mediumtwo_direction == 270)
        {
            CP_Image_Draw(playerBackIcon, mediumtwo_pixelX, mediumtwo_pixelY, (float)PLAYER_SIZE, (float)PLAYER_SIZE, 255);
        }
    }

    if (mediumtwo_guardIconVisible == 1)
    {
        if (mediumtwo_guarddirection == 0)
        {
            CP_Image_Draw(bossRightIcon, mediumtwo_guardpixelX, mediumtwo_guardpixelY, GUARD_SIZE, GUARD_SIZE, 255);
        }
        else if (mediumtwo_guarddirection == 180)
        {
            CP_Image_Draw(bossLeftIcon, mediumtwo_guardpixelX, mediumtwo_guardpixelY, GUARD_SIZE, GUARD_SIZE, 255);
        }

        if (mediumtwo_guardtwodirection == 90)
        {
            CP_Image_Draw(bossFrontIcon, mediumtwo_guardtwopixelX, mediumtwo_guardtwopixelY, GUARD_SIZE, GUARD_SIZE, 255);
        }
        else if (mediumtwo_guardtwodirection == 270)
        {
            CP_Image_Draw(bossBackIcon, mediumtwo_guardtwopixelX, mediumtwo_guardtwopixelY, GUARD_SIZE, GUARD_SIZE, 255);
        }

        if (mediumtwo_guardthreedirection == 0)
        {
            CP_Image_Draw(bossRightIcon, mediumtwo_guardthreepixelX, mediumtwo_guardthreepixelY, GUARD_SIZE, GUARD_SIZE, 255);
        }
        else if (mediumtwo_guardthreedirection == 180)
        {
            CP_Image_Draw(bossLeftIcon, mediumtwo_guardthreepixelX, mediumtwo_guardthreepixelY, GUARD_SIZE, GUARD_SIZE, 255);
        }
    }
    CP_Settings_ImageMode(CP_POSITION_CENTER);

    if (Mediumtwo_Obstacles_Collision(mediumtwo_pixelX, mediumtwo_pixelY))
    {
        if (mediumtwo_energy_amount > mediumtwo_min_energy_width)
        {
            mediumtwo_energy_amount -= 20.0f * deltaTime;

        }
    }

    if (Mediumtwo_Exit_Collision(mediumtwo_pixelX, mediumtwo_pixelY) && mediumtwo_key == 3)
    {
        currenthealthamount = mediumtwo_energy_amount;
        CP_Engine_SetNextGameState(Medium_Level_Three_Init, Medium_Level_Three_Update, Medium_Level_Three_Exit);
        CP_Engine_Run(0);
    }

    //FOV(pixelX, pixelY);

    //energybar
    MediumTwo_EnergyBar();
    MediumTwo_Inventory();

    //level wall creation
    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_StrokeWeight(0.1f);

    if (TimerState == TRUE)
    {
        timer_print();
    }

    //Key "P" condition to pause
    if (CP_Input_KeyTriggered(KEY_P) && mediumtwo_energy_amount > mediumtwo_min_energy_width)
    {
        Paused = TRUE;
    }

    if (Paused)
    {
        MediumTwo_PauseScreen();
        mediumtwo_player_move = 0;
        mediumtwo_guardone_move = 0;
        mediumtwo_guardtwo_move = 0;
        mediumtwo_guardthree_move = 0;
        mediumtwo_guardIconVisible = 0;
        mediumtwo_IconVisible = 0;
        mediumtwo_LevelVisible = 0;;
    }
    else
    {
        timer_countdown(deltaTime);
        CP_Settings_TextSize(40.0f);
    }

    if ((TimerState == FALSE && mediumtwo_energy_amount <= mediumtwo_min_energy_width) || (TimerState == TRUE && (mediumtwo_energy_amount <= mediumtwo_min_energy_width || remainingTime() <= 0)))
    {
        MediumTwo_DeathScreen();
        mediumtwo_player_move = 0;
        mediumtwo_guardone_move = 0;
        mediumtwo_guardtwo_move = 0;
        mediumtwo_guardthree_move = 0;
        mediumtwo_guardIconVisible = 0;
        mediumtwo_IconVisible = 0;
        mediumtwo_LevelVisible = 0;
    }

    float move_amount = mediumtwo_playerspeed * deltaTime;
    float speed_scale = 1.0f;

    if (mediumtwo_player_move == 1)
    {
        if (Mediumtwo_Water_Collision(mediumtwo_pixelX, mediumtwo_pixelY)) {
            speed_scale = 0.4f;
        }
        if (CP_Input_KeyDown(KEY_W))
        {
            mediumtwo_direction = 270;

            if (!Mediumtwo_CheckWallCollision(mediumtwo_pixelX, mediumtwo_pixelY - move_amount) &&
                !Mediumtwo_PlayerPrinter_Collision(mediumtwo_pixelX, mediumtwo_pixelY - move_amount, mediumtwo_printer_one.x, mediumtwo_printer_one.y))
            {
                mediumtwo_pixelY -= move_amount * speed_scale;
            }
        }
        else if (CP_Input_KeyDown(KEY_S))
        {
            mediumtwo_direction = 90;
            if (!Mediumtwo_CheckWallCollision(mediumtwo_pixelX, mediumtwo_pixelY + move_amount) &&
                !Mediumtwo_PlayerPrinter_Collision(mediumtwo_pixelX, mediumtwo_pixelY + move_amount, mediumtwo_printer_one.x, mediumtwo_printer_one.y))
            {
                mediumtwo_pixelY += move_amount * speed_scale;
            }
        }
        else if (CP_Input_KeyDown(KEY_A))
        {
            mediumtwo_direction = 180;
            if (!Mediumtwo_CheckWallCollision(mediumtwo_pixelX - move_amount, mediumtwo_pixelY) &&
                !Mediumtwo_PlayerPrinter_Collision(mediumtwo_pixelX - move_amount, mediumtwo_pixelY, mediumtwo_printer_one.x, mediumtwo_printer_one.y))
            {
                mediumtwo_pixelX -= move_amount * speed_scale;
            }

        }
        else if (CP_Input_KeyDown(KEY_D))
        {
            mediumtwo_direction = 0;
            if (!Mediumtwo_CheckWallCollision(mediumtwo_pixelX + move_amount, mediumtwo_pixelY) &&
                !Mediumtwo_PlayerPrinter_Collision(mediumtwo_pixelX + move_amount, mediumtwo_pixelY, mediumtwo_printer_one.x, mediumtwo_printer_one.y))
            {
                mediumtwo_pixelX += move_amount * speed_scale;
            }
        }
    }

    float guardmove_amount = mediumtwo_guard_speed * deltaTime;
    if (mediumtwo_guardone_move == 1)
    {
        if (mediumtwo_guardpixelX + GUARD_SIZE >= 1360)
        {
            mediumtwo_guarddirection = 180;
            mediumtwo_guardturn = 1;
        }
        else if (mediumtwo_guardpixelX <= 1060)
        {
            mediumtwo_guarddirection = 0;
            mediumtwo_guardturn = 0;
        }

        if (mediumtwo_guardturn == 0 && !Mediumtwo_CheckGuardPlayerCollision(mediumtwo_pixelX, mediumtwo_pixelY, mediumtwo_guardpixelX, mediumtwo_guardpixelY,
            mediumtwo_guardtwopixelX, mediumtwo_guardtwopixelY, mediumtwo_guardthreepixelX, mediumtwo_guardthreepixelY))
        {
            mediumtwo_guardpixelX += guardmove_amount;
        }

        if (mediumtwo_guardturn == 1 &&!Mediumtwo_CheckGuardPlayerCollision(mediumtwo_pixelX, mediumtwo_pixelY, mediumtwo_guardpixelX, mediumtwo_guardpixelY,
            mediumtwo_guardtwopixelX, mediumtwo_guardtwopixelY, mediumtwo_guardthreepixelX, mediumtwo_guardthreepixelY))
        {
            mediumtwo_guardpixelX -= guardmove_amount;
        }
    }
    if (mediumtwo_guardtwo_move == 1)
    {
        if (mediumtwo_guardtwopixelY + GUARD_SIZE >= 800)
        {
            mediumtwo_guardtwodirection = 270;
            mediumtwo_guardtwoturn = 1;
        }
        else if (mediumtwo_guardtwopixelY <= 540)
        {
            mediumtwo_guardtwodirection = 90;
            mediumtwo_guardtwoturn = 0;
        }
        if (mediumtwo_guardtwoturn == 0 && !Mediumtwo_CheckGuardPlayerCollision(mediumtwo_pixelX, mediumtwo_pixelY, mediumtwo_guardpixelX, mediumtwo_guardpixelY,
            mediumtwo_guardtwopixelX, mediumtwo_guardtwopixelY, mediumtwo_guardthreepixelX, mediumtwo_guardthreepixelY))
        {
            mediumtwo_guardtwopixelY += guardmove_amount;
        }

        if (mediumtwo_guardtwoturn == 1 && !Mediumtwo_CheckGuardPlayerCollision(mediumtwo_pixelX, mediumtwo_pixelY, mediumtwo_guardpixelX, mediumtwo_guardpixelY,
            mediumtwo_guardtwopixelX, mediumtwo_guardtwopixelY, mediumtwo_guardthreepixelX, mediumtwo_guardthreepixelY))
        {
            mediumtwo_guardtwopixelY -= guardmove_amount;
        }
    }
    if (mediumtwo_guardthree_move == 1)
    {
        if (mediumtwo_guardthreepixelX >= 600)
        {
            mediumtwo_guardthreedirection = 180;
            mediumtwo_guardthreeturn = 1;
        }
        else if (mediumtwo_guardthreepixelX + GUARD_SIZE <= 300)
        {
            mediumtwo_guardthreedirection = 0;
            mediumtwo_guardthreeturn = 0;
        }

        if (mediumtwo_guardthreeturn == 0 && !Mediumtwo_CheckGuardPlayerCollision(mediumtwo_pixelX, mediumtwo_pixelY, mediumtwo_guardpixelX, mediumtwo_guardpixelY,
            mediumtwo_guardtwopixelX, mediumtwo_guardtwopixelY, mediumtwo_guardthreepixelX, mediumtwo_guardthreepixelY))
        {
            mediumtwo_guardthreepixelX += guardmove_amount;
        }

        if (mediumtwo_guardthreeturn == 1 && !Mediumtwo_CheckGuardPlayerCollision(mediumtwo_pixelX, mediumtwo_pixelY, mediumtwo_guardpixelX, mediumtwo_guardpixelY,
            mediumtwo_guardtwopixelX, mediumtwo_guardtwopixelY, mediumtwo_guardthreepixelX, mediumtwo_guardthreepixelY))
        {
            mediumtwo_guardthreepixelX -= guardmove_amount;
        }
    }

    if (Mediumtwo_CheckGuardPlayerCollision(mediumtwo_pixelX + 20, mediumtwo_pixelY - 20, mediumtwo_guardpixelX, 
        mediumtwo_guardpixelY, mediumtwo_guardtwopixelX, mediumtwo_guardtwopixelY, mediumtwo_guardthreepixelX, mediumtwo_guardthreepixelY))
    {
        if (mediumtwo_energy_amount > mediumtwo_min_energy_width)
        {
            mediumtwo_energy_amount -= 100.0f * deltaTime;
        }
    }
    else if (Mediumtwo_CheckGuardPlayerCollision(mediumtwo_pixelX, mediumtwo_pixelY, mediumtwo_guardpixelX + 20,
        mediumtwo_guardpixelY - 20, mediumtwo_guardtwopixelX, mediumtwo_guardtwopixelY, mediumtwo_guardthreepixelX, mediumtwo_guardthreepixelY))
    {
        if (mediumtwo_energy_amount > mediumtwo_min_energy_width)
        {
            mediumtwo_energy_amount -= 100.0f * deltaTime;
        }
    }
    else if (Mediumtwo_CheckGuardPlayerCollision(mediumtwo_pixelX, mediumtwo_pixelY, mediumtwo_guardpixelX,
        mediumtwo_guardpixelY, mediumtwo_guardtwopixelX + 20, mediumtwo_guardtwopixelY - 20, mediumtwo_guardthreepixelX, mediumtwo_guardthreepixelY))
    {
        if (mediumtwo_energy_amount > mediumtwo_min_energy_width)
        {
            mediumtwo_energy_amount -= 100.0f * deltaTime;
        }
    }
    else if (Mediumtwo_CheckGuardPlayerCollision(mediumtwo_pixelX, mediumtwo_pixelY, mediumtwo_guardpixelX,
        mediumtwo_guardpixelY, mediumtwo_guardtwopixelX, mediumtwo_guardtwopixelY, mediumtwo_guardthreepixelX + 20, mediumtwo_guardthreepixelY - 20))
    {
        if (mediumtwo_energy_amount > mediumtwo_min_energy_width)
        {
            mediumtwo_energy_amount -= 100.0f * deltaTime;
        }
    }

    if (CP_Input_KeyReleased(KEY_Q))
    {
        CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
    }
}

void Medium_Level_Two_Exit(void)
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