#pragma once

void draw_obstacle_trap(float trap_x, float trap_y, float trapWidth, float trapHeight);

void draw_obstacle_printer(float printer_x, float printer_y, float printerWidth, float printerHeight);

void draw_printer_ammo(float printer_x, float printer_y, float printerWidth, float printerHeight);

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);

int AreBoxesIntersecting(float box_center_x, float box_center_y, float box_width, float box_height, float trap_center_x, float trap_center_y, float trap_width, float trap_height);

int PrinterIntersecting(float box_center_x, float box_center_y, float box_width, float box_height, float printer_center_x, float printer_center_y, float printer_width, float printer_height);