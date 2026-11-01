#include <math.h>
#include "cprocessing.h"

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	float minx = area_center_x - (area_width / 2);
	float maxx = area_center_x + (area_width / 2);
	float miny = area_center_y - (area_height / 2);
	float maxy = area_center_y + (area_height / 2);

	if (maxx >= click_x && minx <= click_x && maxy >= click_y && miny <= click_y)
	{
		return 1;
	}
	else {
		return 0;
	}
}

int IsPlayerInRange(float ai_x, float ai_y, float detect_range, float player_x, float player_y)
{
	float direction_x = ai_x - player_x;
	float direction_y = ai_y - player_y;
	float distance = (direction_x * direction_x) + (direction_y * direction_y);

	float rangesquared = detect_range * detect_range;

	if (distance <= rangesquared)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Player_WallCollision(float player_x, float player_y, float player_height, float player_width, float wall_one_x, float wall_one_y, float wall_height, float wall_thickness)
{
	int padding = 5;
	if (player_x <= wall_one_x + wall_thickness + padding && player_x + player_width + padding >= wall_one_x && player_y + player_height + padding >= wall_one_y && player_y - padding<= wall_one_y + wall_height)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int PlayerExit(float player_x, float player_y, float player_height, float player_width, float exit_x, float exit_y, float exit_height, float exit_width)
{
	if(player_x + player_width >= exit_x && player_x + player_width <= exit_x + exit_width && player_y >= exit_y && player_y + player_height <= exit_y + exit_height)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int AI_WallCollision(float ai_x, float ai_y, float ai_height, float ai_width, float wall_x, float wall_y, float wall_height, float wall_thickness)
{
	int padding = 10;
	if (ai_x <= wall_x + wall_thickness + padding && ai_x + ai_width + padding >= wall_x && ai_y + ai_height + padding >= wall_y && ai_y - padding <= wall_y + wall_height)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int AreCirclesIntersecting(float c1_x, float c1_y, float r1, float c2_x, float c2_y, float r2)
//float AreCirclesIntersecting(float ai_x, float ai_y, float r1, float player_x, float player_y, float r2)
{

	float dx = c2_x - c1_x;
	float dy = c2_y - c1_y;
	float max_dist = r1 + r2;
	return (dx * dx + dy * dy) <= (max_dist * max_dist);
	//float distance_x = player_x - ai_x;
	//float distance_y = player_y - ai_y;
	//float dsquared = (distance_x * distance_x) + (distance_y * distance_y);

	//float rangesquared = (r1 + r2) * (r1 + r2);
	//return dsquared;

	//if (dsquared <= rangesquared)
	//{
		//return 1;
	//}
	//else
	//{
		//return 0;
	//}
}