/*
This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "main.h"
#include <string>

const float TICK_PER_REV  = (50*(3600/CART_RPM)) * RATIO; // with no cart, the encoder reads 50 counts per rotation
const float CIRCUMFERENCE = WHEEL_DIA*pi;
const float TICK_PER_INCH = (TICK_PER_REV/CIRCUMFERENCE);

const float W2W_dis = 10;

// double cur_loc[3] = {0,0,0};
// double delta_loc[3] = {0,0,0};
// double des_loc[3] = {0,0,0};
double des_dist = 0;
double delta_enc[2] = {0,0};
double prev_enc[2] = {0,0};
int motor_power = 0;
double dist_to = 0;
double intens = 7.5;
double offs = 10;

void track(void){
  delta_enc[0] = prev_enc[0];
  delta_enc[1] = prev_enc[1];
  delta_enc[0] = (left_encoder.get_value() - prev_enc[0])*TICK_PER_INCH;
  delta_enc[1] = (right_encoder.get_value() - prev_enc[1])*TICK_PER_INCH;
}

void control_loop(void){
  dist_to = des_dist - ((delta_enc[0]+delta_enc[1])/2);
  motor_power = 100/(pow((1+2.71282), (-1*intens*(dist_to - offs))));
}

void auton_drive(double dist){
  des_dist = dist;
  track();
  control_loop();
  if(motor_power < 10){motor_power = 0;}
  set_left_chassis(127*(motor_power/100));
  set_right_chassis(127*(motor_power/100));
  pros::delay(20);
  if(des_dist < 3){return;}
}

void turn(int degree, int direction){
  des_dist = degree;
  track();
  control_loop();
  set_left_chassis(direction*127*(motor_power/100));
  set_right_chassis(direction*127*(motor_power/100));
}