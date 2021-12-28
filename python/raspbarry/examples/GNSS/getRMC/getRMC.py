# -*- coding: utf-8 -*
'''!
  @file getRMC.py
  @brief After clicking upload, you can see the satellite RMC protocol in the serial port
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

#Initialize BC20
print("Starting the BC20.Please wait...")
BC20.change_color(RED)
while BC20.power_on()==False:
  print(".")
  BC20.led_on()
  time.sleep(0.5)
  BC20.led_off()
  time.sleep(0.5)
print("BC20 started successfully!\r\n") 

#Disable sleep mode 
BC20.config_sleep_mode(0)

#Power up GNSS
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

while True :
  BC20.get_QGNSSRD("\"NMEA/RMC\"")
  
#UTC Date, format: ddmmyy, ex. 290519 = 2019/05/29  
  print("UTC Date: "),
  print(BC20.sRMC.UTC_Date)
  
#UTC time, format: hhmmss.ss, ex. 162436.54 = 16:24:36.54
#h - hours
#m - minutes
#s - seconds  
  print("UTC Time: "),
  print(BC20.sRMC.UTC_Time)
  
#DataStatus
#V - Invalid
#A - Valid  
  print("Data Status: "),
  print(BC20.sRMC.DataStatus)
  
#Latitude, format: ddmm.mmmmm, ex. 3150.7820 => 31deg 50.7820min
#d - degrees
#m - minutes  
  print("Latitude: "),
  print(BC20.sRMC.LatitudeVal),
  print(" "),
  
#Latitude north or south
#N - North
#S - South  
  print(BC20.sRMC.LatitudeDir)
  
#Longitude, format: dddmm.mmmmm, ex. 12135.6794 => 121deg 35.6794min
#d - degrees
#m - minutes  
  print("Longitude: "),
  print(BC20.sRMC.LongitudeVal),
  print(" "),
  
#Longitude east or west
#E - East
#W - West  
  print(BC20.sRMC.LongitudeDir)
  
#Ground Speed, speed over ground, unit in knots  
  print("Ground Speed: "),
  print(BC20.sRMC.GroundSpeed),
  print(" knots")
  
#Ground Heading, heading over ground, unit in degrees  
  print("Ground Heading: "),
  print(BC20.sRMC.GroundHeading)
  
#Magnetic Declination, unit in degrees  
  print("Magnetic Declination: "),
  print(BC20.sRMC.MagDeclination)
  
#Magnetic Declination Direction, Magnetic declination E/W indicator  
  print("Magnetic Declination Direction: "),
  print(BC20.sRMC.MagDeclinationDir)
  
#Positioning Mode
#N - No fix
#A - Autonomous GPS fix
#D - Differential GPS fix  
  print("Positioning Mode: "),
  print(BC20.sRMC.PositioningMode)
  
#Navigation Status
#V - Invalid  
  print("Navigation Status: "),
  print(BC20.sRMC.NaviStatus)
  print("")
  BC20.led_on()
  time.sleep(0.5)
  BC20.led_off()
  time.sleep(3)  
  
  
  
  
  
  
  
  
  
  