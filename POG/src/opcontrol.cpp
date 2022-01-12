#include "main.h"

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

#include <string>

const float TICK_PER_REV  = (50*(3600/50)) * 1.666; // with no cart, the encoder reads 50 counts per rotation
const float CIRCUMFERENCE = 4.125*3.14;
const float TICK_PER_INCH = (TICK_PER_REV/CIRCUMFERENCE);

const float W2W_dis = 10;

pros::ADIEncoder left_encoder(1,2,true);
pros::ADIEncoder right_encoder(3,4,false);

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor left_mtr(1);
pros::Motor left_mtr_2(2);
pros::Motor right_mtr_2(4);
pros::Motor right_mtr(5);
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

void drive(double dist){
  des_dist = dist;
  track();
  control_loop();
  left_mtr, left_mtr_2 = (127*(motor_power/100));
  right_mtr, right_mtr_2 = (127*(motor_power/100));
}

void turn(int degree, int direction){
  des_dist = degree;
  track();
  control_loop();
  left_mtr, left_mtr_2 = (127*(motor_power/100));
  right_mtr, right_mtr_2 = (127*(motor_power/100));
  }

void opcontrol() {

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		left_mtr = left;
		left_mtr_2 = left;
		right_mtr = right;
		right_mtr_2 = right;

		pros::delay(20);
	}
}
