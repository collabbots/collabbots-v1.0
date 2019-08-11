#! /usr/bin/env python
# -*- coding: utf-8 -*-
#
# This file presents an interface for interacting with the Playstation 4 Controller
# in Python. Simply plug your PS4 controller into your computer using USB and run this
# script!
#
# NOTE: I assume in this script that the only joystick plugged in is the PS4 controller.
#       if this is not the case, you will need to change the class accordingly.
#
# Copyright © 2015 Clay L. McLeod <clay.l.mcleod@gmail.com>
#
# Distributed under terms of the MIT license.

import os
import pprint
import pygame
import time
from pynput.keyboard import Key, Controller
keyboard = Controller()


def pressKey(keyToPress, currentArm):
    # Arm == 1 --> lowercase
    # Arm == 2 --> uppercase
    if(keyToPress == ''):
        return None
    if(currentArm == 1):
        keyboard.press(str(keyToPress).lower())
        keyboard.release(str(keyToPress).lower())
    elif(currentArm == 2):
        keyboard.press(str(keyToPress).upper())
        keyboard.release(str(keyToPress).upper())
    time.sleep(0.09)


class PS4Controller(object):
    """Class representing the PS4 controller. Pretty straightforward functionality."""

    controller = None
    axis_data = None
    button_data = None
    hat_data = None

    def init(self):
        """Initialize the joystick components"""

        pygame.init()
        pygame.joystick.init()
        self.controller = pygame.joystick.Joystick(0)
        self.controller.init()



    def listen(self):
        """Listen for events to happen"""

        if not self.axis_data:
            self.axis_data = {}

        if not self.button_data:
            self.button_data = {}
            for i in range(self.controller.get_numbuttons()):
                self.button_data[i] = False

        if not self.hat_data:
            self.hat_data = {}
            for i in range(self.controller.get_numhats()):
                self.hat_data[i] = (0, 0)

        while True:
            for event in pygame.event.get():
                if event.type == pygame.JOYAXISMOTION:
                    self.axis_data[event.axis] = round(event.value,2)
                elif event.type == pygame.JOYBUTTONDOWN:
                    self.button_data[event.button] = True
                elif event.type == pygame.JOYBUTTONUP:
                    self.button_data[event.button] = False
                elif event.type == pygame.JOYHATMOTION:
                    self.hat_data[event.hat] = event.value

                # Insert your code on what you would like to happen for each event here!
                # In the current setup, I have the state simply printing out to the screen.

                os.system('clear')
                pprint.pprint(self.button_data)
                pprint.pprint(self.axis_data)
                pprint.pprint(self.hat_data)
            global arm
            
            # SQUARE 
            if (self.button_data[0] == True): 
                pressKey('c', arm) 
            
            # X 
            if (self.button_data[1] == True): 
                pressKey('', arm)

            # O
            if (self.button_data[2] == True): 
                pressKey('z', arm)
            
            # TRIANGLE
            if (self.button_data[3] == True): 
                pressKey('', arm)

            # L1
            if (self.button_data[4] == True): 
                arm = 1
                time.sleep(0.3)

            # R1
            if (self.button_data[5] == True): 
                arm = 2
                time.sleep(0.3)

            # L2
            if (self.button_data[6] == True): 
                pressKey('e', arm)

            # R2
            if (self.button_data[7] == True): 
                pressKey('q', arm)

            # SHARE
            if (self.button_data[8] == True): 
                pressKey('', arm)

            # OPTIONS 
            if (self.button_data[9] == True): 
                pressKey('', arm)

            # LEFT JOYSTICK PRESS
            if (self.button_data[10] == True): 
                pressKey('', arm)

            # RIGHT JOYSTICK
            if (self.button_data[11] == True): 
                pressKey('', arm)

            # PS4 LOGO 
            if (self.button_data[12] == True): 
                pressKey('', arm)

            # TOUCHPAD
            if (self.button_data[13] == True): 
                keyboard.press('?')
                keyboard.release('?')
                time.sleep(1.5); 

            # LEFT JOYSTICK RIGHT 
            if (self.axis_data[0] > 0.9):
                pressKey('a', arm)

            # LEFT JOYSTICK LEFT 
            if (self.axis_data[0] < -0.9):
                pressKey('d', arm)

            # LEFT JOYSTICK DOWN 
            if (self.axis_data[1] > 0.9):
                pressKey('', arm)

            # LEFT JOYSTICK UP
            if (self.axis_data[1] < -0.9):
                pressKey('', arm)

            # RIGHT JOYSTICK RIGHT
            if (self.axis_data[2] > 0.9):
                pressKey('', arm)

            # RIGHT JOYSTICK LEFT
            if (self.axis_data[2] < -0.9):
                pressKey('', arm)

            # RIGHT JOYSTICK DOWN 
            if (self.axis_data[3] > 0.9):
                pressKey('s', arm)

            # RIGHT JOYSTICK UP
            if (self.axis_data[3] < -0.9):
                pressKey('w', arm)
                
            




if __name__ == "__main__":
    ps4 = PS4Controller()
    ps4.init()
    arm = 1
    ps4.listen()
