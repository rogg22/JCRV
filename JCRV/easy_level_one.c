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

int easyone_playerX = 18;
int easyone_playerY = 33;

int easyone_IconVisible = 0;
int easyone_LevelVisible = 0;

//player can move
int easyone_player_move = 0;
float easyone_player_velocity = 350;

//direction
int easyone_direction;

int easyone_key_id = 6;
int easyone_key = 0;
float easyone_key_width = 30;
float easyone_key_height = 20;
float easyone_key_x = 910;
float easyone_key_y = 220;
int is_easyonekey_active = 1;

//energybar
float easyone_max_energy_width = 800.0f;
float easyone_min_energy_width = 0.0f;
float easyone_energy_amount;
float easyone_energybar_x = 145.0f;
float easyone_energybar_y = 30.0f;
float easyone_energybar_h = 40.0f;

//inventory
int easyone_selected_slot;
#define MAX_INVENTORY_SIZE 3
int easyone_healingfood_id = 8;
int easyone_speedfood_id = 5;
int easyone_inventoryid[MAX_INVENTORY_SIZE] = { 0 };

float easyone_heal_x = 1050;
float easyone_heal_y = 450;
int easyone_is_heal_active = 1;
float easyone_itemradius = 40;

CP_BOOL Paused;

int easyone_level[ROWS][COLS] =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,7,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,6,6,6,6,6,6,6,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

};

int easythree_level[ROWS][COLS] =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,7,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,6,6,6,6,6,6,6,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

};


void Easy_Level_One_Init(void)
{
    myFont = CP_Font_Load("Assets/BoldsPixels.ttf");
    CP_Font_Set(myFont);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_TextSize(40.0f);
    playerFrontIcon = CP_Image_Load("Assets/playerFrontIcon.PNG");
    playerBackIcon = CP_Image_Load("Assets/playerBackIcon.PNG");
    playerLeftIcon = CP_Image_Load("Assets/playerLeftIcon.PNG");
    playerRightIcon = CP_Image_Load("Assets/playerRightIcon.PNG");
    startFOV();

    easyone_energy_amount = easyone_max_energy_width;

    for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
        easyone_inventoryid[i] = 0;
    }

    Easyone_Timer(TimerState);

    easyone_playerX = 18;
    easyone_playerY = 33;
}

