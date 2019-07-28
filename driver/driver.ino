#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

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

// FSM
enum FSM_State {
  PROMPT,
  READ,
  PARSE,
  EXECUTE,
  INTERRUPT1,
  INTERRUPT2
};
FSM_State fsm = PROMPT;

// max/min angles for the different motors
#define MAX_TOP_ANGLE 135
#define MAX_BOTTOM_ANGLE 180
#define MAX_BASE_ANGLE 180
#define MIN_TOP_ANGLE -135
#define MIN_BOTTOM_ANGLE 0
#define MIN_BASE_ANGLE 0

// pins for various parts of arm
const int base_pin_1 = 0;
const int bottom_pin_1 = 1;
const int top_pin_1 = 2;
const int claw_pin_1 = 3;
const int base_pin_2 = 5;
const int bottom_pin_2 = 6;
const int top_pin_2 = 7;
const int claw_pin_2 = 8;
const int armOneInterruptPin1 = 0;
const int armOneInterruptPin2 = 1;
const int armOneInterruptPin3 = 4;
const int armOneInterruptPin4 = 5;
const int armTwoInterruptPin1 = 6;
const int armTwoInterruptPin2 = 7;
const int armTwoInterruptPin3 = 8;
const int armTwoInterruptPin4 = 9;

// current angular position
int current_base_angle_1 = 0;
int current_bottom_angle_1 = 0;
int current_top_angle_1 = 0;
int current_base_angle_2 = 0;
int current_bottom_angle_2 = 0;
int current_top_angle_2 = 0;

// speed delay for motors (higher = slower)
int speed_delay = 25;


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
    setAngle(claw_pin_1, angle);
  else if (arm == 2)
    setAngle(claw_pin_2, angle);
}

/**
   Sets the
   @param pin The pin
   @param angle
*/
void setAngle(int pin, int angle) {

  int adjustedAngle;
  if (pin == claw_pin_1 || pin == claw_pin_2)
    adjustedAngle = map(angle, 0, 180, MINIMUM_PULSE, MAXIMUM_PULSE);
  else if (pin == base_pin_1 || pin == base_pin_2)
    adjustedAngle = map(angle, 0, 180, 90, 400);
  else if (pin == bottom_pin_1 || pin == bottom_pin_2)
    adjustedAngle = map(angle, 180, 0, 90, 395);
  else if (pin == top_pin_1 || pin == top_pin_2)
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

  if (arm == 1) {
    if (angle >= current_base_angle_1) {
      for (int i = current_base_angle_1; i < angle; ++i) {
        setAngle(base_pin_1, i);
        delay(speed_delay);
      }
    }
    else if (angle < current_base_angle_1) {
      for (int i = current_base_angle_1; i > angle; i--) {
        setAngle(base_pin_1, i);
        delay(speed_delay);
      }
    }
    current_base_angle_1 = angle;
  }

  else if (arm == 2) {
    if (angle >= current_base_angle_2) {
      for (int i = current_base_angle_2; i < angle; i++) {
        setAngle(base_pin_2, i);
        delay(speed_delay);
      }
    }
    else if (angle < current_base_angle_2) {
      for (int i = current_base_angle_2; i > angle; i--) {
        setAngle(base_pin_2, i);
        delay(speed_delay);
      }
    }
    current_base_angle_2 = angle;
  }

}

/**
   Hi there
   @param angle
   @param arm
*/
void rotateBottom(int angle, int arm) {

  if (angle < MIN_BOTTOM_ANGLE || angle > MAX_BOTTOM_ANGLE)
    return;

  if (arm == 1) {
    if (angle >= current_bottom_angle_1) {
      for (int i = current_bottom_angle_1; i < angle; i++) {
        setAngle(bottom_pin_1, i);
        delay(speed_delay);
      }
    }
    else if (angle < current_bottom_angle_1) {
      for (int i = current_bottom_angle_1; i > angle; i--) {
        setAngle(bottom_pin_1, i);
        delay(speed_delay);
      }
    }
    current_bottom_angle_1 = angle;
  }

  else if (arm == 2) {
    if (angle >= current_bottom_angle_2) {
      for (int i = current_bottom_angle_2; i < angle; i++) {
        setAngle(bottom_pin_2, i);
        delay(speed_delay);
      }
    }
    else if (angle < current_bottom_angle_2) {
      for (int i = current_bottom_angle_2; i > angle; i--) {
        setAngle(bottom_pin_2, i);
        delay(speed_delay);
      }
    }
    current_bottom_angle_2 = angle;
  }

}

