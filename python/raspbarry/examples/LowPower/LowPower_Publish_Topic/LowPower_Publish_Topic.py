# -*- coding: utf-8 -*
'''!
  @file LowPower_Publish_Topic.py
  @brief    This demo adds low-power content to the regular IOTdemo, where you can see the 
  @n        NB module being awakened in a loop on the serial monitor and then upload the message to the cloud
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

WAKEUP_PIN = 13

#Configure device certificate information
Iot_id = "zaMf62jZg"
Client_ID  = "1"
Iot_pwd    = "z-MB62jWRz"

#Configure the domain name and port number
EasyIot_SERVER = "182.254.130.180"
PORT = "1883"

#Set the Topic you need to publish to
pubTopic = "QjREoXEZg"

def ConnectCloud():
  print("Attempting MQTT connection...")
  BC20.change_color(YELLOW)
  while BC20.connected() == False:
    print(".")
    BC20.led_on()
    time.sleep(0.5)
    BC20.led_off()
    time.sleep(0.5)    
    if BC20.connect_server(Client_ID, Iot_id, Iot_pwd):  
      print("Connect Server OK")
    else:
#Used to detect the connection between the device and the server
      if BC20.get_QMTCONN():
        break 
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
  
BC20.get_GSN(1)
print("BC20 IMEI:")
print(BC20.imei)
print("\r\n")
print("SIM card ICCID:")
print(BC20.get_QCCID())
print("SIM card IMSI: ")
print(BC20.get_IMI())

BC20.change_color(BLUE)
while BC20.get_GATT()==0 :
  print(".");
  BC20.led_on()
  time.sleep(0.5)
  BC20.led_off()
  time.sleep(0.5)   
print("Network is connected!")

print("Connecting to DFRobot Easy-IoT")
BC20.set_server(EasyIot_SERVER, PORT)
print("Server is available!")

ConnectCloud()

BC20.set_PSM_mode(1)

BC20.config_sleep_mode(1)

while True:
  print("send message to cloud...")  
  BC20.publish(pubTopic,"Hello")
  print("Message is sent.") 
#The Controller and BC20(NB-IoT module) is bridged by an STM32.
#To put the module into low power mode,
#simply put STM32 into Deep Sleep Mode.
#BC20 will reaches lowest power(PSM + Deep Sleep Mode) automatically.
#To wake up the module,
#wake up STM32 first and then BC20.  
  if BC20.stm_low_power() == False:
    print("STM32 enter Sleep Mode!")
    
#Wakeup interval    
  time.sleep(6)
  
#A rising edge on IRQ to wake up STM32  
  BC20.stm_wake_up(WAKEUP_PIN)   
  print("STM32 exits Sleep Mode!")
#Wake up BC20  
  BC20.change_color(WHITE)
  while BC20.BC20_wake_up() == False:
    BC20.led_on()
    time.sleep(0.5)
    BC20.led_off()
    time.sleep(0.5)
  print("BC20 exits PSM successfully!")        
  
  