void Easy_Level_One_Update()
{

    CP_Graphics_ClearBackground(CP_Color_Create(115, 147, 179, 255));

    CP_Settings_RectMode(CP_POSITION_CORNER);

    float deltaTime = CP_System_GetDt();

    int pixelX = easyone_playerX * CELL_SIZE;
    int pixelY = easyone_playerY * CELL_SIZE;

    easyone_player_move = 1;
    easyone_IconVisible = 1;
    easyone_LevelVisible = 1;

    CP_Color wall_color = CP_Color_Create(173, 216, 230, 255);
    CP_Settings_Fill(wall_color);

    if (easyone_player_move == 1)
    {
        if (CP_Input_KeyDown(KEY_W))
        {
            //easyone_player_y += -easyone_player_velocity * deltaTime;
            easyone_direction = 270;
            if (!Easyone_CheckWallCollision(easyone_playerX, easyone_playerY - 1))
            {
                easyone_playerY--;
                //test_playerY -= easytwo_player_velocity * deltaTime;
            }
        }
        else if (CP_Input_KeyDown(KEY_S))
        {
            //easyone_player_y += easyone_player_velocity * deltaTime;
            easyone_direction = 90;
            if (!Easyone_CheckWallCollision(easyone_playerX, easyone_playerY + 1))
            {
                easyone_playerY++;
            }
        }
        else if (CP_Input_KeyDown(KEY_A))
        {
            //easyone_player_x += -easyone_player_velocity * deltaTime;
            easyone_direction = 180;
            if (!Easyone_CheckWallCollision(easyone_playerX - 1, easyone_playerY))
            {
                easyone_playerX --;
                //test_playerY -= easytwo_player_velocity * deltaTime;
            }
        }
        else if (CP_Input_KeyDown(KEY_D))
        {
            //easyone_player_x += easyone_player_velocity * deltaTime;
            easyone_direction = 0;
            if (!Easyone_CheckWallCollision(easyone_playerX + 1, easyone_playerY))
            {
                easyone_playerX ++;
            }
        }
    }
    if (easyone_LevelVisible == 1)
    {
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (easyone_level[row][col] == WALL)
                {
                    CP_Graphics_DrawRect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                }
                else if (easyone_level[row][col] == TRAP)
                {
                    CP_Graphics_DrawRect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                }
                else if (easyone_level[row][col] == KEY)
                {
                    if (is_easyonekey_active)
                    {
                        CP_Graphics_DrawRect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                    }
                }
                else if (easyone_level[row][col] == PRINTER)
                {
                    CP_Color printer = CP_Color_Create(50, 220, 50, 255);
                    CP_Settings_Fill(printer);
                    CP_Graphics_DrawRect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                }
                else if (easyone_level[row][col] == HEAL)
                {
                    if (easyone_is_heal_active)
                    {
                        CP_Color healcolor = CP_Color_Create(100, 100, 255, 255);
                        CP_Settings_Fill(healcolor);
                        CP_Graphics_DrawRect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                    }
                }
                else if (easyone_level[row][col] == EXITWALL)
                {
                    if (!easyone_key)
                    {
                        CP_Color exit_color = CP_Color_Create(255, 255, 255, 255);
                        CP_Settings_Fill(exit_color);
                        CP_Graphics_DrawRect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                    }
                }
                else
                {
                    CP_Settings_Fill(wall_color);
                }
            }
        }
    }

    if (easyone_IconVisible == 1)
    {
        if (easyone_direction == 0)
        {
            //CP_Image_Draw(playerRightIcon, easyone_player_x, easyone_player_y, easyone_player_width, easyone_player_height, 255);
            CP_Image_Draw(playerRightIcon, pixelX + 40, pixelY + 40, PLAYER_SIZE, PLAYER_SIZE, 255);
        }
        else if (easyone_direction == 180)
        {
            //CP_Image_Draw(playerLeftIcon, easyone_player_x, easyone_player_y, easyone_player_width, easyone_player_height, 255);
            CP_Image_Draw(playerLeftIcon, pixelX + 40, pixelY + 40, PLAYER_SIZE, PLAYER_SIZE, 255);
        }
        else if (easyone_direction == 90)
        {
            //CP_Image_Draw(playerFrontIcon, easyone_player_x, easyone_player_y, easyone_player_width, easyone_player_height, 255);
            CP_Image_Draw(playerFrontIcon, pixelX + 40, pixelY + 40, PLAYER_SIZE, PLAYER_SIZE, 255);
        }
        else if (easyone_direction == 270)
        {
            //CP_Image_Draw(playerBackIcon, easyone_player_x, easyone_player_y, easyone_player_width, easyone_player_height, 255);
            CP_Image_Draw(playerBackIcon, pixelX + 40, pixelY + 40, PLAYER_SIZE, PLAYER_SIZE, 255);
        }
    }

    if (Easyone_Obstacles_Collision(easyone_playerX, easyone_playerY))
    {
        if (easyone_energy_amount > easyone_min_energy_width)
        {
            easyone_energy_amount -= 20.0f * deltaTime;
        }
    }

    if (Easyone_Exit_Collision(easyone_playerX, easyone_playerY))
    {
        CP_Engine_SetNextGameState(Easy_Level_Two_Init, Easy_Level_Two_Update, Easy_Level_Two_Exit);
        CP_Engine_Run(0);
    }

    //FOV(pixelX, pixelY);

    if (TimerState == TRUE)
    {
        timer_print();
    }

    Easyone_EnergyBar();
    Easyone_Inventory(easyone_playerX, easyone_playerY);

    CP_Settings_StrokeWeight(0.1f);

    CP_Settings_RectMode(CP_POSITION_CORNER);

    if (CP_Input_KeyTriggered(KEY_P) && easyone_energy_amount > easyone_min_energy_width)
    {
        Paused = TRUE;
    }

    if (Paused)
    {
        Easyone_PauseScreen();
        easyone_player_move = 0;
        easyone_IconVisible = 0;
        easyone_LevelVisible = 0;
        //ai_move = 0;
    }
    else
    {
        timer_countdown(deltaTime);
        CP_Settings_TextSize(40.0f);
    }

    if ((TimerState == FALSE && easyone_energy_amount <= easyone_min_energy_width) || (TimerState == TRUE && (easyone_energy_amount <= easyone_min_energy_width || remainingTime() <= 0)))
    {
        Easyone_DeathScreen();
        easyone_player_move = 0;
        easyone_IconVisible = 0;
        easyone_LevelVisible = 0;
    }

    if (CP_Input_KeyReleased(KEY_Q))
    {

        CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
        CP_System_SetWindowSize(1600, 900);
        CP_Engine_Run(0);
        return 0;
    }
}

