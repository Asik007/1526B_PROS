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
double des_dist_L = 0;
double des_dist_R = 0;
double delta_enc[2] = {0,0};
double prev_enc[2] = {0,0};
int motor_power = 0;
int motor_power_L = 0;
int motor_power_R = 0;

double dist_to = 0;
int dist_to_L = 0;
int dist_to_R = 0;
double intens = 7.5;
double intens_T = 7.5;

double offs = 10;
double offs_T = 10;

void track(void){
  delta_enc[0] = prev_enc[0];
  delta_enc[1] = prev_enc[1];
  delta_enc[0] = (left_encoder.get_value() - prev_enc[0])*TICK_PER_INCH;
  delta_enc[1] = (right_encoder.get_value() - prev_enc[1])*TICK_PER_INCH;
}

void control_loop_drive(void){
  dist_to = des_dist - ((delta_enc[0]+delta_enc[1])/2);
  motor_power = 100/(pow((1+2.71282), (-1*intens*(dist_to - offs))));
}

float turn_func(double dist_to_end){
return (100/(pow((1+2.71282), (-1*intens_T*(dist_to - offs_T)))));
}

void control_loop_turn_L(void){
  dist_to_L = des_dist_L - (delta_enc[0]);
  motor_power_L = turn_func(dist_to_L);
}

void control_loop_turn_R(void){
  dist_to_R = des_dist_R - (delta_enc[1]);
  motor_power_R = turn_func(dist_to_L);
}


void auton_drive(double dist){
  while(motor_power > 10 || motor_power == 0){
  des_dist = dist;
  track();
  control_loop_drive();
  set_left_chassis(127*(motor_power/100));
  set_right_chassis(127*(motor_power/100));
  pros::delay(20);
  if(des_dist < 3){return;}
}
}

//-1 = left
void auton_turn(int degree, int direction){
  dist_to_L = ((direction*degree)/360)*pi*W2W_dis;
  dist_to_R = ((-1*direction*degree)/360)*pi*W2W_dis;
 while(dist_to_L > .5 || dist_to_R > .5){
  dist_to_L = ((direction*degree)/360)*pi*W2W_dis;
  dist_to_R = ((-1*direction*degree)/360)*pi*W2W_dis;
  track();
  control_loop_turn_L();
  control_loop_turn_R();
  set_left_chassis(127*(motor_power_L/100));
  set_right_chassis(127*(motor_power_R/100));
}
}