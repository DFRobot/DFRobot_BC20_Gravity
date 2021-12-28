# -*- coding: utf-8 -*
'''!
  @file Publish_Topic.py
  @brief    Messages from the device to the cloud are sent by filling in the relevant information 
  @n        of the ALIYUN platform If the Message is sent successfully, you can see "Message is 
  @n        sent." in the serial port, and you can see the Message you sent on the ALIYUN platform
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT License (MIT)
  @author      [PengKaixing](kaixing.peng@dfrobot.com)
  @version  V1.0.0
  @date  2019-07-16
  @url https://github.com/DFRobot/DFRobot_BC20_Gravity
'''

import sys
import os
import time

sys.path.append(os.path.dirname(os.path.dirname(os.path.dirname(os.path.realpath(__file__)))))
from DFRobot_BC20 import *

RED = 'R'
BLUE = 'B'
GREEN = 'G'
YELLOW = 'Y'
PURPLE = 'P'
CYAN = 'C'
WHITE = 'W'

'''For general controllers. Communicate by IIC
   Connect Instructions
      Raspberry Pi   |    Module(BC20)
      SDA(GPIO3)     |       D/T
      SCL(GPIO5)     |       C/R
      GND(GPIO6)     |       GND
      VCC(GPIO2)     |       VCC

   IIC address(A0,A1)
     0x30:(A0=0,A1=0)
     0x31:(A0=0,A1=1)
     0x32:(A0=1,A1=0)
     0x33:(A0=1,A1=1) default'''

'''For general controllers. Communicate by Serial
   Connect Instructions
      Raspberry Pi   |    Module(BC20)
      RXD(GPIO10)    |       D/T
      TXD(GPIO8)     |       C/R
      GND(GPIO6)     |       GND
      VCC(GPIO2)     |       VCC'''
          
BC20=DFRobot_BC20_IIC(0x33)

#BC20=DFRobot_BC20_Serial()
     
while True:
  BC20.change_color(RED)
  for i in range(3):
    BC20.led_on()
    time.sleep(0.5)
    BC20.led_off()
    time.sleep(0.5)
  
  BC20.change_color(GREEN)
  for i in range(3):
    BC20.led_on()
    time.sleep(0.5)
    BC20.led_off()
    time.sleep(0.5)
   
  BC20.change_color(BLUE)
  for i in range(3):
    BC20.led_on()
    time.sleep(0.5)
    BC20.led_off()
    time.sleep(0.5)

  BC20.change_color(YELLOW)
  for i in range(3):
    BC20.led_on()
    time.sleep(0.5)
    BC20.led_off()
    time.sleep(0.5)
              
  BC20.change_color(PURPLE)
  for i in range(3):
    BC20.led_on()
    time.sleep(0.5)
    BC20.led_off()
    time.sleep(0.5)
   
  BC20.change_color(CYAN)
  for i in range(3):
    BC20.led_on()
    time.sleep(0.5)
    BC20.led_off()
    time.sleep(0.5)  
    
  BC20.change_color(WHITE)
  for i in range(3):
    BC20.led_on()
    time.sleep(0.5)
    BC20.led_off()
    time.sleep(0.5)             