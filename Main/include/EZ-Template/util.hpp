/*
This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once
#include "api.h"

void print_ez_template();

extern pros::Motor l_motor;
extern pros::Motor r_motor;

void chassis_motor_init();

void set_left_chassis(int left);
void set_right_chassis(int right);
void set_tank(int input_l, int input_r);
void set_drive_brake(pros::motor_brake_mode_e_t input);

void reset_drive_sensor();

extern pros::ADIEncoder left_encoder;
extern pros::ADIEncoder right_encoder;

extern int left_sensor();
extern int right_sensor();




int sgn(int input);
float clip_num(float input, float max, float min);

extern double pi;
