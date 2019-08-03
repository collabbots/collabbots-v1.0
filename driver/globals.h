#ifndef globals_h
#define globals_h

#include <Adafruit_PWMServoDriver.h>

/********************
   GLOBAL VARIABLES
 ********************/

// servo drivers
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
uint8_t servonum = 1;

// minimum/maximum pulse signals
#define MINIMUM_PULSE 90
#define MAXIMUM_PULSE 540

// two arms
#define ARM1 1
#define ARM2 2

// finite system states to implement robot interface as an FSM (Finite State Machine) 
enum system_state {
  REQ_INSTRCT,      // request for instruction
  READ_INSTRCT,     // read instruction
  PARSE_INSTRCT,    // parse instruction
  EXECUTE_INSTRCT,  // execute instruction
  ARM_1_LIMIT_INTRPT, //
  ARM_2_LIMIT_INTRPT, //
  MANUAL_CTRL_INTRPT, //
  ARM_SWITCH_INTRPT   //
};

system_state sys_state = REQ_INSTRCT;

// max/min angles for the different motors
#define MAX_TOP_ANGLE 135
#define MAX_BOTTOM_ANGLE 180
#define MAX_BASE_ANGLE 180
#define MIN_TOP_ANGLE -135
#define MIN_BOTTOM_ANGLE 0
#define MIN_BASE_ANGLE 0

// servo controller (PCA9685) pins for arm motors
const int arm_1_base_pin = 0;
const int arm_1_bottom_pin = 1;
const int arm_1_top_pin = 2;
const int arm_1_claw_pin = 3;
const int arm_2_base_pin = 5;
const int arm_2_bottom_pin = 6;
const int arm_2_top_pin = 7;
const int arm_2_claw_pin = 8;

// interrupt pins from the arms to thr MKR1000
const int arm_1_bot_intrpt_1 = 0;
const int arm_1_bot_intrpt_2 = 1;
const int arm_1_top_intrpt_1 = 4;
const int arm_1_top_intrpt_2 = 5;
const int arm_2_bot_intrpt_1 = 6;
const int arm_2_bot_intrpt_2 = 7;
const int arm_2_top_intrpt_1 = 8;
const int arm_2_top_intrpt_2 = 9;

// current angular position
int arm_1_base_angle = 0;
int arm_1_bottom_angle = 0;
int arm_1_top_angle = 0;
int arm_2_base_angle = 0;
int arm_2_bottom_angle = 0;
int arm_2_top_angle = 0;

// speed delay for motors (higher = slower)
const int motor_speed_delay = 25;

#endif