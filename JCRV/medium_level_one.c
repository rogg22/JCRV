#include <stdio.h>
#include "cprocessing.h"
#include "game.h"
#include "mainmenu.h"
#include "utils.h"
#include "inventory_energybar.h"
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

float mediumone_pixelX = 360;
float mediumone_pixelY = 180;

int mediumone_LevelVisible = 0;
int mediumone_IconVisible = 0;

//player can move
int mediumone_player_move = 0;
float mediumone_player_speed = 250.0f;

//direction
int mediumone_direction;
int mediumone_guarddirection;
int mediumone_guardtwodirection;
int mediumone_guardturn = 0;

float mediumone_guardpixelX = 220;
float mediumone_guardpixelY = 500;

float mediumone_guardtwopixelX = 1040;
float mediumone_guardtwopixelY = 600;

float mediumone_guard_speed = 200.0f;
int mediumone_guardone_move = 0;
int mediumone_guardtwo_move = 0;
int mediumone_guardIconVisible = 0;

int mediumone_key_id = 6;
int mediumone_key = 0;

int mediumone_alpha1 = 100;
int mediumone_alpha2 = 100;
int mediumone_alpha3 = 100;
int is_mediumonekey_active = 1;
int is_mediumonekey_active2 = 1;
int is_mediumonekey_active3 = 1;
CP_Vector mediumone_keyone = { 1280.0f, 200.0f };
CP_Vector mediumone_keytwo = { 360.0f, 700.0f };
CP_Vector mediumone_keythree = { 900.0f, 600.0f };

CP_Vector mediumone_printer_position = { 740.0f, 650.0f };
//Printer stuff
CP_BOOL AmmoAlive; //(Added)
float ammoSpawnTimer; //(Added)
static CP_Vector ammoPosition; //(Added)
float radian_x;
float radian_y;
float degree;
float a;
float b;

//energybar
float mediumone_max_energy_width = 800.0f;
float mediumone_min_energy_width = 0.0f;
float mediumone_energy_amount;
float mediumone_energybar_x = 145.0f;
float mediumone_energybar_y = 30.0f;
float mediumone_energybar_h = 40.0f;
float mediumone_energybar_icon_x = 110.0f;
float mediumone_energybar_icon_y = 50.0f;
float mediumone_energybar_icon_w = 60.0f;
float mediumone_energybar_icon_h = 90.0f;

//inventory
int mediumone_selected_slot;
#define MAX_INVENTORY_SIZE 3
int mediumone_healingfood_id = 8;
int mediumone_speedfood_id = 5;
int mediumone_inventoryid[MAX_INVENTORY_SIZE] = { 0 };

int mediumone_is_heal_active = 1;

CP_BOOL Paused;

int mediumone_level[ROWS][COLS] =
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
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,11,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,0,5,5,1,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,0,5,5,1,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,1,1,1,8,8,8,8,8,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,2,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,2,0,5,5,5,5,5,5,1,5,5,5,5,5,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,2,0,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,0,0,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,0,0,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,10,10,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,10,10,10,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,1,1,1,1,5,5,5,5,5,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,5,5,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,2,0,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,0,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,0,0,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,0,5,1,1,1,5,5,5,5,5,1,5,5,5,5,5,1,1,1,1,1,1,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,2,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,2,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,1,1,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,2,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,6,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,0,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,10,5,5,6,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,0,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,10,5,5,6,5,7,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,2,0,5,5,5,5,5,5,5,5,5,5,5,6,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,5,0,0,5,5,5,5,5,5,5,5,5,5,5,6,5,5,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }

};

void MediumOne_Timer(CP_BOOL TimerState)
{
    CP_System_SetFrameRate(60.0f);
    if (TimerState == TRUE)
    {
        timer_init(30.0f);
    }
    Paused = FALSE;
}

