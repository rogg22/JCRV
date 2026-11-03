#include <stdio.h>
#include "cprocessing.h"
#include "game.h"
#include "mainmenu.h"
#include "utils.h"
#include "inventory_energybar.h"
#include "timer.h"
#include "obstacles.h"
#include "difficultySelection.h"

CP_Font myFont;
CP_Image playerFrontIcon;
CP_Image playerBackIcon;
CP_Image playerLeftIcon;
CP_Image playerRightIcon;

//player
float player_x = 480;
float player_y = 480;
float player_height = 85;
float player_width = 85;

int easythree_IconVisible = 0;

//player can move
int player_move = 0;
float player_velocity = 350;

//int d_right = 0;
//int d_left = 0;
//int d_up = 0;
//int d_down = 0;
int easy_direction = 0;

//ai
float ai_x = 300;
float ai_y = 440;
float ai_height = 90;
float ai_width = 65;
float easythree_detectrange = 130;

float easythree_aitwo_x;
float easythree_aitwo_y;
float easythree_aitwo_height;
float easythree_aitwo_width;

//ai can move
int ai_move = 1;
float ai_velocity = 150;

int ai_right = 0;
int ai_left = 0;
int ai_up = 0;
int ai_down = 0;

float wall_thickness = 10;

//outer left wall
float wall_one_x = 150;
float wall_one_y = 150;
float wall_one_height = 700;

//bottom wall
float wall_two_x = 160;
float wall_two_y = 840;
float wall_two_height = 1230;

//top wall
float wall_three_x = 160;
float wall_three_y = 150;
float wall_three_height = 950;

//outer right wall
float wall_four_x = 1100;
float wall_four_y = 160;
float wall_four_height = 340;

//exit top wall
float wall_five_x = 1030;
float wall_five_y = 500;
float wall_five_height = 360;

//inner right wall
float wall_six_x = 800;
float wall_six_y = 160;
float wall_six_height = 430;

float wall_seven_x = 280;
float wall_seven_y = 280;
float wall_seven_height = 140;

float wall_eight_x = 290;
float wall_eight_y = 280;
float wall_eight_height = 140;

float wall_nine_x = 670;
float wall_nine_y = 280;
float wall_nine_height = 140;

float wall_ten_x = 530;
float wall_ten_y = 280;
float wall_ten_height = 140;

float wall_eleven_x = 280;
float wall_eleven_y = 570;
float wall_eleven_height = 140;

float wall_twelve_x = 290;
float wall_twelve_y = 700;
float wall_twelve_height = 140;

float wall_thirteen_x = 670;
float wall_thirteen_y = 570;
float wall_thirteen_height = 140;

float wall_fourteen_x = 530;
float wall_fourteen_y = 700;
float wall_fourteen_height = 140;

float wall_fifteen_x = 800;
float wall_fifteen_y = 760;
float wall_fifteen_height = 80;

//office wall
float wall_sixteen_x = 810;
float wall_sixteen_y = 500;
float wall_sixteen_height = 70;

//exit wall
float wall_seventeen_x = 1390;
float wall_seventeen_y = 500;
float wall_seventeen_height = 350;

//desk
float easyone_desk_x = 890;
float easyone_desk_y = 270;
float easyone_desk_height = 60;
float easyone_desk_width = 120;

//mainwall
float easyone_mainwall_x = 920;
float easyone_mainwall_y = 630;
float easyone_mainwall_height = 180;
float easyone_mainwall_width = 100;

//exit
float exit_x = 1290;
float exit_y = 590;
float exit_height = 150;
float exit_width = 100;

//key
int easythree_key_id = 6;
int easythree_key = 0;
float easythree_key_width = 30;
float easythree_key_height = 20;
float easythree_key_x = 910;
float easythree_key_y = 220;
int is_easythreekey_active = 1;

float max_energy_width = 800.0f;
float min_energy_width = 0.0f;
float energy_amount;
float energybar_x = 145.0f;
float energybar_y = 30.0f;
float energybar_h = 40.0f;
//inventory
int selected_slot;
#define MAX_INVENTORY_SIZE 3
int healingfood_id = 8;
int speedfood_id = 5;
int inventoryid[MAX_INVENTORY_SIZE] = { 0 };

