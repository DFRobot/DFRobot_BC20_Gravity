# -*- coding: utf-8 -*
'''!
  @file getGGA.py
  @brief After clicking upload, you can see the satellite GGA protocol in the serial port
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
if BC20.get_QGNSSC() != 1 :
  print(".")
  BC20.led_on()
  time.sleep(0.5)
  BC20.led_off()
print("GNSS is ON.")
BC20.change_color(CYAN)
while True:  
  BC20.get_QGNSSRD("\"NMEA/GGA\"")
#UTC time, format: hhmmss.ss, ex. 162436.54 => 16:24:36.54
#h - hours
#m - minutes
#s - seconds'''  
  print("UTC Time: "),
  print(BC20.sGGA.UTC_Time)
  
#Latitude, format: ddmm.mmmmm, ex. 3150.7820 => 31deg 50.7820min
#d - degrees
#m - minutes  
  print("Latitude: "),
  print(BC20.sGGA.LatitudeVal),
  print(" "),
  
#Latitude north or south
#N - North
#S - North
  print(BC20.sGGA.LatitudeDir)
  
#Longitude, format: dddmm.mmmmm, ex. 12135.6794 => 121deg 35.6794min
#d - degrees
#m - minutes
  print("Longitude: "),
  print(BC20.sGGA.LongitudeVal),
  print(" "),
#Longitude wast or west
#E - East
#W - West
  print(BC20.sGGA.LongitudeDir)
  
#Fix status
#0 - degrees
#2 - DGPS fix
  print("Fix Status: "),
  print(BC20.sGGA.Status)
  
#Number of satellites being used (0 - 24)
  print("StatelliteNum: "),
  print(BC20.sGGA.StatelliteNum),
  print(" in Used")
  
#HDOP, Horizontal Dilution of Precision
  print("HDOP: "),
  print(BC20.sGGA.HDOP)
  
#Altitude, Altitude according to WGS84 ellipsoid, unit in meters
  print("Altitude: "),
  print(BC20.sGGA.Altitude),
  print(" m")

#GeoID Separation, height of GeoID (means sea level) above WGS84 ellipsoid, unit in meters
  print("GeoID Separation: "),
  print(BC20.sGGA.GeoID_Separation),
  print(" m")
  
#DGPS Age, age of DGPS data, empty if DGPS is not used, unit in seconds
  print("DGPS Age: "),
  print(BC20.sGGA.DGPS_Age)
  
#DGPS Station ID, DGPS station ID, empty if DGPS is not used
  print("DGPS Station ID: "),
  print(BC20.sGGA.DGPS_StationID)
  print("")
  BC20.led_on()
  time.sleep(0.5)
  BC20.led_off()
  time.sleep(3)     