static void Mediumone_ResetStage()
{
    mediumone_is_heal_active = 1;

    mediumone_pixelX = 360;
    mediumone_pixelY = 180;

    mediumone_guardpixelX = 220;
    mediumone_guardpixelY = 500;

    mediumone_guardtwopixelX = 1040;
    mediumone_guardtwopixelY = 600;

    mediumone_alpha1 = 100;
    mediumone_alpha2 = 100;
    mediumone_alpha3 = 100;
    is_mediumonekey_active = 1;
    is_mediumonekey_active2 = 1;
    is_mediumonekey_active3 = 1;
    mediumone_key = 0;

    // printer and ammo
    AmmoAlive = FALSE;
    ammoSpawnTimer = 0.0f;

    Paused = FALSE;
}

static int Mediumone_CheckWallCollision(float player_x, float player_y)
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
            if (mediumone_level[row][col] == WALL)
            {
                return 1;
            }
            if (mediumone_level[row][col] == GUARDWALL)
            {
                if (mediumone_key < 2)
                {
                    return 1;
                }      
            }

            if (mediumone_level[row][col] == EXITWALL)
            {
                if (mediumone_key != 3)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

static int Mediumone_CheckGuardWallCollision(float guard_x, float guard_y)
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
            if (mediumone_level[row][col] == WALL)
            {
                return 1;
            }
        }
        return 0;
    }
}

static int Mediumone_CheckGuardPlayerCollision(float pixelX, float pixelY, float guardX, float guardY, float guardtwoX, float guardtwoY)
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

static int Mediumone_Obstacles_Collision(float player_x, float player_y)
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
            if (mediumone_level[row][col] == TRAP)
            {
                return 1;
            }
        }
    }
    return 0;
}

static int Mediumone_PlayerPrinter_Collision(float playerX, float playerY, float printerX, float printerY)
{
    float printer_left = printerX - (PRINTER_SIZE / 2.0f);
    float printer_top = printerY - (PRINTER_SIZE / 2.0f);
    if (PrinterIntersecting(playerX, playerY, printer_left, printer_top)) {
        return 1;
    }
    return 0;
}

static int Mediumone_AmmoWall_Collision(float ammo_x, float ammo_y)
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
            if (mediumone_level[row][col] == WALL)
            {
                return 1;
            }
        }
    }
    return 0;
}

static int Mediumone_Key_Collision(float player_x, float player_y, float keyX, float keyY)
{
    if (KeyIntersecting(player_x, player_y, keyX, keyY)) {
        return 1;
    }
    return 0;
}

static int Mediumone_Water_Collision(float player_x, float player_y)
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
            if (mediumone_level[row][col] == WATER)
            {
                return 1;
            }
        }
    }
    return 0;
}

static int Mediumone_PowerUp_Collision(float player_x, float player_y)
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
            if (mediumone_level[row][col] == HEAL)
            {
                return 1;
            }
        }
    }
    return 0;
}

static int Mediumone_Exit_Collision(float player_x, float player_y)
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
            if (mediumone_level[row][col] == EXIT)
            {
                return 1;
            }
        }
    }
    return 0;
}
static void MediumOne_EnergyBar()
{
    if (mediumone_energy_amount < mediumone_min_energy_width) mediumone_energy_amount = mediumone_min_energy_width;
    if (mediumone_energy_amount > mediumone_max_energy_width) mediumone_energy_amount = mediumone_max_energy_width;

    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_StrokeWeight(2.0f);

    CP_Image_Draw(energybar_icon, mediumone_energybar_icon_x, mediumone_energybar_icon_y, mediumone_energybar_icon_w, mediumone_energybar_icon_h, 255);

    CP_Settings_Fill(CP_Color_Create(80, 80, 80, 255));
    CP_Graphics_DrawRect(mediumone_energybar_x, mediumone_energybar_y, mediumone_max_energy_width, mediumone_energybar_h);

    if (mediumone_energy_amount < 600.0f && mediumone_energy_amount > 200.0f) {
        CP_Settings_Fill(CP_Color_Create(255, 165, 0, 255));
        CP_Graphics_DrawRect(mediumone_energybar_x, mediumone_energybar_y, mediumone_energy_amount, mediumone_energybar_h);
    }
    else if (mediumone_energy_amount < 200.0f) {
        CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
        CP_Graphics_DrawRect(mediumone_energybar_x, mediumone_energybar_y, mediumone_energy_amount, mediumone_energybar_h);
    }
    else {
        CP_Settings_Fill(CP_Color_Create(50, 200, 50, 255));
        CP_Graphics_DrawRect(mediumone_energybar_x, mediumone_energybar_y, mediumone_energy_amount, mediumone_energybar_h);
    }
}