float damage_x = 850;
float damage_y = 300;
float heal_x = 1050;
float heal_y = 450;
//float speed_x = 500;
//float speed_y = 800;
int is_heal_active = 1;
//int is_speed_active = 1;
float radius = 40;

CP_BOOL Paused;
CP_BOOL Alive;

//obstacles
CP_Vector trap_position1 = { 200, 450 }; // Trap static coordinates
CP_Vector printer_position1 = { 1150, 550 }; // Trap static coordinates
static CP_Vector printer_ammo1 = { 1140, 450 };

float trapWidth = 40.0f;
float trapHeight = 40.0f;
float printerWidth = 80.0f;
float printerHeight = 60.0f;
float printerAmmoWidth = 80.0f;
float printerAmmoHeight = 80.0f;


void Easy_Level_Three_Init(void)
{
    myFont = CP_Font_Load("Assets/BoldsPixels.ttf");
    CP_Font_Set(myFont);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_TextSize(40.0f);
    playerFrontIcon = CP_Image_Load("Assets/playerFrontIcon.PNG");
    playerBackIcon = CP_Image_Load("Assets/playerBackIcon.PNG");
    playerLeftIcon = CP_Image_Load("Assets/playerLeftIcon.PNG");
    playerRightIcon = CP_Image_Load("Assets/playerRightIcon.PNG");

    energy_amount = max_energy_width;

    for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
        inventoryid[i] = 0;
    }

    Timer(TimerState);
}

