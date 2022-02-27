#include "main.h"

#define flipDB true
const float powerCE = .8;
const float turnCE = .8;

float WheelSize = 4.25;
float Ratio = 1;
float W2W_dist = 6; //realy the radius
float TPR_raw = 360;


double pi = 2*acos(0.0);
float circum = WheelSize * pi;
float TPR = TPR_raw * Ratio;

void Disttotick(){
    TargetTicksLeftT = (dist / circum) * TPR;
    TargetTicksRightT = (dist / circum) * TPR;
    return;
}


void strDrive(int dist){


	
}

pros::Controller master(pros::E_CONTROLLER_MASTER);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */


void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
	// pros::lcd::register_btn1_cb(on_center_button);
	Lower_Claw();
	Lower_Back();
	ResetEnc();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */




void opcontrol() {

	pros::Task tracking (OdomMath);


  
	okapi::MotorGroup left_mtrs({6,4});
	okapi::MotorGroup right_mtrs ({-1, -2});



	// while (true){
		// OdomMath();
	// }


	while (true) {
		int power = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);

		float left_pwr = (((powerCE*power) - (turn*turnCE))/127);
		float right_pwr = (((powerCE*power) + (turn*turnCE))/127);



		left_mtrs.moveVoltage((left_pwr)*12000);
		right_mtrs.moveVoltage((right_pwr)*12000);

		intake_control();
		lift_control();
		sol_control();

		// std::cout << Coords[0] << "	" << Coords[1] << "	" << Coords[2] << "\n";



		pros::delay(70);
	}
}
