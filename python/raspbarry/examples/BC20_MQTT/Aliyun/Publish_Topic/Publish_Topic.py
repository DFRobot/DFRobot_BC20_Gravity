# -*- coding: utf-8 -*
'''!
  @file Publish_Topic.py
  @brief  Messages from the device to the cloud are sent by filling in the relevant information of the     
  @n      ALIYUN platform,If the Message is sent successfully, you can see "Message is sent." in the serial 
  @n      port, and you can see the Message you sent on the ALIYUN platform
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

sys.path.append(os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.realpath(__file__)))))))
from DFRobot_BC20_Gravity import *

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

#Configure device certificate information
ProductKey = "your_ProductKey"
ClientId = "your_ClientId"
DeviceName = "your_DeviceName"
DeviceSecret = "your_DeviceSecret"

#Configure the domain name and port number
ALIYUN_SERVER =".iot-as-mqtt.cn-shanghai.aliyuncs.com"
PORT = "1883"

#Product identifier that needs to be operated

Identifier = "your_Identifier"

#TOPIC that need to be published
pubTopic = "your_pubTopic"

def ConnectCloud():
  print("Attempting MQTT connection...")
  BC20.change_color(YELLOW)
  while BC20.connected() == False:
    print(".")
    BC20.led_on()
    time.sleep(0.5)
    BC20.led_off()
    time.sleep(0.5)    
    if BC20.connect_aliyun(ProductKey,DeviceName,DeviceSecret):  
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
print("Checking SIM card...")
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
print("SIM card ICCID:")
print(BC20.get_QCCID())
print("SIM card IMSI: ")
print(BC20.get_IMI())

'''The module will automatically attempt to connect to the network (mobile station).
   Check whether it is connected to the network.'''
BC20.change_color(BLUE)
while BC20.get_GATT()==0 :
  print(".");
  BC20.led_on()
  time.sleep(0.5)
  BC20.led_off()
  time.sleep(0.5)   
print("Network is connected!\r\n")

print("Connecting to DFRobot Aliyun-IoT")

#Configure IoT Server
while BC20.set_aliyun_server(ProductKey,ALIYUN_SERVER,PORT) == False:
  print("Connection to server failed!")
  time.sleep(1)

print("Server is available!")
ConnectCloud()

while True:
  time.sleep(5)
  print("send message to cloud...")  
  BC20.publish(pubTopic,"Hello")
  print("Message is sent.")        