void Easy_Level_Three_Update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(115, 147, 179, 255));

    CP_Settings_RectMode(CP_POSITION_CORNER);

    float deltaTime = CP_System_GetDt();
    //timer_countdown(deltaTime);

    //bounding box
    float boundingbox_x = player_x - 30;
    float boundingbox_y = player_y - 45;
    float boundingbox_height = 100;
    float boundingbox_width = 75;

    //energy bar
    EnergyBar(boundingbox_x, boundingbox_y);
    Inventory(boundingbox_x, boundingbox_y);

    if (TimerState == TRUE)
    {
        timer_print();
    }

    Obstacles(boundingbox_x, boundingbox_y, boundingbox_height, boundingbox_width);

    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_StrokeWeight(0.1f);

    //player
    //CP_Color player_color = CP_Color_Create(0, 0, 255, 255);
    //CP_Settings_Fill(player_color);
    //CP_Graphics_DrawRect(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height);

    player_move = 1;
    easythree_IconVisible = 1;

    //ai
    CP_Color ai_color = CP_Color_Create(0, 0, 255, 255);
    CP_Settings_Fill(ai_color);
    CP_Graphics_DrawRect(ai_x, ai_y, ai_width, ai_height);

    //wall color
    CP_Color wall_color = CP_Color_Create(173, 216, 230, 255);
    CP_Settings_Fill(wall_color);

    //easy, stage one
    CP_Graphics_DrawRect(wall_one_x, wall_one_y, wall_thickness, wall_one_height);
    CP_Graphics_DrawRect(wall_two_x, wall_two_y, wall_two_height, wall_thickness);
    CP_Graphics_DrawRect(wall_three_x, wall_three_y, wall_three_height, wall_thickness);
    CP_Graphics_DrawRect(wall_four_x, wall_four_y, wall_thickness, wall_four_height);
    CP_Graphics_DrawRect(wall_five_x, wall_five_y, wall_five_height, wall_thickness);
    CP_Graphics_DrawRect(wall_six_x, wall_six_y, wall_thickness, wall_six_height);
    CP_Graphics_DrawRect(wall_seven_x, wall_seven_y, wall_thickness, wall_seven_height);
    CP_Graphics_DrawRect(wall_eight_x, wall_eight_y, wall_eight_height, wall_thickness);
    CP_Graphics_DrawRect(wall_nine_x, wall_nine_y, wall_thickness, wall_nine_height);
    CP_Graphics_DrawRect(wall_ten_x, wall_ten_y, wall_ten_height, wall_thickness);
    CP_Graphics_DrawRect(wall_eleven_x, wall_eleven_y, wall_thickness, wall_eleven_height);
    CP_Graphics_DrawRect(wall_twelve_x, wall_twelve_y, wall_twelve_height, wall_thickness);
    CP_Graphics_DrawRect(wall_thirteen_x, wall_thirteen_y, wall_thickness, wall_thirteen_height);
    CP_Graphics_DrawRect(wall_fourteen_x, wall_fourteen_y, wall_fourteen_height, wall_thickness);
    CP_Graphics_DrawRect(wall_fifteen_x, wall_fifteen_y, wall_thickness, wall_fifteen_height);
    CP_Graphics_DrawRect(wall_sixteen_x, wall_sixteen_y, wall_sixteen_height, wall_thickness);
    CP_Graphics_DrawRect(wall_seventeen_x, wall_seventeen_y, wall_thickness, wall_seventeen_height);
    CP_Graphics_DrawRect(easyone_desk_x, easyone_desk_y, easyone_desk_width, easyone_desk_height);
    CP_Graphics_DrawRect(easyone_mainwall_x, easyone_mainwall_y, easyone_mainwall_height, easyone_mainwall_width);

    CP_Color exit_color = CP_Color_Create(255, 255, 255, 255);
    CP_Settings_Fill(exit_color);
    CP_Graphics_DrawRect(exit_x, exit_y, exit_width, exit_height);
    
    //Key "P" condition to pause
    if (CP_Input_KeyTriggered(KEY_P) && energy_amount > min_energy_width)
    {
        Paused = TRUE;
    }

    if (Paused)
    {
        PauseScreen();
        player_move = 0;
        easythree_IconVisible = 0;
        //ai_move = 0;
    }
    else
    {
        timer_countdown(deltaTime);
        player_move = 1;
        easythree_IconVisible = 1;
        CP_Settings_TextSize(40.0f);
        //ai_move = 1;
        //if ((int)remainingTime() % 10 == 0)
        //{
        //    Alive = TRUE;
        //    draw_printer_ammo(printer_ammo1.x, printer_ammo1.y, printerAmmoWidth, printerAmmoHeight);
        //}
        //if (Alive == TRUE)
        //{
        //    printer_ammo1.x += player_velocity * deltaTime;
        //    //printer_ammo1.x += speed * currentElapsedTime;
        //    draw_printer_ammo(printer_ammo1.x, printer_ammo1.y, printerAmmoWidth, printerAmmoHeight);

        //    if (PrinterIntersecting(player_x, player_y, player_width, player_height, printer_ammo1.x, printer_ammo1.y, printerAmmoWidth, printerAmmoHeight) && energy_amount >= 0)
        //    {
        //        //rectWidth -= currentElapsedTime * healthSpeed;
        //        energy_amount -= 2.0f;
        //        Alive = FALSE;
        //    }
        //}
    }

    if ((TimerState == FALSE && energy_amount <= min_energy_width) || (TimerState == TRUE && (energy_amount <= min_energy_width || remainingTime() <= 0)))
    {
        DeathScreen();
        easythree_IconVisible = 0;
    }

    //player movement
    if (player_move == 1)
    {
        if (CP_Input_KeyDown(KEY_W))
        {
            player_y += -player_velocity * deltaTime;
            easy_direction = 270;
        }
        else if (CP_Input_KeyDown(KEY_S))
        {
            player_y += player_velocity * deltaTime;
            easy_direction = 90;
        }
        else if (CP_Input_KeyDown(KEY_A))
        {
            player_x += -player_velocity * deltaTime;
            easy_direction = 180;
        }
        else if (CP_Input_KeyDown(KEY_D))
        {
            player_x += player_velocity * deltaTime;
            easy_direction = 0;
        }
    }
    
    if (easythree_IconVisible == 1)
    {
        if (easy_direction == 0)
        {
            //CP_Font_DrawText("Right", 850, 850);
            CP_Image_Draw(playerRightIcon, player_x, player_y, player_width, player_height, 255);
        }
        else if (easy_direction == 180)
        {
            //CP_Font_DrawText("Left", 850, 850);

            CP_Image_Draw(playerLeftIcon, player_x, player_y, player_width, player_height, 255);
        }
        else if (easy_direction == 90)
        {
            //CP_Font_DrawText("Down", 850, 850);

            CP_Image_Draw(playerFrontIcon, player_x, player_y, player_width, player_height, 255);
        }
        else if (easy_direction == 270)
        {
            //CP_Font_DrawText("Front", 850, 850);

            CP_Image_Draw(playerBackIcon, player_x, player_y, player_width, player_height, 255);
        }
    }

    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, wall_one_x, wall_one_y, wall_one_height, wall_thickness))
    {
        player_x += collidex(player_x, easy_direction, wall_one_x, wall_thickness, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, wall_one_y, wall_one_height, player_velocity, deltaTime);
        //wallone
    }
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, wall_two_x, wall_two_y, wall_thickness, wall_two_height))
    {
        player_x += collidex(player_x, easy_direction, wall_two_x, wall_two_height, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, wall_two_y, wall_thickness, player_velocity, deltaTime);
        //walltwo
    }
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, wall_three_x, wall_three_y, wall_thickness, wall_three_height))
    {
        player_x += collidex(player_x, easy_direction, wall_three_x, wall_three_height, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, wall_three_y, wall_thickness, player_velocity, deltaTime);
        //wallthree
    }
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, wall_four_x, wall_four_y, wall_four_height, wall_thickness))
    {
        player_x += collidex(player_x, easy_direction, wall_four_x, wall_thickness, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, wall_four_y, wall_four_height, player_velocity, deltaTime);
        //wallfour
    }
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, wall_five_x, wall_five_y, wall_thickness, wall_five_height))
    {
        player_x += collidex(player_x, easy_direction, wall_five_x, wall_five_height, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, wall_five_y, wall_thickness, player_velocity, deltaTime);
        //wallfive
    }
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, wall_six_x, wall_six_y, wall_six_height, wall_thickness))
    {
        player_x += collidex(player_x, easy_direction, wall_six_x, wall_thickness, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, wall_six_y, wall_six_height, player_velocity, deltaTime);
        //wallsix
    }
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, wall_seven_x, wall_seven_y, wall_seven_height, wall_thickness))
    {
        player_x += collidex(player_x, easy_direction, wall_seven_x, wall_thickness, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, wall_seven_y, wall_seven_height, player_velocity, deltaTime);
        //wallseven
    }
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, wall_eight_x, wall_eight_y, wall_thickness, wall_eight_height))
    {
        player_x += collidex(player_x, easy_direction, wall_eight_x, wall_eight_height, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, wall_eight_y, wall_thickness, player_velocity, deltaTime);
        //walleight
    }
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, wall_nine_x, wall_nine_y, wall_nine_height, wall_thickness))
    {
        player_x += collidex(player_x, easy_direction, wall_nine_x, wall_thickness, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, wall_nine_y, wall_nine_height, player_velocity, deltaTime);
        //wallnine
    }
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, wall_ten_x, wall_ten_y, wall_thickness, wall_ten_height))
    {
        player_x += collidex(player_x, easy_direction, wall_ten_x, wall_ten_height, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, wall_ten_y, wall_thickness, player_velocity, deltaTime);
        //wallten
    }
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, wall_eleven_x, wall_eleven_y, wall_eleven_height, wall_thickness))
    {
        player_x += collidex(player_x, easy_direction, wall_eleven_x, wall_thickness, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, wall_eleven_y, wall_eleven_height, player_velocity, deltaTime);
        //walleleven
    }
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, wall_twelve_x, wall_twelve_y, wall_thickness, wall_twelve_height))
    {
        player_x += collidex(player_x, easy_direction, wall_twelve_x, wall_twelve_height, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, wall_twelve_y, wall_thickness, player_velocity, deltaTime);
        //walltwelve
    }
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, wall_thirteen_x, wall_thirteen_y, wall_thirteen_height, wall_thickness))
    {
        player_x += collidex(player_x, easy_direction, wall_thirteen_x, wall_thickness, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, wall_thirteen_y, wall_thirteen_height, player_velocity, deltaTime);
        //wallthirteen
    }
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, wall_fourteen_x, wall_fourteen_y, wall_thickness, wall_fourteen_height))
    {
        player_x += collidex(player_x, easy_direction, wall_fourteen_x, wall_fourteen_height, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, wall_fourteen_y, wall_thickness, player_velocity, deltaTime);
        //wallfourteen
    }
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, wall_fifteen_x, wall_fifteen_y, wall_fifteen_height, wall_thickness))
    {
        player_x += collidex(player_x, easy_direction, wall_fifteen_x, wall_thickness, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, wall_fifteen_y, wall_fifteen_height, player_velocity, deltaTime);
        //wallfifteen
    }
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, wall_sixteen_x, wall_sixteen_y, wall_thickness, wall_sixteen_height))
    {
        player_x += collidex(player_x, easy_direction, wall_sixteen_x, wall_sixteen_height, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, wall_sixteen_y, wall_thickness, player_velocity, deltaTime);
        //wallsixteen
    }
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, wall_seventeen_x, wall_seventeen_y, wall_seventeen_height, wall_thickness))
    {
        player_x += collidex(player_x, easy_direction, wall_seventeen_x, wall_thickness, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, wall_seventeen_y, wall_seventeen_height, player_velocity, deltaTime);
        //wallseventeen
    }
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, easyone_desk_x,  easyone_desk_y, easyone_desk_height, easyone_desk_width))
    {
        player_x += collidex(player_x, easy_direction, easyone_desk_x, easyone_desk_width, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, easyone_desk_y, easyone_desk_height, player_velocity, deltaTime);
        //desk
    }
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, easyone_mainwall_x, easyone_mainwall_y, easyone_desk_height, easyone_desk_width))
    {
        player_x += collidex(player_x, easy_direction, easyone_mainwall_x, easyone_mainwall_width, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, easyone_mainwall_y, easyone_mainwall_height, player_velocity, deltaTime);
        //mainwall
    }

    //check for exit
    CP_BOOL isExit = PlayerExit(boundingbox_x, boundingbox_y, boundingbox_height, boundingbox_width, exit_x, exit_y, exit_height, exit_width);

    //check for exit
    if (isExit)
    {
        if (easythree_key == 1 )
        {
            CP_Engine_SetNextGameState(Easy_Level_Two_Init, Easy_Level_Two_Update, Easy_Level_Two_Exit);
            CP_Engine_Run(0);
        }
    }

    //second ai wall collision
    //CP_BOOL AI_RightWallCollision = AI_WallCollision(ai_x, ai_y, ai_height, ai_width, wall_four_x, wall_four_y, wall_four_height, wall_thickness);
    //CP_BOOL AI_LeftWallCollision = AI_WallCollision(ai_x, ai_y, ai_height, ai_width, wall_six_x, wall_six_y, wall_six_height, wall_thickness);

    //check for ai collision
    if (Player_WallCollision(boundingbox_x, boundingbox_y, boundingbox_width, boundingbox_height, ai_x, ai_y, ai_height, ai_width))
    {
        player_x += collidex(player_x, easy_direction, ai_x, ai_width, player_velocity, deltaTime);
        player_y += collidey(player_y, easy_direction, ai_y, ai_height, player_velocity, deltaTime);
        //aione
    }

    CP_BOOL inrange = IsPlayerInRange(ai_x, ai_y, easythree_detectrange, boundingbox_x, boundingbox_y);

    if (inrange)
    {
        //energy_amount -= 2.0f;
    }

    //ai movement
    //if (ai_move == 1)
    //{
    //    if (ai_right == 1)
    //    {
    //        ai_x += ai_velocity * deltaTime;
    //    }
    //    else if (ai_left == 1)
    //    {
    //        ai_x += -ai_velocity * deltaTime;
    //    }
    //    else if (ai_up == 1)
    //    {
    //        ai_y += -ai_velocity * deltaTime;
    //    }
    //    else if (ai_down == 1)
    //    {
    //        ai_y += ai_velocity * deltaTime;
    //    }

    //    if (ai_x >= wall_seven_x + wall_thickness)
    //    {
    //    }

    //    if(ai_y >= wall_eight_y + wall_thickness + 5 && ai_x + ai_width + 50 <= wall_eight_x + wall_eight_height)
    //    {
    //        ai_up = 1;
    //        ai_left = 0;
    //    }
    //    else
    //    {
    //        ai_up = 0;
    //        if (ai_x + ai_width + 5 <= wall_nine_x && ai_y <= wall_nine_y + wall_nine_height)
    //        {
    //            ai_right = 1;
    //        }
    //        else
    //        {
    //            ai_right = 0;
    //            if (ai_y + ai_height + 5 <= wall_fourteen_y  && ai_x >= wall_ten_x)
    //            {
    //                ai_down = 1;
    //            }
    //            else
    //            {
    //                ai_down = 0;
    //                if (ai_x >= wall_eleven_x + wall_thickness && ai_y >= wall_eleven_y)
    //                {
    //                    ai_left = 1;

    //                }
    //            }
    //        }
    //    }
    //}
    //else if (ai_move == 0)
    //{
    //    ai_velocity = 0;
    //}

    //go back to main menu
    if (CP_Input_KeyReleased(KEY_Q))
    {
        player_x = 480;
        player_y = 480;

        ai_x = 300;
        ai_y = 440;

        //d_right = 0;
        //d_left = 0;
        //d_up = 0;
        //d_down = 0;

        CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
        CP_System_SetWindowSize(1600, 900);
        CP_Engine_Run(0);
        return 0;
    }
}

