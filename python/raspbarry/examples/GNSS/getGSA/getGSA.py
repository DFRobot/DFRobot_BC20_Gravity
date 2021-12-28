# -*- coding: utf-8 -*
'''!
  @file getGSA.py
  @brief After clicking upload, you can see the satellite GSA protocol in the serial port
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

sys.path.append(os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.realpath(__file__))))))
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

print("Starting the BC20.Please wait...")
BC20.change_color(RED)
while BC20.power_on()==False:
  print(".")
  BC20.led_on()
  time.sleep(0.5)
  BC20.led_off()
  time.sleep(0.5)
print("BC20 started successfully!\r\n") 

BC20.config_sleep_mode(0)

print("Turning on GNSS ... ")
BC20.set_QGNSSC(1)
BC20.change_color(YELLOW)
if BC20.get_QGNSSC() == 0:
  print(".")
  BC20.led_on()
  time.sleep(0.5)
  BC20.led_off()
  time.sleep(0.5)
print("GNSS is ON.")
BC20.change_color(CYAN)

while True:

  BC20.get_QGNSSRD("\"NMEA/GSA\"")
  
  print("Mode\t\t"),
  for i in range(BC20.sGSA.NUM):
#Selection of 2D or 3D fix
#'M'=Manual, forced to switch 2D/3D mode
#'A'=Allowed to automatically switch 2D/3D mode
    print(BC20.sGSA.data[i].Mode),
    print("\t\t"),
  print("")  
  print("System ID\t"),
  for i in range(BC20.sGSA.NUM):
    print(BC20.sGSA.data[i].GNSS_SystemID),
    print("\t\t"),
  print("")
  for i in range(12):
    print("CH"),
    print(i + 1),
    print("\t\t"),
    
#A list of satellite being used on each channel
    for j in range(BC20.sGSA.NUM):
      print(BC20.sGSA.data[j].Statellite_CH[i]),
      print("\t\t"),
    print("")
  print("PDOP\t\t"),
  for i in range(BC20.sGSA.NUM) :
    print(BC20.sGSA.data[i].PDOP),
    print("\t\t"),
  print("")
#HDOP: Horizontal Dilution Of Precision 
  print("HDOP\t\t"),
  for i in range(BC20.sGSA.NUM) :
    print(BC20.sGSA.data[i].HDOP),
    print("\t\t"),
  print("") 

#VDOP: Vertical Dilution Of Precision
  print("VDOP\t\t"),
  for i in range(BC20.sGSA.NUM) :
    print(BC20.sGSA.data[i].VDOP),
    print("\t\t"),
  print("")        
  BC20.led_on()
  time.sleep(0.5)
  BC20.led_off()
  time.sleep(3)
  print("")       
      
  
  
  
  
  
  