#include "ETC.h"
#include "okapi/api.hpp"
using namespace okapi;


#include "main.h"


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
    // Logger::setDefaultLogger(
    //     std::make_shared<Logger>(
    //         TimeUtilFactory::createDefault().getTimer(),
    //         "/ser/sout",
    //         Logger::LogLevel::warn
    //     )
    // );
    // Open_valve();

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


// pros::ADIEncoder left ('A', 'B', true);
// pros:ADIEncoder right ('C', 'D');


void autonomous(){
    std::shared_ptr<okapi::OdomChassisController> drive =
        ChassisControllerBuilder()
            .withMotors({-1,-2},{4,6})
            // Green gearset, 4 in wheel diam, 11.5 in wheel track
        .withDimensions({AbstractMotor::gearset::green, (84.0 / 60.0)},{{4_in, 12_in}, imev5GreenTPR})
	// 	.withGains(
    //     {0.001, 0, 0.0001}, // distance controller gains
    //     {0.001, 0, 0.0001}, // turn controller gains
    //     {0.001, 0, 0.0001}  // angle controller gains (helps drive straight)
    // )
        .withSensors(
            ADIEncoder{'A', 'B'}, 
            ADIEncoder{'C', 'D'})
        .withOdometry({{3.25_in, 12_in}, quadEncoderTPR}, StateMode::FRAME_TRANSFORMATION)
        // .withLogger()
        // .withLogger(
        // std::make_shared<Logger>(
        //     TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
        //     "/ser/sout", // Output to the PROS terminal
        //     Logger::LogLevel::debug // Most verbose log level
        // )
    // )
        .buildOdometry();
        // drive->setMaxVelocity(100);

        // drive->moveDistance(1.9_m);
        // drive->waitUntilSettled();
        // Raise_Claw();
        // pros::delay(1000);
        // drive->moveDistance(-1.75_m);
        drive->setState({0_in, 0_in, 0_deg});
// pros::lcd::print("%d", Encoder.get());
        pros::delay(1000);
        // drive->driveToPoint({2_ft, 0_ft});


        // drive->turnToAngle(90_deg);
// pros::lcd::print("%d", Encoder.get());
        // printf(drive->getState().str().c_str());
// return;
//         pros::delay(1000);
//         drive->turnToAngle(180_deg);
//         // printf(drive->getState().str().c_str());
// // pros::lcd::print("%d", Encoder.get());
//         pros::delay(1000);

//         drive->turnToAngle(270_deg);
//         // pros::lcd::print("%d", Encoder.get());
//         // printf(drive->getState().str().c_str());


//         pros::delay(1000);

//         drive->turnToAngle(0_deg);
//         // pros::lcd::print("%d", Encoder.get());
//         // printf(drive->getState().str().c_str());







    //    drive -> turnToPoint({10_ft, 0_ft});
    //    drive -> turnToPoint({10_ft, 10_ft});
    //    drive -> turnToPoint({0_ft, 10_ft});
    //    drive -> turnToPoint({3_ft, 10_ft});
       
        drive->driveToPoint({2_ft, 0_ft});
        pros::delay(1000);
        printf( drive->getState().str().c_str());
        std::cout << "step 1 \n";
        drive->driveToPoint({2_ft, 2_ft});
        pros::delay(1000);
        printf( drive->getState().str().c_str());

        std::cout << "step 2 \n";
        drive->driveToPoint({0_ft, 2_ft});
        pros::delay(1000);
        printf( drive->getState().str().c_str());

        
        std::cout << "step 3 \n";
        drive->driveToPoint({0_ft, 0_ft});
        pros::delay(1000);
        printf( drive->getState().str().c_str());

        
        std::cout << "step 4 \n";
        drive->setState({0_in, 0_in, 0_deg});
        printf( drive->getState().str().c_str());



        return; 
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
    // ADIEncoder left ('A','B',true);
    // ADIEncoder right ('C','D');

    // Chassis Controller - lets us drive the robot around with open- or closed-loop control
    std::shared_ptr<okapi::ChassisController> opdrive =
        ChassisControllerBuilder()
            .withMotors({-1,-2},{4,6})
            // Green gearset, 4 in wheel diam, 11.5 in wheel track
        .withDimensions({AbstractMotor::gearset::green, (84.0 / 36.0)},{{4_in, 12_in}, imev5GreenTPR})
		// .withSensors(
        // ADIEncoder{'A', 'B', true}, // left encoder in ADI ports A & B
        // ADIEncoder{'C', 'D'})  // right encoder in ADI ports C & D (reversed)
 // build an odometry chassis
        .build();


    // Joystick to read analog values for tank or arcade control
    // Master controller by default
    Controller controller;
	// Button to run our sample autonomous routine
    ControllerButton runAutoButton1(ControllerDigital::R1);
    ControllerButton runAutoButton2(ControllerDigital::R2);


    

    while (true) {
        // std::cout << drive.
        // Arcade drive with the left stick
        opdrive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
                                  controller.getAnalog(ControllerAnalog::leftX));
        // printf( to_string(drive->getModel()->getSensorVals()));
        // printf(left.get());
        // printf("%f", left.get());
        // printf(",   %f", right.get());
        // printf("\n");



        intake_control(-1);
		sol_control(0);
		lift_control(0);
		if (runAutoButton1.changedToPressed() && runAutoButton2.changedToPressed() == true) {
         autonomous();
		}

		// print_stuff();
        // Wait and give up the time we don't need to other tasks.
        // Additionally, joystick values, motor telemetry, etc. all updates every 10 ms.
        pros::delay(10);
    }
}