void EnergyBar(float player_x, float player_y)
{

    //check for damage
    //if (AreCirclesIntersecting(player_x, player_y, 40, damage_x, damage_y, radius)) {
    //    energy_amount -= 2.0f;
    //}

    if (energy_amount < min_energy_width) energy_amount = min_energy_width;
    if (energy_amount > max_energy_width) energy_amount = max_energy_width;

    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_StrokeWeight(2.0f);

    CP_Settings_Fill(CP_Color_Create(80, 80, 80, 255));
    CP_Graphics_DrawRect(energybar_x, energybar_y, max_energy_width, energybar_h);

    if (energy_amount < 600.0f && energy_amount > 200.0f) {
        CP_Settings_Fill(CP_Color_Create(255, 165, 0, 255));
        CP_Graphics_DrawRect(energybar_x, energybar_y, energy_amount, energybar_h);
    }
    else if (energy_amount < 200.0f) {
        CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
        CP_Graphics_DrawRect(energybar_x, energybar_y, energy_amount, energybar_h);
    }
    else {
        CP_Settings_Fill(CP_Color_Create(50, 200, 50, 255));
        CP_Graphics_DrawRect(energybar_x, energybar_y, energy_amount, energybar_h);
    }

    //damage
    //CP_Settings_Fill(CP_Color_Create(220, 50, 50, 255));
    //CP_Graphics_DrawCircle(damage_x, damage_y, radius);
}

