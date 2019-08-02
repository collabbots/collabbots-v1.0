#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

// TODO: arm 1/2 relax disconnects power from the arm. activate will switch it back on.
// TODO: add wifi data transfer of angles for visualization module to work off the system.
// TODO: add manual control code and construct FSM for the same.
// TODO: organize code into multiple files.

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


/********************
   HELPER FUNCTIONS
 ********************/

/**
   Sets the spacing
   @param spacing Specifies
   @param arm Specifies
*/
void setClawSpacing(double spacing, int arm)
{
  if (spacing > 5 || spacing < 0)
    return;
  int angle = -13.386 * spacing + 106.28;
  if (arm == 1)
    setAngle(arm_1_claw_pin, angle);
  else if (arm == 2)
    setAngle(arm_2_claw_pin, angle);
}

/**
   Sets the
   @param pin The pin
   @param angle
*/
void setAngle(int pin, int angle) 
{
  int adjustedAngle;
  if (pin == arm_1_claw_pin || pin == arm_2_claw_pin)
    adjustedAngle = map(angle, 0, 180, MINIMUM_PULSE, MAXIMUM_PULSE);
  else if (pin == arm_1_base_pin || pin == arm_2_base_pin)
    adjustedAngle = map(angle, 0, 180, 90, 400);
  else if (pin == arm_1_bottom_pin)
    adjustedAngle = map(angle, 180, 0, 90, 395);
  else if (pin == arm_2_bottom_pin)
    adjustedAngle = map(angle, 0, 180, 90, 395); 
  else if (pin == arm_1_top_pin || pin == arm_2_top_pin)
    adjustedAngle = map(angle, -135, 135, 90, 540);
  pwm.setPWM(pin, 0, adjustedAngle);

}

/**
   Summary
   @param angle Absolute angle to change to
   @param arm The arm that should be controlled
*/
void rotateBase(int angle, int arm)
{
  if (angle < MIN_BASE_ANGLE || angle > MAX_BASE_ANGLE)
    return;

  if (arm == 1) 
  {
    if (angle >= arm_1_base_angle) 
    {
      for (int i = arm_1_base_angle; i < angle; ++i) 
      {
        setAngle(arm_1_base_pin, i);
        delay(motor_speed_delay);
      }
    }
    else if (angle < arm_1_base_angle) 
    {
      for (int i = arm_1_base_angle; i > angle; i--) 
      {
        setAngle(arm_1_base_pin, i);
        delay(motor_speed_delay);
      }
    }
    arm_1_base_angle = angle;
  }

  else if (arm == 2) 
  {
    if (angle >= arm_2_base_angle) 
    {
      for (int i = arm_2_base_angle; i < angle; i++) 
      {
        setAngle(arm_2_base_pin, i);
        delay(motor_speed_delay);
      }
    }
    else if (angle < arm_2_base_angle) 
    {
      for (int i = arm_2_base_angle; i > angle; i--) 
      {
        setAngle(arm_2_base_pin, i);
        delay(motor_speed_delay);
      }
    }
    arm_2_base_angle = angle;
  }

}

/**
   Hi there
   @param angle
   @param arm
*/
void rotateBottom(int angle, int arm) 
{
  if (angle < MIN_BOTTOM_ANGLE || angle > MAX_BOTTOM_ANGLE)
    return;

  if (arm == 1) 
  {
    if (angle >= arm_1_bottom_angle) 
    {
      for (int i = arm_1_bottom_angle; i < angle; i++) 
      {
        setAngle(arm_1_bottom_pin, i);
        delay(motor_speed_delay);
      }
    }
    else if (angle < arm_1_bottom_angle) 
    {
      for (int i = arm_1_bottom_angle; i > angle; i--) 
      {
        setAngle(arm_1_bottom_pin, i);
        delay(motor_speed_delay);
      }
    }
    arm_1_bottom_angle = angle;
  }

  else if (arm == 2) 
  {
    if (angle >= arm_2_bottom_angle) 
    {
      for (int i = arm_2_bottom_angle; i < angle; i++) 
      {
        setAngle(arm_2_bottom_pin, i);
        delay(motor_speed_delay);
      }
    }
    else if (angle < arm_2_bottom_angle) 
    {
      for (int i = arm_2_bottom_angle; i > angle; i--) 
      {
        setAngle(arm_2_bottom_pin, i);
        delay(motor_speed_delay);
      }
    }
    arm_2_bottom_angle = angle;
  }

}

/**
   @param angle
   @para
*/
void rotateTop(int angle, int arm) 
{
  if (angle < MIN_TOP_ANGLE || angle > MAX_TOP_ANGLE)
    return;

  if (arm == 1) 
  {
    if (angle >= arm_1_top_angle) 
    {
      for (int i = arm_1_top_angle; i < angle; i++) 
      {
        setAngle(arm_1_top_pin, i);
        delay(motor_speed_delay);
      }
    }
    else if (angle < arm_1_top_angle) 
    {
      for (int i = arm_1_top_angle; i > angle; i--) 
      {
        setAngle(arm_1_top_pin, i);
        delay(motor_speed_delay);
      }
    }
    arm_1_top_angle = angle;
  }

  else if (arm == 2) 
  {
    if (angle >= arm_2_top_angle) 
    {
      for (int i = arm_2_top_angle; i < angle; i++) 
      {
        setAngle(arm_2_top_pin, i);
        delay(motor_speed_delay);
      }
    }
    else if (angle < arm_2_top_angle) 
    {
      for (int i = arm_2_top_angle; i > angle; i--) 
      {
        setAngle(arm_2_top_pin, i);
        delay(motor_speed_delay);
      }
    }
    arm_2_top_angle = angle;
  }

}

