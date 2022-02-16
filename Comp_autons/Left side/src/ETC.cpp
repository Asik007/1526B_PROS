#include "main.h"

#define inv_right true
#define inv_left true
#define ODO_radii 5

#define Left_lift_port 19
#define Right_lift_port 18

#define intake_port 8

#define claw_sol 4
#define back_sol 5
#define open_val 6





int state = 0;
bool Lift_rvr = true;
float intake_CE = 1;



// const char* str_true = "true";

std::string str_true = "true";
std::string str_false = "false";


std::string back_state_str;  
std::string claw_state_str; 
std::string lift_state_str;

pros::Motor Left_lift (Left_lift_port, Lift_rvr);
pros::Motor Right_lift (Right_lift_port, !Lift_rvr);
bool lift_state;
// bool prev_lift_state;


void Raise_lift(int pog){
    Left_lift.move_voltage(12000*pog);
    Right_lift.move_voltage(12000*pog);
    lift_state = true;
    
    return;
}
void Lower_lift(int pog){
    Left_lift.move_voltage(-12000*pog);
    Right_lift.move_voltage(-12000*pog);
    lift_state = false;
    return;
}


pros::ADIDigitalOut Claw_sol (claw_sol);
pros::ADIDigitalOut Back_sol (back_sol);
pros::ADIDigitalOut Main_sol (open_val);

// pros::ADIDigitalOut POGL (5);

bool back_state;
bool claw_state;
// bool prev_back_state;
// bool prev_claw_state;


void Open_valve(){
  Main_sol.set_value(true);
}

void Close_valve(){
  Main_sol.set_value(false);
}

void Raise_Back(){
    // prev_back_state = back_state;
    Back_sol.set_value(true);
    // POGL.set_value(true);
    // Back_sol.set_value(4095);

    back_state = true;
}

void Lower_Back(){
    // prev_back_state = back_state;    
    Back_sol.set_value(false);
    // Back_sol.set_value(0);
    // POGL.set_value(false);

    back_state = false;
}

void Raise_Claw(){
    // prev_claw_state = claw_state;
    Claw_sol.set_value(false);
    claw_state = true;
}

void Lower_Claw(){
    // prev_claw_state = claw_state;
    Claw_sol.set_value(true);
    claw_state = false;
}


pros::Motor intake (intake_port);


void intake_on(){
    intake.move_voltage(12000*intake_CE);
    std::cout << "intake:" << intake.get_voltage();

}

void intake_rvr(){
    intake.move_voltage(-12000*intake_CE);
    std::cout << "intake:" << intake.get_voltage();

   
}
void intake_stop(){
    intake.move_voltage(0);
    std::cout << "intake:" << intake.get_voltage();

}


ControllerButton btnY(ControllerDigital::Y);
ControllerButton btnX(ControllerDigital::X);
void lift_control(int lift_ctrl){
    Left_lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    Right_lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    

    if( lift_ctrl == 0){}
    if(lift_ctrl == 1){Raise_lift(.5); pros::delay(300); return;}
    if(lift_ctrl == 2){Lower_lift(.5); pros::delay(500); return;}

    std::string lift_debug = std::to_string(Left_lift.get_actual_velocity());pros::lcd::print(2,lift_debug.c_str());
    if(btnY.isPressed() || btnX.isPressed() == true){    
    if(btnX.isPressed() == true){
      // pros::lcd::clear();
      // pros::lcd::print("POGGERS 1");
      Raise_lift(1);
      

      

    
    }
    if(btnY.isPressed()== true){
      Lower_lift(1);
    }
    }
    else{
    Left_lift.move_voltage(0);
    Right_lift.move_voltage(0);
    }
    // Lower_lift(0);

    // Left_lift.move_voltage(10000*0);
    // Right_lift.move_voltage(10000*0);


    // Left_lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    // Right_lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    

return;
}
ControllerButton btnA(ControllerDigital::A);
ControllerButton btnB(ControllerDigital::B);
ControllerButton btnL1(ControllerDigital::L1);
ControllerButton btnL2(ControllerDigital::L2);



void sol_control(int sol_ctrl){
    if(sol_ctrl == 0){}
    if(sol_ctrl == 1){Raise_Claw();return;}
    if(sol_ctrl == 2){Lower_Claw(); return;}
    if(sol_ctrl == 3){Raise_Back(); return;}
    if(sol_ctrl == 4){Lower_Back(); return;}
    

    if(btnA.isPressed()){
      Raise_Claw();
    }
    if(btnB.isPressed()){
      Lower_Claw();
    }
    if(btnL1.isPressed()){
      Raise_Back();
    }
    if(btnL2.isPressed()){
      Lower_Back();
    }
    
}
ControllerButton btnUP(ControllerDigital::up);
ControllerButton btnL(ControllerDigital::left);
ControllerButton btnR(ControllerDigital::right);
ControllerButton btnDWN(ControllerDigital::down);
int makeshiftwait = 0;
void intake_control(int state_ctrl){
    intake.set_brake_mode(MOTOR_BRAKE_COAST);
    // std::cout << "Motor Current Draw: " << Right_lift.get_current_draw();
          // std::cout << "Motor Current Draw: " << intake.get_efficiency() << "\n";
      // pros::delay(1000);
      
    if (state_ctrl <= 0){}
    else{
      state = abs(state_ctrl);
    }
    if(btnUP.changedToPressed()==true){
    pros::lcd::clear_line(4);
    // pros::lcd::print(4,"i was pressed");
    ++state;
    }

    if(btnL.isPressed()==true){state = 2;}
    if(btnR.isPressed()==true){state = 1;}
    if(btnDWN.isPressed()==true){state = 0;}
    if(state == 0){intake_stop(); }
    if(state == 2){intake_on();}
    if(state == 1){intake_rvr();}
    if(intake.get_efficiency() < 10 && state > 0){
  state = 2;
      // intake.move_relative(720, 200); 
    // std::cout << "plz work \n";
          // std::cout << "Motor Current Draw: " << intake.get_efficiency() << "\n";
    }
    //  pros::delay(50);}
    if(state >= 3){state = 0;}
    // std::string s = std::to_string(state);
    // const *pchar = s.c_str();  //use char const* as target type

}

// void print_stuff(){
    
    
//     if(back_state == true){back_state_str = str_true;}
//     if(back_state == false){back_state_str = str_false;}
//     if(claw_state == true){claw_state_str = str_true;}
//     if(claw_state == false){claw_state_str = str_false;}
//     if(lift_state == true){lift_state_str = str_true;}
//     if(lift_state == false){lift_state_str = str_false;}
//     std::string s = std::to_string(state);
//     // std::string lift_mtr = std::to_string(motor_power);



//     pros::lcd::clear_line(2);
//     pros::lcd::clear_line(3);
//     pros::lcd::clear_line(4);
//     pros::lcd::clear_line(3);


//     // pros::lcd::print(2,lift_mtr.c_str());
//     pros::lcd::print(3,claw_state_str.c_str());
//     pros::lcd::print(4, s.c_str());
//     pros::lcd::print(5,lift_state_str.c_str());

// }
