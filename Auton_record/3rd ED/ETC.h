#pragma once

//true state = Lift or claw is open

void Raise_lift();
void Lower_lift();
extern bool lift_state;
// extern bool prev_lift_state;
void Raise_Back();
void Lower_Back();
extern bool back_state;

void Open_valve();
void Close_valve();

// extern bool prev_back_state;
void Raise_Claw();
void Lower_Claw();
extern bool claw_state;
// extern bool prev_claw_state;
void intake_on();
void intake_rvr();
void intake_stop();
extern int state;
void intake_control(int);
void sol_control(int);
void lift_control(int);
void print_stuff();