void Inventory(float player_x, float player_y)
{

    if (CP_Input_KeyTriggered(KEY_1)) {
        selected_slot = 0;
    }
    if (CP_Input_KeyTriggered(KEY_2)) {
        selected_slot = 1;
    }
    if (CP_Input_KeyTriggered(KEY_3)) {
        selected_slot = 2;
    }

    if ((is_heal_active == 1) && AreCirclesIntersecting(player_x, player_y, 40, heal_x, heal_y, 25.0f)) {
        int item_placed = 0;
        //remove item after item gets picked up
        for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
            if (inventoryid[i] == healingfood_id) {

                is_heal_active = 0;
                item_placed = 1;
                break;
            }
        }
        //check for empty slot in inventory. if found, put item in empty slot
        if (!item_placed) {
            for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
                if (inventoryid[i] == 0) {
                    inventoryid[i] = healingfood_id;

                    is_heal_active = 0;
                    break;
                }
            }
        }
    }
    if ((is_easythreekey_active == 1) && AreCirclesIntersecting(player_x, player_y, 40, easythree_key_x, easythree_key_y, 25.0f))
    {
        int item_placed = 0;
        for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
            if (inventoryid[i] == easythree_key_id) {
                is_easythreekey_active = 0;
                item_placed = 1;
                break;
            }
        }
        if (!item_placed) {
            for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
                if (inventoryid[i] == 0) {
                    inventoryid[i] = easythree_key_id;

                    is_easythreekey_active = 0;
                    break;
                }
            }
        }
    }

    //if ((is_speed_active == 1) && AreCirclesIntersecting(player_x - 30, player_y - 45, 50, speed_x, speed_y, 25.0f)) {
    //    int item_placed = 0;
    //    for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
    //        if (inventoryid[i] == speedfood_id) {

    //            is_speed_active = 0;
    //            item_placed = 1;
    //            break;
    //        }
    //    }
    //    if (!item_placed) {
    //        for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
    //            if (inventoryid[i] == 0) {
    //                inventoryid[i] = speedfood_id;

    //                is_speed_active = 0;
    //                break;
    //            }
    //        }
    //    }
    //}

    //draw heal buff
    if (is_heal_active) {
        CP_Settings_Fill(CP_Color_Create(50, 220, 50, 255));
        CP_Graphics_DrawCircle(heal_x, heal_y, radius);
    }

    if (is_easythreekey_active)
    {
        CP_Color key_color = CP_Color_Create(0, 0, 255, 255);
        CP_Settings_Fill(key_color);
        CP_Graphics_DrawRect(easythree_key_x, easythree_key_y, easythree_key_width, easythree_key_width);
    }

    //draw speed buff
    //if (is_speed_active) {
    //    CP_Settings_Fill(CP_Color_Create(220, 220, 50, 255));
    //    CP_Graphics_DrawCircle(speed_x, speed_y, radius);
    //}

    CP_Settings_RectMode(CP_POSITION_CENTER);
    CP_Settings_StrokeWeight(2.0f);

    //draw inventory
    for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
        float slot_x = 170.0f + (i * 50.0f);
        float slot_y = 110.0f;

        //highlight if selected
        if (i == selected_slot) {
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

        if (inventoryid[i] == healingfood_id) {
            CP_Settings_Fill(CP_Color_Create(50, 220, 50, 255));
            CP_Graphics_DrawCircle(slot_x, slot_y, 20.0f);
        }
        //else if (inventoryid[i] == speedfood_id) {
        //    CP_Settings_Fill(CP_Color_Create(220, 220, 50, 255));
        //    CP_Graphics_DrawCircle(slot_x, slot_y, 20.0f);
        //}
        else if (inventoryid[i] == easythree_key_id)
        {
            CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
            CP_Graphics_DrawCircle(slot_x, slot_y, 20.0f);
        }
    }

    if (CP_Input_KeyTriggered(KEY_R)) {

        //if (inventoryid[selected_slot] == healingfood_id) {
            //energy_amount += 50.0f;
        //    inventoryid[selected_slot] = 0;
        //}
        //else if (inventoryid[selected_slot] == speedfood_id) {
        //    player_velocity += 20.0f;
        //    inventoryid[selected_slot] = 0;
        //}
        if (inventoryid[selected_slot] == easythree_key_id)
        {
            easythree_key = 1;
            inventoryid[selected_slot] = 0;
        }
    }
}