static void MediumOne_Inventory()
{
    if (CP_Input_KeyTriggered(KEY_1)) {
        mediumone_selected_slot = 0;
    }
    if (CP_Input_KeyTriggered(KEY_2)) {
        mediumone_selected_slot = 1;
    }
    if (CP_Input_KeyTriggered(KEY_3)) {
        mediumone_selected_slot = 2;
    }
    if ((mediumone_is_heal_active == 1) && Mediumone_PowerUp_Collision(mediumone_pixelX, mediumone_pixelY)) {
        int item_placed = 0;
        //remove item after item gets picked up
        for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
            if (mediumone_inventoryid[i] == mediumone_healingfood_id) {

                mediumone_is_heal_active = 0;
                item_placed = 1;
                break;
            }
        }
        //check for empty slot in inventory. if found, put item in empty slot
        if (!item_placed) {
            for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
                if (mediumone_inventoryid[i] == 0) {
                    mediumone_inventoryid[i] = mediumone_healingfood_id;

                    mediumone_is_heal_active = 0;
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
        if (i == mediumone_selected_slot) {
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

        if (mediumone_inventoryid[i] == mediumone_healingfood_id) {
            CP_Settings_ImageMode(CP_POSITION_CENTER);
            CP_Image_Draw(heal_inventory, slot_x, slot_y, 200.0f, 200.0f, 255);
            CP_Settings_ImageMode(CP_POSITION_CORNER);
        }
    }
    if (CP_Input_KeyTriggered(KEY_R)) {

        if (mediumone_inventoryid[mediumone_selected_slot] == mediumone_healingfood_id) {
            mediumone_energy_amount += 100.0f;
            if (mediumone_energy_amount > mediumone_max_energy_width)
            {
                mediumone_energy_amount = mediumone_max_energy_width;
            }
            mediumone_inventoryid[mediumone_selected_slot] = 0;
        }
        //else if (inventoryid[selected_slot] == speedfood_id) {
        //    player_velocity += 20.0f;
        //    inventoryid[selected_slot] = 0;
        //}
    }
}

void MediumOne_PauseScreen()
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

void MediumOne_DeathScreen()
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
            mediumone_energy_amount = mediumone_max_energy_width;
            for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
                mediumone_inventoryid[i] = 0;
            }
            Mediumone_ResetStage();
        }
        else if (IsAreaClicked(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 320.0f, 400.0f, 130.0f, mouseX, mouseY)) {
            CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
        }
    }
}

void Medium_Level_One_Init(void)
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

    mediumone_energy_amount = mediumone_max_energy_width;
    for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
        mediumone_inventoryid[i] = 0;
    }

    startFOV();
    Mediumone_ResetStage();
    MediumOne_Timer(TimerState);
}