void Easyone_Timer(CP_BOOL TimerState)
{
    CP_System_SetFrameRate(60.0f);
    if (TimerState == TRUE)
    {
        timer_init(30.0f);
    }
    Paused = FALSE;
}

int Easyone_CheckWallCollision(player_x, player_y)
{
    for (int row = 0; row < PLAYER_CELLS; row++)
    {
        for (int col = 0; col < PLAYER_CELLS; col++)
        {
            int checkX = player_x + col;
            int checkY = player_y + row;

            if (checkX < 0 || checkX >= COLS || checkY < 0 || checkY >= ROWS)
            {
                return 1;
            }
            if (easyone_level[checkY][checkX] == WALL)
            {
                return 1;
            }
            if (easyone_level[checkY][checkX] == PRINTER)
            {
                return 1;
            }

            if (easyone_level[checkY][checkX] == EXITWALL)
            {
                if (!easyone_key)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int Easyone_PowerUp_Collision(player_x, player_y)
{
    for (int row = 0; row < PLAYER_CELLS; row++)
    {
        for (int col = 0; col < PLAYER_CELLS; col++)
        {
            int checkX = player_x + col;
            int checkY = player_y + row;

            if (checkX < 0 || checkX >= COLS || checkY < 0 || checkY >= ROWS)
            {
                return 1;
            }
            if (easyone_level[checkY][checkX] == HEAL)
            {
                return 1;
            }
        }
    }
    return 0;
}

int Easyone_Obstacles_Collision(player_x, player_y)
{
    for (int row = 0; row < PLAYER_CELLS; row++)
    {
        for (int col = 0; col < PLAYER_CELLS; col++)
        {
            int checkX = player_x + col;
            int checkY = player_y + row;

            if (checkX < 0 || checkX >= COLS || checkY < 0 || checkY >= ROWS)
            {
                return 1;
            }
            if (easyone_level[checkY][checkX] == TRAP)
            {
                return 1;
            }
        }
    }
    return 0;
}

int Easyone_Key_Collision(player_x, player_y)
{
    for (int row = 0; row < PLAYER_CELLS; row++)
    {
        for (int col = 0; col < PLAYER_CELLS; col++)
        {
            int checkX = player_x + col;
            int checkY = player_y + row;

            if (checkX < 0 || checkX >= COLS || checkY < 0 || checkY >= ROWS)
            {
                return 1;
            }
            if (easyone_level[checkY][checkX] == KEY)
            {
                return 1;
            }
        }
    }
    return 0;
}

int Easyone_Exit_Collision(player_x, player_y)
{
    for (int row = 0; row < PLAYER_CELLS; row++)
    {
        for (int col = 0; col < PLAYER_CELLS; col++)
        {
            int checkX = player_x + col;
            int checkY = player_y + row;

            if (checkX < 0 || checkX >= COLS || checkY < 0 || checkY >= ROWS)
            {
                return 1;
            }
            if (easyone_level[checkY][checkX] == EXIT)
            {
                return 1;
            }
        }
    }
    return 0;
}

void Easyone_EnergyBar()
{
    if (easyone_energy_amount < easyone_min_energy_width) easyone_energy_amount = easyone_min_energy_width;
    if (easyone_energy_amount > easyone_max_energy_width) easyone_energy_amount = easyone_max_energy_width;

    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_StrokeWeight(2.0f);

    CP_Settings_Fill(CP_Color_Create(80, 80, 80, 255));
    CP_Graphics_DrawRect(easyone_energybar_x, easyone_energybar_y, easyone_max_energy_width, easyone_energybar_h);

    if (easyone_energy_amount < 600.0f && easyone_energy_amount > 200.0f) {
        CP_Settings_Fill(CP_Color_Create(255, 165, 0, 255));
        CP_Graphics_DrawRect(easyone_energybar_x, easyone_energybar_y, easyone_energy_amount, easyone_energybar_h);
    }
    else if (easyone_energy_amount < 200.0f) {
        CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
        CP_Graphics_DrawRect(easyone_energybar_x, easyone_energybar_y, easyone_energy_amount, easyone_energybar_h);
    }
    else {
        CP_Settings_Fill(CP_Color_Create(50, 200, 50, 255));
        CP_Graphics_DrawRect(easyone_energybar_x, easyone_energybar_y, easyone_energy_amount, easyone_energybar_h);
    }
}
void Easyone_Inventory(player_x, player_y)
{
    if (CP_Input_KeyTriggered(KEY_1)) {
        easyone_selected_slot = 0;
    }
    if (CP_Input_KeyTriggered(KEY_2)) {
        easyone_selected_slot = 1;
    }
    if (CP_Input_KeyTriggered(KEY_3)) {
        easyone_selected_slot = 2;
    }
    if ((easyone_is_heal_active == 1) && Easyone_PowerUp_Collision(easyone_playerX, easyone_playerY)) {
        int item_placed = 0;
        //remove item after item gets picked up
        for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
            if (easyone_inventoryid[i] == easyone_healingfood_id) {
                easyone_is_heal_active = 0;
                item_placed = 1;
                break;
            }
        }
        //check for empty slot in inventory. if found, put item in empty slot
        if (!item_placed) {
            for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
                if (easyone_inventoryid[i] == 0) {
                    easyone_inventoryid[i] = easyone_healingfood_id;

                    easyone_is_heal_active = 0;
                    break;
                }
            }
        }
    }
    if ((is_easyonekey_active == 1) && Easyone_Key_Collision(easyone_playerX, easyone_playerY))
    {
        int item_placed = 0;
        for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
            if (easyone_inventoryid[i] == easyone_key_id) {
                is_easyonekey_active = 0;
                item_placed = 1;
                break;
            }
        }
        if (!item_placed) {
            for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
                if (easyone_inventoryid[i] == 0) {
                    easyone_inventoryid[i] = easyone_key_id;
                    is_easyonekey_active = 0;
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
        if (i == easyone_selected_slot) {
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

        if (easyone_inventoryid[i] == easyone_healingfood_id) {
            CP_Settings_Fill(CP_Color_Create(50, 220, 50, 255));
            CP_Graphics_DrawCircle(slot_x, slot_y, 20.0f);
        }
        //else if (inventoryid[i] == speedfood_id) {
        //    CP_Settings_Fill(CP_Color_Create(220, 220, 50, 255));
        //    CP_Graphics_DrawCircle(slot_x, slot_y, 20.0f);
        //}
        else if (easyone_inventoryid[i] == easyone_key_id)
        {
            CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
            CP_Graphics_DrawCircle(slot_x, slot_y, 20.0f);
        }
    }
    if (CP_Input_KeyTriggered(KEY_R)) {

        if (easyone_inventoryid[easyone_selected_slot] == easyone_healingfood_id) {
            easyone_energy_amount += 50.0f;
            easyone_inventoryid[easyone_selected_slot] = 0;
        }
        //else if (inventoryid[selected_slot] == speedfood_id) {
        //    player_velocity += 20.0f;
        //    inventoryid[selected_slot] = 0;
        //}
        if (easyone_inventoryid[easyone_selected_slot] == easyone_key_id)
        {
            easyone_key = 1;
            easyone_inventoryid[easyone_selected_slot] = 0;
        }
    }
}

void Easyone_PauseScreen()
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

void Easyone_DeathScreen(void)
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
            easyone_energy_amount = easyone_max_energy_width;

            easyone_playerX = 18;
            easyone_playerY = 33;

            easyone_direction = 0;
        }
        else if (IsAreaClicked(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 320.0f, 400.0f, 130.0f, mouseX, mouseY)) {
            CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
        }
    }
}

void Easy_Level_One_Exit(void)
{
    CP_Font_Free(myFont);
    CP_Image_Free(playerFrontIcon);
    CP_Image_Free(playerBackIcon);
    CP_Image_Free(playerLeftIcon);
    CP_Image_Free(playerRightIcon);
}