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
String stringInput; 
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

  /**********
   MANUAL MODE 
   In manual mode, run the serial monitor on Mac/Ubuntu and hold
   the keys to turn the arm. 
   A/D: rotate base 
   W/S: rotate bottom
   Q/E: rotate top 
   Z/C: open/close claw
   Note: lower case means controlling arm 1; CAPS LOCK means controlling arm 2
   **********/

  if (currentMode == MANUAL){
  
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

  /**********
   COMMAND_LINE MODE 
   In command line mode, enter the commands in the Serial monitor 
   to turn the arm to a specified position.
   Commands take the following form: 
   set arm1/arm2 base/bottom/top/claw angle/spacing
   **********/

  else if (currentMode == COMMAND_LINE){
    // read stringInput
    if (sys_state == REQ_INSTRCT)
    {
      Serial.println("Enter command in form: set arm1/arm2 base/bottom/top/claw angle/spacing");
      sys_state = READ_INSTRCT;
    }
    else if (sys_state == READ_INSTRCT) 
    {
      if (Serial.available() > 0) 
      {
        stringInput = Serial.readStringUntil('\n');
        // go onto to next state
        sys_state = PARSE_INSTRCT;
      }
    }
    else if (sys_state == PARSE_INSTRCT) 
    {
      // find location of spaces
      int firstSpace = -1;
      int secondSpace = -1;
      int thirdSpace = -1;
      for (int i = 0; i < stringInput.length(); i++) {
        if (stringInput[i] == ' ' && firstSpace == -1)
          firstSpace = i;
        else if (stringInput[i] == ' ' && secondSpace == -1)
          secondSpace = i;
        else if (stringInput[i] == ' ' && thirdSpace == -1)
          thirdSpace = i;
      }
  
      if (firstSpace != -1 && secondSpace != -1 && thirdSpace != -1) 
      {
        // break the string apart at the spaces
        armToChange = stringInput.substring(firstSpace + 1, secondSpace);
        motorToChange = stringInput.substring(secondSpace + 1, thirdSpace);
        String amountToChangeString = stringInput.substring(thirdSpace + 1, stringInput.length());
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
  
}