/**
   @param angle
   @para
*/
void rotateTop(int angle, int arm) {

  if (angle < MIN_TOP_ANGLE || angle > MAX_TOP_ANGLE)
    return;

  if (arm == 1) {
    if (angle >= current_top_angle_1) {
      for (int i = current_top_angle_1; i < angle; i++) {
        setAngle(top_pin_1, i);
        delay(speed_delay);
      }
    }
    else if (angle < current_top_angle_1) {
      for (int i = current_top_angle_1; i > angle; i--) {
        setAngle(top_pin_1, i);
        delay(speed_delay);
      }
    }
    current_top_angle_1 = angle;
  }

  else if (arm == 2) {
    if (angle >= current_top_angle_2) {
      for (int i = current_top_angle_2; i < angle; i++) {
        setAngle(top_pin_2, i);
        delay(speed_delay);
      }
    }
    else if (angle < current_top_angle_2) {
      for (int i = current_top_angle_2; i > angle; i--) {
        setAngle(top_pin_2, i);
        delay(speed_delay);
      }
    }
    current_top_angle_2 = angle;
  }

}

void arm1Interrupt() {
  fsm = INTERRUPT1;
}

void arm2Interrupt() {
  fsm = INTERRUPT2;
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
//  pinMode(armOneInterruptPin1, INPUT);
//  attachInterrupt(digitalPinToInterrupt(armOneInterruptPin1), arm1Interrupt, RISING);
//  pinMode(armOneInterruptPin2, INPUT);
//  attachInterrupt(digitalPinToInterrupt(armOneInterruptPin2), arm1Interrupt, RISING);
//  pinMode(armOneInterruptPin3, INPUT);
//  attachInterrupt(digitalPinToInterrupt(armOneInterruptPin3), arm1Interrupt, RISING);
//  pinMode(armOneInterruptPin4, INPUT);
//  attachInterrupt(digitalPinToInterrupt(armOneInterruptPin4), arm1Interrupt, RISING);
//  pinMode(armTwoInterruptPin1, INPUT);
//  attachInterrupt(digitalPinToInterrupt(armTwoInterruptPin1), arm2Interrupt, RISING);
//  pinMode(armTwoInterruptPin2, INPUT);
//  attachInterrupt(digitalPinToInterrupt(armTwoInterruptPin2), arm2Interrupt, RISING);
//  pinMode(armTwoInterruptPin3, INPUT);
//  attachInterrupt(digitalPinToInterrupt(armTwoInterruptPin3), arm2Interrupt, RISING);
//  pinMode(armTwoInterruptPin4, INPUT);
//  attachInterrupt(digitalPinToInterrupt(armTwoInterruptPin4), arm2Interrupt, RISING);


  // CONFIGURE STARTING POSITIONS
  pwm.begin();
  pwm.setPWMFreq(60); // analog servos run at ~60 Hz updates
  pwm.setPWM(base_pin_1, 0, MINIMUM_PULSE);
  pwm.setPWM(base_pin_2, 0, MINIMUM_PULSE);
  delay(500);
  pwm.setPWM(bottom_pin_1, 0, 395);
  pwm.setPWM(bottom_pin_2, 0, 395);
  delay(500);
  pwm.setPWM(top_pin_1, 0, 315);
  pwm.setPWM(top_pin_2, 0, 315);
  pwm.setPWM(claw_pin_1, 0, 160);
  pwm.setPWM(claw_pin_2, 0, 160);
  delay(500); 

}

void loop()
{ 
  
  // read input
  if (fsm == PROMPT)
  {
    Serial.println("Enter command in form set (arm1/arm2) (base/bottom/top/claw) (angle/spacing):");
    fsm = READ;
  }

  else if (fsm == READ) {
    if (Serial.available() > 0) {
      input = Serial.readStringUntil('\n');
      //go onto to next state
      fsm = PARSE;
    }

  }

  else if (fsm == PARSE) {

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

    if (firstSpace != -1 && secondSpace != -1 && thirdSpace != -1) {

      //break the string apart at the spaces
      armToChange = input.substring(firstSpace + 1, secondSpace);
      motorToChange = input.substring(secondSpace + 1, thirdSpace);
      String amountToChangeString = input.substring(thirdSpace + 1, input.length());
      amountToChange = amountToChangeString.toInt();

      fsm = EXECUTE;

    }

    else {

      Serial.println("Sorry, invalid command");
      fsm = PROMPT;

    }

  }

  else if (fsm == EXECUTE) {

    if (armToChange == "arm1") {

      if (motorToChange == "base")
        rotateBase(amountToChange, ARM1);

      if (motorToChange == "bottom")
        rotateBottom(amountToChange, ARM1);

      if (motorToChange == "top")
        rotateTop(amountToChange, ARM1);

      if (motorToChange == "claw")
        setClawSpacing(amountToChange, ARM1);

    }

    else if (armToChange == "arm2") {

      if (motorToChange == "base")
        rotateBase(amountToChange, ARM2);

      if (motorToChange == "bottom")
        rotateBottom(amountToChange, ARM2);

      if (motorToChange == "top")
        rotateTop(amountToChange, ARM2);

      if (motorToChange == "claw")
        setClawSpacing(amountToChange, ARM2);

    }

    fsm = PROMPT;

  }

  else if (fsm == INTERRUPT1) {
    rotateBottom(90, ARM1);
    rotateTop(0, ARM1);
    fsm = PROMPT;
  }

  else if (fsm == INTERRUPT2) {
    rotateBottom(90, ARM2);
    rotateTop(0, ARM2);
    fsm = PROMPT;
  }

}
