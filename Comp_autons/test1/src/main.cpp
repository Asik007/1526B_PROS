#include "ETC.h"
#include "okapi/api.hpp"
#include <iostream>
#include <string>
#include "main.h"

using namespace okapi;

const std::string autos_name[12] = {

"__test_auton__",
"_tri red str__",
"_tri red mid__",
"_tri red mid2_",
"_lef red mid__",
"_lef red str__",
"__risky 100___",
"_risky skils__",
"_skills jacob_",
"__test lift__",
"____NOTHING___",
"_risk tri mid_"
};




/**
 * Autonomous selector using LLEMU.
 *
 * When this function is called, display the current selected auton to the brain.
 * When is_auton is true, the autonomous mode will run.  Otherwise, it will only
 * print to brain.
 */
const int num_of_pages = 12; // Number of pages
int current_page = 0;

void
auto_select(bool is_auton) {
  Controller controller;

  for (int i=0; i<7; i++){
    pros::lcd::clear_line(i);
  }

  pros::lcd::set_text(0, "Autonomous "+std::to_string(current_page+1));

  switch (current_page) {
    case 0:
      pros::lcd::set_text(1, autos_name[0]);
      controller.setText(0,0,autos_name[0]);
      
      if (is_auton) test_auton();
      break;
    case 1: // Auto 2
      pros::lcd::set_text(1, autos_name[1]);
      controller.setText(0,0,autos_name[1]);
      
      if (is_auton) auto_1();
      break;
    case 2: // Auto 3
      pros::lcd::set_text(1, autos_name[2]);
      controller.setText(0,0,autos_name[2]);
      if (is_auton) auto_2();
      break;
    case 3: // Auto 4
      pros::lcd::set_text(1, autos_name[3]);
      controller.setText(0,0,autos_name[3]);

      if (is_auton) auto_3();
      break;
    case 4: // Auto 5
      pros::lcd::set_text(1, autos_name[4]);
      controller.setText(0,0,autos_name[4]);

      if (is_auton) auto_4();
      break;
    case 5: // Auto 6
      pros::lcd::set_text(1, autos_name[5]);
      controller.setText(0,0,autos_name[5]);

      if (is_auton) auto_5();
      break;
    case 6: // Auto 6
      pros::lcd::set_text(1, autos_name[6]);
      controller.setText(0,0,autos_name[6]);

      if (is_auton) auto_6();
      break;
    case 7: // Auto 6
      pros::lcd::set_text(1, autos_name[7]);
      controller.setText(0,0,autos_name[7]);

      if (is_auton) auto_7();
      break;
      case 8: // Auto 6
      pros::lcd::set_text(1, autos_name[8]);
      controller.setText(0,0,autos_name[8]);

      if (is_auton) auto_8();
      break;
      case 9: // Auto 6
      pros::lcd::set_text(1, autos_name[9]);
      controller.setText(0,0,autos_name[9]);

      if (is_auton) auto_9();
      break;
      case 10: // Auto 6
      pros::lcd::set_text(1, autos_name[10]);
      controller.setText(0,0,autos_name[10]);

      if (is_auton) auto_10();
      break;
      case 11: // Auto 6
      pros::lcd::set_text(1, autos_name[11]);
      controller.setText(0,0,autos_name[11]);

      if (is_auton) auto_11();
      break;
      
    default:
      break;
  }
}