void Timer(CP_BOOL TimerState)
{
    CP_System_SetFrameRate(60.0f);
    if (TimerState == TRUE)
    {
        timer_init(30.0f);
    }
    Paused = FALSE;
}

void Obstacles(float player_x, float player_y, float player_width, float player_height)
{
    printer_ammo1.x = 1140;
    printer_ammo1.y = 450;

    draw_obstacle_trap(trap_position1.x, trap_position1.y, trapWidth, trapHeight);
    //draw_obstacle_printer(printer_ammo1.x, printer_ammo1.y, printerAmmoWidth, printerAmmoHeight);

    if (AreBoxesIntersecting(player_x, player_y, player_width, player_height, trap_position1.x, trap_position1.y, trapWidth, trapHeight) && energy_amount >= 0) {
        energy_amount -= 2.0f;
    }
}

void PauseScreen(void)
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

void DeathScreen(void)
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

            energy_amount = max_energy_width;
            player_x = 480;
            player_y = 480;

            ai_x = 300;
            ai_y = 440;

            easy_direction = 0;

            //d_right = 0;
            //d_left = 0;
            //d_up = 0;
            //d_down = 0;
        }
        else if (IsAreaClicked(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() * 0.25f + 320.0f, 400.0f, 130.0f, mouseX, mouseY)) {
            CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
        }
    }
}

void Easy_Level_Three_Exit(void)
{
    CP_Font_Free(myFont);
}

