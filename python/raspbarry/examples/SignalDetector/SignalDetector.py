# -*- coding: utf-8 -*
'''!
  @file file SignalDetector.py
  @brief    After clicking upload, you can see the current network signal on the serial monitor.
  @n        Meanwhile, you can judge the signal strength by the flashing of LED light of NB module
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

#The signal strength is indicated by both numerical value in dBm
#and the flashing LED:
#Strong signal - fast flash
#Medium signal - slow flash
#Weak signal - burst flash.
def NB_Signal_Fun():
#Get the NB-IoT signal strength.
  BC20.get_SQ()
#Signal quality RSSI<10, WEAK signal strength  
  BC20.change_color(WHITE)
  if BC20.rssi< 10 or BC20.rssi == 99:
    if BC20.rssi == 99:
      print("Signal not detectable")
    elif BC20.rssi == 0:
      print("Signal Strength: -113 dBm or less")
    else:
      print("Signal Strength: "),
      print(str((BC20.rssi - 2) * 2 - 109)+" dBm Weak")
    BC20.led_on()
    time.sleep(0.1)
    BC20.led_off()
    time.sleep(0.9)  
#Signal quality 10<=RSSI<25, MEDIUM signal strength    
  elif BC20.rssi >= 10 and BC20.rssi < 25:
    print("Signal Strength: "),
    print(str(((BC20.rssi - 2) * 2 - 109))+" dBm Medium")
    BC20.led_on()
    time.sleep(0.5)
    BC20.led_off()
    time.sleep(0.5)
#Signal quality RSSI>=25, STRONG signal strength    
  elif BC20.rssi >= 25:
    if BC20.rssi < 31:    
      print("Signal Strength: "),
      print(str((BC20.rssi - 2) * 2 - 109)+" dBm Strong")
    elif BC20.rssi == 31:
      print("Signal Strength: -51 dBm or greater")  
    for i in range(5):
      BC20.led_on()
      time.sleep(0.1)
      BC20.led_off()
      time.sleep(0.1)            

def setup():
  #Initialize BC20      
  print("Starting the BC20.Please wait...")
  BC20.change_color(RED)
  while BC20.power_on()==False:
    print(".")
    time.sleep(1)
    BC20.led_on()
    time.sleep(0.5)
    BC20.led_off()
    time.sleep(0.5)
  print("BC20 started successfully!\r\n")  

  #Check whether SIM card is inserted
  print("Checking SIM card ...")
  BC20.change_color(GREEN)
  while BC20.check_NB_card() == False:
    print("Please insert the NB SIM card...")
    BC20.led_on()
    time.sleep(0.5)
    BC20.led_off()
    time.sleep(0.5)  
  print("SIM card check OK!\r\n") 
  
  #Print IMEI, ICCID and IMSI  
  BC20.get_GSN(1)
  print("BC20 IMEI:")
  print(BC20.imei)
  print("\r\n")
  print("SIM card ICCID:")
  print(BC20.get_QCCID())
  print("SIM card IMSI: ")
  print(BC20.get_IMI())
  
  #The module will automatically attempt to connect to the network (mobile station).
  #Check whether it is connected to the network.
  print("Connecting network ...")
  BC20.change_color(BLUE)
  while BC20.get_GATT()==0 :
    print(".");
    BC20.led_on()
    time.sleep(0.5)
    BC20.led_off()
    time.sleep(0.5)   
  print("Network is connected!\r\n")   
  
def loop():
  #Get local NB-IoT signal strength and print
  NB_Signal_Fun()
  
if __name__ == "__main__":
  setup()
  while(1):
    loop() 
  