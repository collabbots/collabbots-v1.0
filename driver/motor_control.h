#ifndef motor_control_h
#define motor_control_h

#include "globals.h"
#include <Servo.h>
#include <Wire.h>

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

#endif
