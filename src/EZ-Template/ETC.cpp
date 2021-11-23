#include "main.h"

bool Lift_rvr = true;

pros::Motor Left_lift (5, Lift_rvr);
pros::Motor Right_lift (6, !Lift_rvr);
bool lift_state;
// bool prev_lift_state;
void Raise_lift(){
    print_ez_template();
}
void Lower_lift(){
    print_ez_template();
}



pros::ADIAnalogOut Claw_sol (11);
pros::ADIAnalogOut Back_sol (10);
bool back_state;
bool claw_state;
// bool prev_back_state;
// bool prev_claw_state;

void Raise_Back(){
    // prev_back_state = back_state;
    Back_sol.set_value(4095);
    back_state = true;
}

void Lower_Back(){
    // prev_back_state = back_state;    
    Back_sol.set_value(0);
    back_state = false;
}

void Raise_Claw(){
    // prev_claw_state = claw_state;
    Back_sol.set_value(0);
    claw_state = true;
}

void Lower_Claw(){
    // prev_claw_state = claw_state;
    Back_sol.set_value(4095);
    claw_state = false;
}


pros::Motor intake (7);
int intake_state;
int prev_intake_state;

void intake_on(){
    intake_state = prev_intake_state;
    intake.move(127);
    intake_state = 1;
}

void intake_rvr(){
    intake_state = prev_intake_state;
    intake.move(-127);
    intake_state = -1;
}
void intake_stop(){
    intake_state = prev_intake_state;
    intake.move(0);
    intake_state = 0;
}
