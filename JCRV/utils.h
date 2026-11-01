#pragma once
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int IsPlayerInRange(float ai_x, float ai_y, float detect_range, float player_x, float player_y);
int Player_WallCollision(float player_x, float player_y, float player_height, float player_width, float wall_one_x, float wall_one_y, float wall_height, float wall_thickness);
int AI_WallCollision(float ai_x, float ai_y, float ai_height, float ai_width, float wall_x, float wall_y, float wall_height, float wall_thickness);
int PlayerExit(float player_x, float player_y, float player_height, float player_width, float exit_x, float exit_y, float exit_height, float exit_width);
int AreCirclesIntersecting(float c1_x, float c1_y, float r1, float c2_x, float c2_y, float r2);
//float AreCirclesIntersecting(float ai_x, float ai_y, float r1, float player_x, float player_y, float r2);