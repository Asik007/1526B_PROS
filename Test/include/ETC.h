#pragma once

#define Left_lift_port 19
#define Right_lift_port 20

#define intake_port 10

#define claw_sol 'F'
#define back_sol 'G'

//true state = Lift or claw is open

void Raise_lift();
void Lower_lift();
extern bool lift_state;
// extern bool prev_lift_state;
void Raise_Back();
void Lower_Back();
extern bool back_state;
// extern bool prev_back_state;
void Raise_Claw();
void Lower_Claw();
extern bool claw_state;
// extern bool prev_claw_state;
void intake_on();
void intake_rvr();
void intake_stop();
extern int state;
void intake_control();
void sol_control();
void lift_control();
void print_stuff();



