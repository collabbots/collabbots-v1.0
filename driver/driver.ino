#include "motor_control.h"
#include "wifi_rw.h"

// TODO: arm 1/2 relax disconnects power from the arm. activate will switch it back on.
// TODO: add wifi data transfer of angles for visualization module to work off the system.
// TODO: add manual control code and construct FSM for the same.
// TODO: organize code into multiple files.

/******************
   MAIN EXECUTION
 ******************/

void arm1Interrupt() 
{
  sys_state = ARM_1_LIMIT_INTRPT;
}

void arm2Interrupt() 
{
  sys_state = ARM_2_LIMIT_INTRPT;
}
 
int input;
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

  // configure interrupts
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


  // configure starting positions for the motors
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
    sys_state = READ_INSTRCT;
  }
  else if (sys_state == READ_INSTRCT) 
  {
    if (Serial.available() > 0) 
    {
      input = Serial.read(); 
      // go onto to next state
      sys_state = EXECUTE_INSTRCT;
    }
  }
  else if (sys_state == EXECUTE_INSTRCT) 
  {
    if (input == 'A')
      rotateBase(arm_2_base_angle + 3, ARM2);

    else if (input == 'D')
      rotateBase(arm_2_base_angle - 3, ARM2);

    else if (input == 'W')
      rotateBottom(arm_2_bottom_angle + 3, ARM2); 

    else if (input == 'S')
      rotateBottom(arm_2_bottom_angle - 3, ARM2); 

    else if (input == 'Q')
      rotateTop(arm_2_top_angle + 3, ARM2); 

    else if (input == 'E')
      rotateTop(arm_2_top_angle - 3, ARM2); 

    else if (input == 'Z')
      setClawSpacing(5, ARM2);

    else if (input == 'C')
      setClawSpacing(2, ARM2);

    else if (input == 'a')
      rotateBase(arm_1_base_angle + 3, ARM1);

    else if (input == 'd')
      rotateBase(arm_1_base_angle - 3, ARM1);

    else if (input == 'w')
      rotateBottom(arm_1_bottom_angle + 3, ARM1); 

    else if (input == 's')
      rotateBottom(arm_1_bottom_angle - 3, ARM1); 

    else if (input == 'q')
      rotateTop(arm_1_top_angle + 3, ARM1); 

    else if (input == 'e')
      rotateTop(arm_1_top_angle - 3, ARM1); 

    else if (input == 'z')
      setClawSpacing(5, ARM1);

    else if (input == 'c')
      setClawSpacing(2, ARM1);

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