void Medium_Level_One_Update()
{
    CP_Graphics_ClearBackground(CP_Color_Create(115, 147, 179, 255));

    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_ImageMode(CP_POSITION_CORNER);

    float deltaTime = CP_System_GetDt();

    mediumone_player_move = 1;
    mediumone_guardone_move = 1;
    mediumone_guardtwo_move = 1;
    mediumone_IconVisible = 1;
    mediumone_guardIconVisible = 1;
    mediumone_LevelVisible = 1;

    if (mediumone_LevelVisible == 1)
    {
        CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
        CP_Color floor_color = CP_Color_Create(115, 147, 179, 255);
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (mediumone_level[row][col] == WALL)
                {
                    CP_Color wall_color = CP_Color_Create(173, 216, 230, 255);
                    CP_Settings_Fill(wall_color);
                    CP_Graphics_DrawRect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                }
                else if (mediumone_level[row][col] == TILES)
                {
                    CP_Settings_Fill(floor_color);
                    CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE);
                }
                else if (mediumone_level[row][col] == TRAP)
                {
                    CP_Settings_Fill(floor_color);
                    CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)TRAP_SIZE, (float)TRAP_SIZE);
                    CP_Image_Draw(Trap, (float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)TRAP_SIZE, (float)TRAP_SIZE, 255);
                }
                else if (mediumone_level[row][col] == HEAL) {
                    if (mediumone_is_heal_active) {
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
                else if (mediumone_level[row][col] == EXITWALL)
                {
                    if (mediumone_key == 3)
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
                else if (mediumone_level[row][col] == GUARDWALL)
                {
                    CP_Color remove = CP_Color_Create(255, 0, 0, 255);
                    CP_Settings_Fill(remove);
                    if (mediumone_key < 2)
                    {
                        CP_Graphics_DrawRect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                    }

                    else
                    {
                        CP_Settings_Fill(floor_color);
                        CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE);
                    }
                }
                else if (mediumone_level[row][col] == WATER)
                {
                    CP_Settings_Fill(floor_color);
                    CP_Graphics_DrawRect((float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE);
                    CP_Image_Draw(Water, (float)col * CELL_SIZE, (float)row * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE, 255);
                }
            }
        }
    }

    if (Mediumone_Key_Collision(mediumone_pixelX, mediumone_pixelY, mediumone_keyone.x, mediumone_keyone.y) && (is_mediumonekey_active == 1)) {
        is_mediumonekey_active = 0;
        if (mediumone_key == 0) {
            mediumone_alpha1 = 255;
        }
        if (mediumone_key == 1) {
            mediumone_alpha2 = 255;
        }
        if (mediumone_key == 2) {
            mediumone_alpha3 = 255;
        }
        mediumone_key++;
    }
    if (Mediumone_Key_Collision(mediumone_pixelX, mediumone_pixelY, mediumone_keytwo.x, mediumone_keytwo.y) && (is_mediumonekey_active2 == 1)) {
        is_mediumonekey_active2 = 0;
        if (mediumone_key == 0) {
            mediumone_alpha1 = 255;
        }
        if (mediumone_key == 1) {
            mediumone_alpha2 = 255;
        }
        if (mediumone_key == 2) {
            mediumone_alpha3 = 255;
        }
        mediumone_key++;
    }
    if (Mediumone_Key_Collision(mediumone_pixelX, mediumone_pixelY, mediumone_keythree.x, mediumone_keythree.y) && (is_mediumonekey_active3 == 1)) {
        is_mediumonekey_active3 = 0;
        if (mediumone_key == 0) {
            mediumone_alpha1 = 255;
        }
        if (mediumone_key == 1) {
            mediumone_alpha2 = 255;
        }
        if (mediumone_key == 2) {
            mediumone_alpha3 = 255;
        }
        mediumone_key++;
    }

    if (is_mediumonekey_active == 1) {
        draw_key(Key, mediumone_keyone.x, mediumone_keyone.y);
    }
    if (is_mediumonekey_active2 == 1) {
        draw_key(Key, mediumone_keytwo.x, mediumone_keytwo.y);
    }
    if (is_mediumonekey_active3 == 1) {
        draw_key(Key, mediumone_keythree.x, mediumone_keythree.y);
    }

    CP_Image_Draw(key_inventory, 250.0f, 15.0f, 200.0f, 200.0f, mediumone_alpha1);
    CP_Image_Draw(key_inventory, 300.0f, 15.0f, 200.0f, 200.0f, mediumone_alpha2);
    CP_Image_Draw(key_inventory, 350.0f, 15.0f, 200.0f, 200.0f, mediumone_alpha3);

    draw_obstacle_printer(printer, mediumone_printer_position.x, mediumone_printer_position.y);

    if (AmmoAlive == FALSE) {
        ammoSpawnTimer += deltaTime;
    }

    if (!AmmoAlive && ammoSpawnTimer >= 1.0f) {   // fires every 3 seconds
        AmmoAlive = TRUE;
        ammoSpawnTimer = 0.0f;
        degree = return_degree();

        //direction cosines(90 half 180)
        radian_x = return_radian_x();
        radian_y = return_radian_y();

        //magnitudes

        a = PRINTER_SIZE / 2.0f;
        b = PRINTER_SIZE / 2.0f;
        //vectors(added printer position so it spawns from there
        ammoPosition.x = mediumone_printer_position.x + (radian_x * a);
        ammoPosition.y = mediumone_printer_position.y + (radian_y * b);

    }
    if (AmmoAlive == TRUE) {
        float ammoSpeed = 200.0f;

        ammoPosition.x += (deltaTime * ammoSpeed) * radian_x;
        ammoPosition.y += (deltaTime * ammoSpeed) * radian_y;

        if (AreBoxesIntersecting(mediumone_pixelX, mediumone_pixelY, ammoPosition.x, ammoPosition.y))
        {
            mediumone_energy_amount -= 100.0f;
            if (mediumone_energy_amount < mediumone_min_energy_width) {
                mediumone_energy_amount = 0.0f;
            }
            draw_printer_ammo(ammoPosition.x, ammoPosition.y, AMMO_SIZE, AMMO_SIZE);
            AmmoAlive = FALSE;
        }
        else if (Mediumone_AmmoWall_Collision(ammoPosition.x, ammoPosition.y))
        {
            draw_printer_ammo(ammoPosition.x, ammoPosition.y, AMMO_SIZE, AMMO_SIZE);
            AmmoAlive = FALSE;
        }
        else {
            draw_printer_ammo(ammoPosition.x, ammoPosition.y, AMMO_SIZE, AMMO_SIZE);
        }
    }

    if (mediumone_IconVisible == 1)
    {
        if (mediumone_direction == 0)
        {
            CP_Image_Draw(playerRightIcon, mediumone_pixelX, mediumone_pixelY, PLAYER_SIZE, PLAYER_SIZE, 255);
        }
        else if (mediumone_direction == 180)
        {
            CP_Image_Draw(playerLeftIcon, mediumone_pixelX, mediumone_pixelY, PLAYER_SIZE, PLAYER_SIZE, 255);
        }
        else if (mediumone_direction == 90)
        {
            CP_Image_Draw(playerFrontIcon, mediumone_pixelX, mediumone_pixelY, PLAYER_SIZE, PLAYER_SIZE, 255);
        }
        else if (mediumone_direction == 270)
        {
            CP_Image_Draw(playerBackIcon, mediumone_pixelX, mediumone_pixelY, PLAYER_SIZE, PLAYER_SIZE, 255);
        }
    }

    if (mediumone_guardIconVisible == 1)
    {
        if (mediumone_guarddirection == 0)
        {
            CP_Image_Draw(bossRightIcon, mediumone_guardpixelX, mediumone_guardpixelY, GUARD_SIZE, GUARD_SIZE, 255);
        }
        else if (mediumone_guarddirection == 2)
        {
            CP_Image_Draw(bossLeftIcon, mediumone_guardpixelX, mediumone_guardpixelY, GUARD_SIZE, GUARD_SIZE, 255);
        }
        else if (mediumone_guarddirection == 1)
        {
            CP_Image_Draw(bossFrontIcon, mediumone_guardpixelX, mediumone_guardpixelY, GUARD_SIZE, GUARD_SIZE, 255);
        }
        else if (mediumone_guarddirection == 3)
        {
            CP_Image_Draw(bossBackIcon, mediumone_guardpixelX, mediumone_guardpixelY, GUARD_SIZE, GUARD_SIZE, 255);
        }

        if (mediumone_guardtwodirection == 0)
        {
            CP_Image_Draw(bossRightIcon, mediumone_guardtwopixelX, mediumone_guardtwopixelY, GUARD_SIZE, GUARD_SIZE, 255);
        }
        else if (mediumone_guardtwodirection == 180)
        {
            CP_Image_Draw(bossLeftIcon, mediumone_guardtwopixelX, mediumone_guardtwopixelY, GUARD_SIZE, GUARD_SIZE, 255);
        }
    }

    CP_Settings_ImageMode(CP_POSITION_CENTER);

    if (Mediumone_Obstacles_Collision(mediumone_pixelX, mediumone_pixelY))
    {
        if (mediumone_energy_amount > mediumone_min_energy_width)
        {
            mediumone_energy_amount -= 20.0f * deltaTime;
        }
    }

    if (Mediumone_Exit_Collision(mediumone_pixelX, mediumone_pixelY) && mediumone_key == 3)
    {
        currenthealthamount = mediumone_energy_amount;
        CP_Engine_SetNextGameState(Medium_Level_Two_Init, Medium_Level_Two_Update, Medium_Level_Two_Exit);
        CP_Engine_Run(0);
    }

    //FOV(pixelX, pixelY);
    MediumOne_EnergyBar();
    MediumOne_Inventory();

    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_StrokeWeight(0.1f);

    if (TimerState == TRUE)
    {
        timer_print();
    }

    //Key "P" condition to pause
    if (CP_Input_KeyTriggered(KEY_P) && mediumone_energy_amount > mediumone_min_energy_width)
    {
        Paused = TRUE;
    }

    if (Paused)
    {
        MediumOne_PauseScreen();
        mediumone_player_move = 0;
        mediumone_guardone_move = 0;
        mediumone_guardtwo_move = 0;
        mediumone_IconVisible = 0;
        mediumone_guardIconVisible = 0;
        mediumone_LevelVisible = 0;
    }
    else
    {
        timer_countdown(deltaTime);
        CP_Settings_TextSize(40.0f);
    }

    if ((TimerState == FALSE && mediumone_energy_amount <= mediumone_min_energy_width) || (TimerState == TRUE && (mediumone_energy_amount <= mediumone_min_energy_width || remainingTime() <= 0)))
    {
        MediumOne_DeathScreen();
        mediumone_player_move = 0;
        mediumone_guardone_move = 0;
        mediumone_guardtwo_move = 0;
        mediumone_IconVisible = 0;
        mediumone_guardIconVisible = 0;
        mediumone_LevelVisible = 0;
    }

    float playermove_amount = mediumone_player_speed * deltaTime;
    float speed_scale = 1.0f;

    if (mediumone_player_move == 1)
    {
        if (Mediumone_Water_Collision(mediumone_pixelX, mediumone_pixelY)) {
            speed_scale = 0.4f;
        }
        if (CP_Input_KeyDown(KEY_W))
        {
            mediumone_direction = 270;

            //if (!Mediumone_CheckWallCollision(mediumone_pixelX, mediumone_pixelY - playermove_amount) && 
            //    !Mediumone_CheckGuardPlayerCollision(mediumone_pixelX, mediumone_pixelY - playermove_amount, mediumone_guardpixelX, 
            //        mediumone_guardpixelY, mediumone_guardtwopixelX, mediumone_guardtwopixelY) &&
            //    !Mediumone_PlayerPrinter_Collision(mediumone_pixelX, mediumone_pixelY - playermove_amount, mediumone_printer_position.x, mediumone_printer_position.y))
            if (!Mediumone_CheckWallCollision(mediumone_pixelX, mediumone_pixelY - playermove_amount) && 
                !Mediumone_PlayerPrinter_Collision(mediumone_pixelX, mediumone_pixelY - playermove_amount, mediumone_printer_position.x, mediumone_printer_position.y))
            {
                mediumone_pixelY -= playermove_amount * speed_scale;
            }
        }
        else if (CP_Input_KeyDown(KEY_S))
        {
            mediumone_direction = 90;
            //if (!Mediumone_CheckWallCollision(mediumone_pixelX, mediumone_pixelY + playermove_amount) && 
            //    !Mediumone_CheckGuardPlayerCollision(mediumone_pixelX, mediumone_pixelY + playermove_amount, mediumone_guardpixelX, 
            //        mediumone_guardpixelY, mediumone_guardtwopixelX, mediumone_guardtwopixelY) &&
            //    !Mediumone_PlayerPrinter_Collision(mediumone_pixelX, mediumone_pixelY + playermove_amount, mediumone_printer_position.x, mediumone_printer_position.y))
            if (!Mediumone_CheckWallCollision(mediumone_pixelX, mediumone_pixelY + playermove_amount) &&
                !Mediumone_PlayerPrinter_Collision(mediumone_pixelX, mediumone_pixelY + playermove_amount, mediumone_printer_position.x, mediumone_printer_position.y))
            {
                mediumone_pixelY += playermove_amount * speed_scale;
            }
        }
        else if (CP_Input_KeyDown(KEY_A))
        {
            mediumone_direction = 180;
            if (!Mediumone_CheckWallCollision(mediumone_pixelX - playermove_amount, mediumone_pixelY) && 
                !Mediumone_PlayerPrinter_Collision(mediumone_pixelX - playermove_amount, mediumone_pixelY, mediumone_printer_position.x, mediumone_printer_position.y))
            //if (!Mediumone_CheckWallCollision(mediumone_pixelX - playermove_amount, mediumone_pixelY) && 
            //    !Mediumone_CheckGuardPlayerCollision(mediumone_pixelX - playermove_amount, mediumone_pixelY, mediumone_guardpixelX, 
            //        mediumone_guardpixelY, mediumone_guardtwopixelX, mediumone_guardtwopixelY) && 
            //    !Mediumone_PlayerPrinter_Collision(mediumone_pixelX - playermove_amount, mediumone_pixelY, mediumone_printer_position.x, mediumone_printer_position.y))
            {
                mediumone_pixelX -= playermove_amount * speed_scale;
            }

        }
        else if (CP_Input_KeyDown(KEY_D))
        {
            mediumone_direction = 0;
            if (!Mediumone_CheckWallCollision(mediumone_pixelX + playermove_amount, mediumone_pixelY) && 
                !Mediumone_PlayerPrinter_Collision(mediumone_pixelX + playermove_amount, mediumone_pixelY, mediumone_printer_position.x, mediumone_printer_position.y))
            //if (!Mediumone_CheckWallCollision(mediumone_pixelX + playermove_amount, mediumone_pixelY) && 
            //    !Mediumone_CheckGuardPlayerCollision(mediumone_pixelX + playermove_amount, mediumone_pixelY, mediumone_guardpixelX,
            //        mediumone_guardpixelY, mediumone_guardtwopixelX, mediumone_guardtwopixelY) &&
            //    !Mediumone_PlayerPrinter_Collision(mediumone_pixelX + playermove_amount, mediumone_pixelY, mediumone_printer_position.x, mediumone_printer_position.y))
            {
                mediumone_pixelX += playermove_amount * speed_scale;
            }
        }
    }

    float guardmove_amount = mediumone_guard_speed * deltaTime;
    if (mediumone_guardone_move == 1)
    {
        switch (mediumone_guarddirection)
        {
        case 0:
            if (!Mediumone_CheckGuardPlayerCollision(mediumone_pixelX, mediumone_pixelY, mediumone_guardpixelX,
                mediumone_guardpixelY, mediumone_guardtwopixelX, mediumone_guardtwopixelY))
            {
                mediumone_guardpixelX += guardmove_amount;
            }
            if (mediumone_guardpixelX >= 420)
            {
                mediumone_guarddirection = 1;
            }
            break;
        case 1:
            if (!Mediumone_CheckGuardPlayerCollision(mediumone_pixelX, mediumone_pixelY, mediumone_guardpixelX,
                mediumone_guardpixelY, mediumone_guardtwopixelX, mediumone_guardtwopixelY))
            {
                mediumone_guardpixelY += guardmove_amount;
            }
            if (mediumone_guardpixelY >= 740)
            {
                mediumone_guarddirection = 2;
            }
            break;
        case 2:
            if (!Mediumone_CheckGuardPlayerCollision(mediumone_pixelX, mediumone_pixelY, mediumone_guardpixelX,
                mediumone_guardpixelY, mediumone_guardtwopixelX, mediumone_guardtwopixelY))
            {
                mediumone_guardpixelX -= guardmove_amount;
            }
            if (mediumone_guardpixelX <= 220)
            {
                mediumone_guarddirection = 3;
            }
            break;
        case 3:
            if (!Mediumone_CheckGuardPlayerCollision(mediumone_pixelX, mediumone_pixelY, mediumone_guardpixelX,
                mediumone_guardpixelY, mediumone_guardtwopixelX, mediumone_guardtwopixelY))
            {
                mediumone_guardpixelY -= guardmove_amount;
            }
            if (mediumone_guardpixelY <= 500)
            {
                mediumone_guarddirection = 0;
            }
            break;
        }
    }

    if (mediumone_guardtwo_move == 1)
    {
        if (mediumone_guardtwopixelX + GUARD_SIZE >= 1360)
        {
            mediumone_guardtwodirection = 180;
            mediumone_guardturn = 1;
        }
        else if (mediumone_guardtwopixelX <= 1040)
        {
            mediumone_guardtwodirection = 0;
            mediumone_guardturn = 0;
        }

        if (mediumone_guardturn == 0 && !Mediumone_CheckGuardPlayerCollision(mediumone_pixelX, mediumone_pixelY, mediumone_guardpixelX,
            mediumone_guardpixelY, mediumone_guardtwopixelX, mediumone_guardtwopixelY))
        {
            mediumone_guardtwopixelX += guardmove_amount;
        }

        if (mediumone_guardturn == 1 && !Mediumone_CheckGuardPlayerCollision(mediumone_pixelX, mediumone_pixelY, mediumone_guardpixelX,
            mediumone_guardpixelY, mediumone_guardtwopixelX, mediumone_guardtwopixelY))
        {
            mediumone_guardtwopixelX -= guardmove_amount;
        }
    }

    if (Mediumone_CheckGuardPlayerCollision(mediumone_pixelX + 20, mediumone_pixelY - 20, mediumone_guardpixelX, 
        mediumone_guardpixelY, mediumone_guardtwopixelX, mediumone_guardtwopixelY))
    {
        if (mediumone_energy_amount > mediumone_min_energy_width)
        {
            mediumone_energy_amount -= 100.0f * deltaTime;
        }
    }
    else if (Mediumone_CheckGuardPlayerCollision(mediumone_pixelX, mediumone_pixelY, mediumone_guardpixelX + 20, 
        mediumone_guardpixelY - 20, mediumone_guardtwopixelX, mediumone_guardtwopixelY))
    {
        if (mediumone_energy_amount > mediumone_min_energy_width)
        {
            mediumone_energy_amount -= 100.0f * deltaTime;
        }
    }
    else if (Mediumone_CheckGuardPlayerCollision(mediumone_pixelX, mediumone_pixelY, mediumone_guardpixelX, 
        mediumone_guardpixelY, mediumone_guardtwopixelX + 20, mediumone_guardtwopixelY - 20))
    {
        if (mediumone_energy_amount > mediumone_min_energy_width)
        {
            mediumone_energy_amount -= 100.0f * deltaTime;
        }
    }

    if (CP_Input_KeyReleased(KEY_Q))
    {
        mediumone_pixelX = 360;
        mediumone_pixelY = 180;
        mediumone_direction = 0;

        CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
        CP_System_SetWindowSize(1600, 900);
        CP_Engine_Run(0);
    }
}

void Medium_Level_One_Exit(void)
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