// Page up/down
void
page_up() {
  if(current_page==num_of_pages-1)
    current_page=0;
  else
    current_page++;
  auto_select(false);
}
void
page_down() {
  if(current_page==0)
    current_page=num_of_pages-1;
  else
    current_page--;
  auto_select(false);
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void
initialize() {
  Controller controller;
//   print_ez_template();
  // pros::delay(500);

//   disable_all_tasks();

  pros::lcd::initialize();
  auto_select(false);
  pros::lcd::register_btn0_cb(page_down);
  pros::lcd::register_btn2_cb(page_up);
  Lower_Claw();
  Lower_Back();
  Left_lift.tare_position();
  Right_lift.tare_position();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void
disabled() {
//   disable_all_tasks();
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void
competition_initialize() {
  // Raise_Claw();
//   disable_all_tasks();
}

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
void
autonomous() {
  auto_select(true);
  pros::lcd::set_text(6, "POG");
}
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
  Controller controller;

  // std::shared_ptr<okapi::OdomChassisController> opdrive =
  //       ChassisControllerBuilder()
  //           .withMotors({-1,-2},{4,6})
  //           // Green gearset, 4 in wheel diam, 11.5 in wheel track
  //       .withDimensions({AbstractMotor::gearset::green, (84.0 / 60.0)},{{4_in, 12_in}, imev5GreenTPR})
	// // 	.withGains(
  //   //     {0.001, 0, 0.0001}, // distance controller gains
  //   //     {0.001, 0, 0.0001}, // turn controller gains
  //   //     {0.001, 0, 0.0001}  // angle controller gains (helps drive straight)
  //   // )
  //       .withSensors(
  //           ADIEncoder{'A', 'B'}, 
  //           ADIEncoder{'C', 'D'})
  //       .withOdometry({{3.25_in, 12_in}, quadEncoderTPR}, StateMode::FRAME_TRANSFORMATION)
  //       // .withLogger()
  //       // .withLogger(
  //       // std::make_shared<Logger>(
  //       //     TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
  //       //     "/ser/sout", // Output to the PROS terminal
  //       //     Logger::LogLevel::debug // Most verbose log level
  //       // )
  //   // )
  //       .buildOdometry();
//     // ADIEncoder left ('A','B',true);
//     // ADIEncoder right ('C','D');
      // okpai::Motor left1 (4);
      // okpai::Motor left2 (6);
okapi::MotorGroup right_mtr({4,6});
okapi::MotorGroup left_mtr({-1,-2});
// left_mtr.SetMaxC
    // Chassis Controller - lets us drive the robot around with open- or closed-loop control
    std::shared_ptr<okapi::ChassisController> opdrive =
        ChassisControllerBuilder()
            .withMotors(left_mtr, right_mtr)
            // Green gearset, 4 in wheel diam, 11.5 in wheel track
        .withDimensions({AbstractMotor::gearset::green, (84.0 / 36.0)},{{4_in, 12_in}, imev5GreenTPR})
		// .withSensors(
        // ADIEncoder{'A', 'B', true}, // left encoder in ADI ports A & B
        // ADIEncoder{'C', 'D'})  // right encoder in ADI ports C & D (reversed)
        .build();


    // Joystick to read analog values for tank or arcade control
    // Master controller by default

	// Button to run our sample autonomous routine
    ControllerButton runAutoButton1(ControllerDigital::R1);
    ControllerButton runAutoButton2(ControllerDigital::R2);
    controller.clearLine(2);


           controller.clear();


    
  // opdrive->setState({0_in, 0_in, 0_deg});


pros::ADIDigitalOut Claw_sol2 (4);

    while (true) {
      


      // std::cout << right_mtr.getTemperature()<< right_mtr.isOverCurrent()<<right_mtr.isOverTemp()<<right_mtr.getCurrentLimit()<<"\n";

      // opdrive->getModel()->driveVector(20,20);
        // std::cout << drive.
        // Arcade drive with the left stick
        opdrive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
                                  controller.getAnalog(ControllerAnalog::leftX));
        // printf( to_string(drive->getModel()->getSensorVals()));
        // printf(left.get());
        // printf("%f", left.get());
        // printf(",   %f", right.get());
        // printf("\n");
  //       std::string auton_str;

  //       if(runAutoButton1.changedToPressed() == true ){ current_page++;}
  //       if(current_page >= 7){current_page = 0;}
  //       switch (current_page) {
  //       case 1: // Auto 2
  //       auton_str = std::to_string(current_page) + "  " + autos_name[1];
  //       case 2: // Auto 3
  //       auton_str = std::to_string(current_page) + "  " + autos_name[2];  
  //       case 3: // Auto 4
  //       auton_str = std::to_string(current_page) + "  " + autos_name[3];  
  //       case 4: // Auto 5
  //       auton_str = std::to_string(current_page) + "  " + autos_name[4]; 
  //       case 5: // Auto 6
  //       auton_str = std::to_string(current_page) + "  " + autos_name[5];  

  //       default:
  //         break;
  // }
  //       // controller.print(0,0, current_page);

  //       controller.setText(0,0,autos_name[1]


        // if(runAutoButton1.changedToPressed() == true ){ 
  //         if(pros::usd::is_installed())
  //         {	FILE* usd_file_write = fopen("/usd/rerun.txt", "w");
	// fprintf(usd_file_write, opdrive->getState());
	// fclose(usd_file_write);}
// auto state = opdrive->getState();
//     std::cout << state.str() << std::endl;
//     pros::delay(50);
        // }




        intake_control(-1);
		// sol2_control();
		sol_control();

		lift_control(0);
		if (runAutoButton1.changedToPressed() == true) {
         current_page++;
           controller.clear();
           controller.clearLine(0);
		}
    if(current_page > num_of_pages){current_page = 0;}
    auto_select(false);
    // controller.setText(0,0,autos_name[1]);

    // std::cout << auton_str <<"\n";

		// print_stuff();
        // Wait and give up the time we don't need to other tasks.
        // Additionally, joystick values, motor telemetry, etc. all updates every 10 ms.
        // controller.setText(0,0,autos_name[1]ng(current_page));
        pros::delay(20);
    }
}