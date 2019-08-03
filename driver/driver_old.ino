//#include "motor_control.h"
//#include "wifi_rw.h"
//
//// TODO: arm 1/2 relax disconnects power from the arm. activate will switch it back on.
//// TODO: add wifi data transfer of angles for visualization module to work off the system.
//// TODO: add manual control code and construct FSM for the same.
//// TODO: organize code into multiple files.
//
///******************
//   MAIN EXECUTION
// ******************/
//
//void arm1Interrupt() 
//{
//  sys_state = ARM_1_LIMIT_INTRPT;
//}
//
//void arm2Interrupt() 
//{
//  sys_state = ARM_2_LIMIT_INTRPT;
//}
//
//int input;
//String armToChange;
//String motorToChange;
//int amountToChange;
//
//void setup()
//{
//  Serial.begin(9600);
//
//  pinMode(2, OUTPUT);
//  digitalWrite(2, HIGH);
//  pinMode(3, OUTPUT);
//  digitalWrite(3, HIGH);
//
//  // configure interrupts
//  pinMode(arm_1_bot_intrpt_1, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(arm_1_bot_intrpt_1), arm1Interrupt, RISING);
//  pinMode(arm_1_bot_intrpt_2, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(arm_1_bot_intrpt_2), arm1Interrupt, RISING);
//  pinMode(arm_1_top_intrpt_1, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(arm_1_top_intrpt_1), arm1Interrupt, RISING);
//  pinMode(arm_1_top_intrpt_2, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(arm_1_top_intrpt_2), arm1Interrupt, RISING);
//  pinMode(arm_2_bot_intrpt_1, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(arm_2_bot_intrpt_1), arm2Interrupt, RISING);
//  pinMode(arm_2_bot_intrpt_2, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(arm_2_bot_intrpt_2), arm2Interrupt, RISING);
//  pinMode(arm_2_top_intrpt_1, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(arm_2_top_intrpt_1), arm2Interrupt, RISING);
//  pinMode(arm_2_top_intrpt_2, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(arm_2_top_intrpt_2), arm2Interrupt, RISING);
//
//
//  // configure starting positions for the motors
//  pwm.begin();
//  pwm.setPWMFreq(60); // analog servos run at ~60 Hz updates
//  pwm.setPWM(arm_1_base_pin, 0, MINIMUM_PULSE);
//  pwm.setPWM(arm_2_base_pin, 0, MINIMUM_PULSE);
//  delay(500);
//  pwm.setPWM(arm_1_bottom_pin, 0, 395);
//  pwm.setPWM(arm_2_bottom_pin, 0, MINIMUM_PULSE);
//  delay(500);
//  pwm.setPWM(arm_1_top_pin, 0, 315);
//  pwm.setPWM(arm_2_top_pin, 0, 315);
//  pwm.setPWM(arm_1_claw_pin, 0, 160);
//  pwm.setPWM(arm_2_claw_pin, 0, 160);
//  delay(500); 
//}
//
//void loop()
//{   
//  // read input
//  if (sys_state == REQ_INSTRCT)
//  {
//    Serial.println("Enter command in form: set arm1/arm2 base/bottom/top/claw angle/spacing");
//    sys_state = READ_INSTRCT;
//  }
//  else if (sys_state == READ_INSTRCT) 
//  {
//    if (Serial.available() > 0) 
//    {
//      input = Serial.readStringUntil('\n');
//      // go onto to next state
//      sys_state = PARSE_INSTRCT;
//    }
//  }
//  else if (sys_state == PARSE_INSTRCT) 
//  {
//    // find location of spaces
//    int firstSpace = -1;
//    int secondSpace = -1;
//    int thirdSpace = -1;
//    for (int i = 0; i < input.length(); i++) {
//      if (input[i] == ' ' && firstSpace == -1)
//        firstSpace = i;
//      else if (input[i] == ' ' && secondSpace == -1)
//        secondSpace = i;
//      else if (input[i] == ' ' && thirdSpace == -1)
//        thirdSpace = i;
//    }
//
//    if (firstSpace != -1 && secondSpace != -1 && thirdSpace != -1) 
//    {
//      // break the string apart at the spaces
//      armToChange = input.substring(firstSpace + 1, secondSpace);
//      motorToChange = input.substring(secondSpace + 1, thirdSpace);
//      String amountToChangeString = input.substring(thirdSpace + 1, input.length());
//      amountToChange = amountToChangeString.toInt();
//
//      sys_state = EXECUTE_INSTRCT;
//    }
//    else 
//    {
//      Serial.println("Sorry, invalid command");
//      sys_state = REQ_INSTRCT;
//    }
//  }
//  else if (sys_state == EXECUTE_INSTRCT) 
//  {
//    Serial.print("Setting "); 
//    Serial.print(armToChange); 
//    Serial.print(" "); 
//    Serial.print(motorToChange); 
//    Serial.print(" to "); 
//    Serial.println(amountToChange);
//
//    if (armToChange == "arm1")
//    {
//      if (motorToChange == "base")
//        rotateBase(amountToChange, ARM1);
//
//      if (motorToChange == "bottom")
//        rotateBottom(amountToChange, ARM1);
//
//      if (motorToChange == "top")
//        rotateTop(amountToChange, ARM1);
//
//      if (motorToChange == "claw")
//        setClawSpacing(amountToChange, ARM1);
//    }
//    else if (armToChange == "arm2") 
//    {
//      if (motorToChange == "base")
//        rotateBase(amountToChange, ARM2);
//
//      if (motorToChange == "bottom")
//        rotateBottom(amountToChange, ARM2);
//
//      if (motorToChange == "top")
//        rotateTop(amountToChange, ARM2);
//
//      if (motorToChange == "claw")
//        setClawSpacing(amountToChange, ARM2);
//    }
//
//    sys_state = REQ_INSTRCT;
//  }
//  else if (sys_state == ARM_1_LIMIT_INTRPT) 
//  {
//    rotateBottom(90, ARM1);
//    rotateTop(0, ARM1);
//    sys_state = REQ_INSTRCT;
//  }
//  else if (sys_state == ARM_2_LIMIT_INTRPT) 
//  {
//    rotateBottom(90, ARM2);
//    rotateTop(0, ARM2);
//    sys_state = REQ_INSTRCT;
//  }
//}