void arm1Interrupt() 
{
  sys_state = ARM_1_LIMIT_INTRPT;
}

void arm2Interrupt() 
{
  sys_state = ARM_2_LIMIT_INTRPT;
}

/******************
   MAIN EXECUTION
 ******************/

String input;
String armToChange;
String motorToChange;
int amountToChange;

void setup()
{
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

  // CONFIGURE INTERRUPTS
  pinMode(arm_1_bot_intrpt_1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(arm_1_bot_intrpt_1), arm1Interrupt, RISING);
  pinMode(arm_1_bot_intrpt_2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(arm_1_bot_intrpt_2), arm1Interrupt, RISING);
  pinMode(arm_1_top_intrpt_1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(arm_1_top_intrpt_1), arm1Interrupt, RISING);
  pinMode(arm_1_top_intrpt_2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(arm_1_top_intrpt_2), arm1Interrupt, RISING);
  pinMode(arm_2_bot_intrpt_1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(arm_2_bot_intrpt_1), arm2Interrupt, RISING);
  pinMode(arm_2_bot_intrpt_2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(arm_2_bot_intrpt_2), arm2Interrupt, RISING);
  pinMode(arm_2_top_intrpt_1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(arm_2_top_intrpt_1), arm2Interrupt, RISING);
  pinMode(arm_2_top_intrpt_2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(arm_2_top_intrpt_2), arm2Interrupt, RISING);


  // CONFIGURE STARTING POSITIONS
  pwm.begin();
  pwm.setPWMFreq(60); // analog servos run at ~60 Hz updates
  pwm.setPWM(arm_1_base_pin, 0, MINIMUM_PULSE);
  pwm.setPWM(arm_2_base_pin, 0, MINIMUM_PULSE);
  delay(500);
  pwm.setPWM(arm_1_bottom_pin, 0, 395);
  pwm.setPWM(arm_2_bottom_pin, 0, MINIMUM_PULSE);
  delay(500);
  pwm.setPWM(arm_1_top_pin, 0, 315);
  pwm.setPWM(arm_2_top_pin, 0, 315);
  pwm.setPWM(arm_1_claw_pin, 0, 160);
  pwm.setPWM(arm_2_claw_pin, 0, 160);
  delay(500); 
}

void loop()
{   
  // read input
  if (sys_state == REQ_INSTRCT)
  {
    Serial.println("Enter command in form: set arm1/arm2 base/bottom/top/claw angle/spacing");
    sys_state = READ_INSTRCT;
  }

  else if (sys_state == READ_INSTRCT) 
  {
    if (Serial.available() > 0) 
    {
      input = Serial.readStringUntil('\n');
      //go onto to next state
      sys_state = PARSE_INSTRCT;
    }

  }

  else if (sys_state == PARSE_INSTRCT) 
  {
    //find location of spaces
    int firstSpace = -1;
    int secondSpace = -1;
    int thirdSpace = -1;
    for (int i = 0; i < input.length(); i++) {
      if (input[i] == ' ' && firstSpace == -1)
        firstSpace = i;
      else if (input[i] == ' ' && secondSpace == -1)
        secondSpace = i;
      else if (input[i] == ' ' && thirdSpace == -1)
        thirdSpace = i;
    }

    if (firstSpace != -1 && secondSpace != -1 && thirdSpace != -1) 
    {
      //break the string apart at the spaces
      armToChange = input.substring(firstSpace + 1, secondSpace);
      motorToChange = input.substring(secondSpace + 1, thirdSpace);
      String amountToChangeString = input.substring(thirdSpace + 1, input.length());
      amountToChange = amountToChangeString.toInt();

      sys_state = EXECUTE_INSTRCT;
    }

    else 
    {
      Serial.println("Sorry, invalid command");
      sys_state = REQ_INSTRCT;
    }
  }

  else if (sys_state == EXECUTE_INSTRCT) 
  {
    Serial.print("Setting "); 
    Serial.print(armToChange); 
    Serial.print(" "); 
    Serial.print(motorToChange); 
    Serial.print(" to "); 
    Serial.println(amountToChange);

    if (armToChange == "arm1") 
    {
      if (motorToChange == "base")
        rotateBase(amountToChange, ARM1);

      if (motorToChange == "bottom")
        rotateBottom(amountToChange, ARM1);

      if (motorToChange == "top")
        rotateTop(amountToChange, ARM1);

      if (motorToChange == "claw")
        setClawSpacing(amountToChange, ARM1);
    }

    else if (armToChange == "arm2") 
    {
      if (motorToChange == "base")
        rotateBase(amountToChange, ARM2);

      if (motorToChange == "bottom")
        rotateBottom(amountToChange, ARM2);

      if (motorToChange == "top")
        rotateTop(amountToChange, ARM2);

      if (motorToChange == "claw")
        setClawSpacing(amountToChange, ARM2);

    }

    sys_state = REQ_INSTRCT;

  }

  else if (sys_state == ARM_1_LIMIT_INTRPT) 
  {
    rotateBottom(90, ARM1);
    rotateTop(0, ARM1);
    sys_state = REQ_INSTRCT;
  }

  else if (sys_state == ARM_2_LIMIT_INTRPT) 
  {
    rotateBottom(90, ARM2);
    rotateTop(0, ARM2);
    sys_state = REQ_INSTRCT;
  }

}