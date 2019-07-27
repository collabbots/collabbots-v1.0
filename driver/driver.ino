#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h> 

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
uint8_t servonum = 1;

//minimum/maximum pulse signals 
#define MINIMUM_PULSE 90
#define MAXIMUM_PULSE 540 

#define ARM1 1 
#define ARM2 2

//max/min angles for the different motors
#define MAX_TOP_ANGLE 135
#define MAX_BOTTOM_ANGLE 180
#define MAX_BASE_ANGLE 180 
#define MIN_TOP_ANGLE -135
#define MIN_BOTTOM_ANGLE 0 
#define MIN_BASE_ANGLE 0 

//pins for various parts of arm 
const int basePin1 = 0; 
const int bottomPin1 = 1;      //FOR MOTOR 2: FULL RED = CLAW/GRIPPER, QUARTER-RED = BOTTOM, HALF-RED = TOP
const int topPin1 = 2; 
const int clawPin1 = 3;  

const int basePin2 = 5; 
const int bottomPin2 = 6; 
const int topPin2 = 7; 
const int clawPin2 = 8; 

//current angular position 
int currentBaseAngle1 = 0; 
int currentBottomAngle1 = 0; 
int currentTopAngle1 = 0;

int currentBaseAngle2 = 0; 
int currentBottomAngle2 = 0; 
int currentTopAngle2 = 0; 

//speed of motors (higher = slower)
int speed = 25; 

void setup() {
  Serial.begin(9600);
  
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  pwm.setPWM(basePin1, 0, MINIMUM_PULSE);
  pwm.setPWM(basePin2, 0, MINIMUM_PULSE);
  delay(500); 
  pwm.setPWM(bottomPin1, 0, MINIMUM_PULSE);
  pwm.setPWM(bottomPin2, 0, MINIMUM_PULSE);
  delay(500); 
  pwm.setPWM(topPin1, 0, 315); 
  pwm.setPWM(topPin2, 0, 315);
  pwm.setPWM(clawPin1, 0, 160); 
  pwm.setPWM(clawPin2, 0, 160);
  delay(500);
}


void setClawSpacing(double spacing, int arm){
  if (spacing > 5 || spacing < 0)
    return; 
  int angle = -13.386 * spacing + 106.28; 
  if (arm == 1)
    setAngle(clawPin1, angle);  
  else if (arm == 2) 
    setAngle(clawPin2, angle); 
}


void setAngle(int pin, int angle){
  
  int adjustedAngle; 
  if (pin == clawPin1 || pin == clawPin2)
    adjustedAngle = map(angle, 0, 180, MINIMUM_PULSE, MAXIMUM_PULSE); 
  else if (pin == basePin1 || pin == basePin2)
    adjustedAngle = map(angle, 0, 180, 90, 400); 
  else if (pin == bottomPin1 || pin == bottomPin2)
    adjustedAngle = map(angle, 0, 180, 85, 395); 
  else if (pin == topPin1 || pin == topPin2)
    adjustedAngle = map(angle, -135, 135, 90, 540); 
  pwm.setPWM(pin, 0, adjustedAngle);
  
}



void rotateBase(int angle, int arm){
  
  if (angle < MIN_BASE_ANGLE || angle > MAX_BASE_ANGLE)
    return; 

  if (arm == 1){
    if (angle >= currentBaseAngle1){
      for (int i = currentBaseAngle1; i < angle; i++){
        setAngle(basePin1, i);
        delay(speed); 
      }
    }
    else if (angle < currentBaseAngle1){
      for (int i = currentBaseAngle1; i > angle; i--){
        setAngle(basePin1, i);
        delay(speed); 
      }
    }
    currentBaseAngle1 = angle;
  }

  else if (arm == 2){
    if (angle >= currentBaseAngle2){
      for (int i = currentBaseAngle2; i < angle; i++){
        setAngle(basePin2, i);
        delay(speed); 
      }
    }
    else if (angle < currentBaseAngle2){
      for (int i = currentBaseAngle2; i > angle; i--){
        setAngle(basePin2, i);
        delay(speed); 
      }
    }
    currentBaseAngle2 = angle;
  } 
  
}

void rotateBottom(int angle, int arm){
  
  if (angle < MIN_BOTTOM_ANGLE || angle > MAX_BOTTOM_ANGLE)
    return; 

  if (arm == 1){
    if (angle >= currentBottomAngle1){
      for (int i = currentBottomAngle1; i < angle; i++){
        setAngle(bottomPin1, i);
        delay(speed); 
      }
    }
    else if (angle < currentBottomAngle1){
      for (int i = currentBottomAngle1; i > angle; i--){
        setAngle(bottomPin1, i);
        delay(speed); 
      }
    }
    currentBottomAngle1 = angle; 
  }

  else if (arm == 2){
    if (angle >= currentBottomAngle2){
      for (int i = currentBottomAngle2; i < angle; i++){
        setAngle(bottomPin2, i);
        delay(speed); 
      }
    }
    else if (angle < currentBottomAngle2){
      for (int i = currentBottomAngle2; i > angle; i--){
        setAngle(bottomPin2, i);
        delay(speed); 
      }
    }
    currentBottomAngle2 = angle; 
  }
  
}



void rotateTop(int angle, int arm){
  
  if (angle < MIN_TOP_ANGLE || angle > MAX_TOP_ANGLE)
    return; 

  if (arm == 1){
    if (angle >= currentTopAngle1){
      for (int i = currentTopAngle1; i < angle; i++){
        setAngle(topPin1, i);
        delay(speed); 
      }
    }
    else if (angle < currentTopAngle1){
      for (int i = currentTopAngle1; i > angle; i--){
        setAngle(topPin1, i);
        delay(speed); 
      }
    }
    currentTopAngle1 = angle; 
  }

  else if (arm == 2){
    if (angle >= currentTopAngle2){
      for (int i = currentTopAngle2; i < angle; i++){
        setAngle(topPin2, i);
        delay(speed); 
      }
    }
    else if (angle < currentTopAngle2){
      for (int i = currentTopAngle2; i > angle; i--){
        setAngle(topPin2, i);
        delay(speed); 
      }
    }
    currentTopAngle2 = angle; 
  }
  
}


void loop(){

  setClawSpacing(5, ARM1); 
  delay(2000); 
  setClawSpacing(4, ARM1); 
  delay(1500); 
  
}
