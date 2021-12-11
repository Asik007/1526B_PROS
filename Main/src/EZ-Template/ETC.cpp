#include "main.h"


int state = 0;
bool Lift_rvr = true;
float intake_CE = .5;


// const char* str_true = "true";

std::string str_true = "true";
std::string str_false = "false";


std::string back_state_str;  
std::string claw_state_str; 
std::string lift_state_str;

pros::Motor Left_lift (5, Lift_rvr);
pros::Motor Right_lift (6, !Lift_rvr);
bool lift_state;
// bool prev_lift_state;
void Raise_lift(){
    Left_lift.move_voltage(10000);
    Right_lift.move_voltage(10000);
    lift_state = true;
}
void Lower_lift(){
    Left_lift.move_voltage(-10000);
    Right_lift.move_voltage(-10000);
    lift_state = false;
}



pros::ADIAnalogOut Claw_sol ('F');
pros::ADIAnalogOut Back_sol ('G');
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


void intake_on(){
    intake.move(127*intake_CE);
}

void intake_rvr(){
    intake.move(-127*intake_CE);
}
void intake_stop(){
    intake.move(0);
}



void lift_control(){
    
    if(master.get_digital(DIGITAL_X) || master.get_digital(DIGITAL_Y) == true){
    if(master.get_digital(DIGITAL_X) == true){
      // pros::lcd::clear();
      // pros::lcd::print("POGGERS 1");
      Raise_lift();
    }
    if(master.get_digital(DIGITAL_Y)== true){
      Lower_lift();
    }
    }
    else{
    Left_lift.move(0);
    Right_lift.move(0);
    }


}



void sol_control(){
    if(master.get_digital(DIGITAL_A)){
      Raise_Claw();
    }
    if(master.get_digital(DIGITAL_B)){
      Lower_Claw();
    }
    if(master.get_digital(DIGITAL_L1)){
      Raise_Back();
    }
    if(master.get_digital(DIGITAL_L2)){
      Lower_Back();
    }
    
}

void intake_control(){

    if(master.get_digital_new_press(DIGITAL_UP)==true){
    pros::lcd::clear_line(4);
    // pros::lcd::print(4,"i was pressed");
    ++state;
    }

    if(master.get_digital(DIGITAL_LEFT)==true){state = 1;}
    if(master.get_digital(DIGITAL_RIGHT)==true){state = 2;}
    if(master.get_digital(DIGITAL_DOWN)==true){state = 0;}
    if(state == 0){intake_stop(); }
    if(state == 1){intake_on();}
    if(state == 2){intake_rvr();}
    if(state >= 3){state = 0;}
    // std::string s = std::to_string(state);
    // const *pchar = s.c_str();  //use char const* as target type
}

void print_stuff(){
    
    
    if(back_state == true){back_state_str = str_true;}
    if(back_state == false){back_state_str = str_false;}
    if(claw_state == true){claw_state_str = str_true;}
    if(claw_state == false){claw_state_str = str_false;}
    if(lift_state == true){lift_state_str = str_true;}
    if(lift_state == false){lift_state_str = str_false;}
    std::string s = std::to_string(state);


    pros::lcd::clear_line(2);
    pros::lcd::clear_line(3);
    pros::lcd::clear_line(4);
    pros::lcd::clear_line(3);


    pros::lcd::print(2,back_state_str.c_str());
    pros::lcd::print(3,claw_state_str.c_str());
    pros::lcd::print(4, s.c_str());
    pros::lcd::print(5,lift_state_str.c_str());

}
