/*
This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "main.h"


float LEFT_CURVE_SCALE  = 0;
float RIGHT_CURVE_SCALE = 0;

pros::controller_analog_e_t current_l_stick = LEFT_JOYSTICK;
pros::controller_analog_e_t current_r_stick = RIGHT_JOYSTICK;




// Hold button constants
const int WAIT = 500; // Time button needs to be held before increasing
const int INCREASE_INTERVAL = 50; // After buttin is held for WAIT, curve scaler will increase every this amount of time

// Struct for pointer values
typedef struct {
  bool lock;
  int init_timer;
  int increase = INCREASE_INTERVAL;
} button_;

// Button logic
// When tapped, run increase/decrease function once
// When held, run increase/decrease function every INCREASE_INTERCAL time
void
button_press(button_ *input_name, int button, void (*f)()) {
  if (button && !input_name->lock) {
    f();
    input_name->lock = true;
  }
  else if (button && input_name->lock) {
    input_name->init_timer+=DELAY_TIME;
    if (input_name->init_timer > WAIT) {
      input_name->increase+=DELAY_TIME;
      if (input_name->increase > INCREASE_INTERVAL) {
        f();
        input_name->increase = 0;
      }
    }
  }
  else if (!button) {
    input_name->lock = false;
    input_name->init_timer = 0;
  }
}

///
// Joystick Control
///

int x = 0;


void
chassis_joystick_control() {
  // Arcade tank toggle

  // Toggle for controller curve
  // if (!DISBALE_CONTROLLER)
  //   modify_curve_with_controller();

  // Toggle for arcade / tank
  int left_stick, right_stick;
  right_stick  = JS_turn*master.get_analog(current_r_stick);
  left_stick = JS_str*master.get_analog(current_l_stick);

  // Threshold if joysticks don't come back to perfect 0
  if (abs(left_stick)>THRESH || abs(right_stick)>THRESH) {
      set_tank(left_stick+right_stick, left_stick-right_stick);
    reset_drive_sensor();
  }
  // When joys are released, run active brake (P) on drive
  else {
    set_tank((0-left_sensor())*ACTIVE_BRAKE_KP, (0-right_sensor())*ACTIVE_BRAKE_KP);
  }
}
