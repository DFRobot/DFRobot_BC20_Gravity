# -*- coding: utf-8 -*
'''!
  @file LowPower_Subscribe_Topic.py
  @brief    After filling in the relevant information and clicking upload, the 
  @n        NB module will enter low power consumption. You can issue a message 
  @n        through the cloud to wake up the NB module, but this message will not 
  @n        be displayed. After waking up, you can normally communicate with the 
  @n        device from the cloud.You can modify the code to select whether the 
  @n        NB module will enter low power again, just remember to wake it up
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

sleepFlag=False
timeStamp=0
SLEEP_INTERVAL=10000

#Configure device certificate information
Iot_id = "zaMf62jZg"
Client_ID  = "1"
Iot_pwd    = "z-MB62jWRz"

#Configure the domain name and port number
EasyIot_SERVER = "182.254.130.180"
PORT = "1883"

#Set the Topic you need to publish to
sub_topic = "QjREoXEZg"

#Each time the module receive a message, this function will be called.
#It will print the message and corresponding topic.
def callback():
  global sleepFlag
  global timeStamp
  print("Recevice [Topic:"+BC20.topic+"] ")
  receivedData=BC20.payload
  print(receivedData)
  timeStamp=int(round(time.time() * 1000))
  sleepFlag = True   

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
  while BC20.sub_topic('0', '1', sub_topic, '0') == False:
    print(".")
  print("\nTopic:"+sub_topic+" subscribed!")

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

#The module will automatically attempt to connect to the network (mobile station).
#Check whether it is connected to the network.
BC20.change_color(BLUE)
while BC20.get_GATT()==0 :
  print(".");
  BC20.led_on()
  time.sleep(0.5)
  BC20.led_off()
  time.sleep(0.5)   
print("Network is connected!\r\n")

#Set callback function
BC20.set_callback(callback)

print("Connecting to DFRobot Easy-IoT")

#Configure IoT Server
BC20.set_server(EasyIot_SERVER, PORT)
print("Server is available!")

#Enable Deep Sleep Mode
BC20.config_sleep_mode(1)
BC20.set_PSM_mode(1)

#Conect to DFRobot Easy-IoT
ConnectCloud()


if BC20.stm_low_power() == False:
  print("Module enters Sleep Mode!")

BC20.set_callback(callback)

while True:
#Note:
#1.The first message sent from the cloud is to wake up the module.
#This meassage will be THROWN AWAY.

#2.The second message and the following messages will be received and printed
#before the module enters sleep module.

#3.When the module enters sleep mode again, another wakeup message
#is needed before sending the valid messages.

#4.Interval between entering each sleep mode is determined
#by SLEEP_INTERVAL.
  BC20.loop()
  if sleepFlag == True:
    if (int(round(time.time() * 1000))) - timeStamp  >SLEEP_INTERVAL:
      sleepFlag=False
      if BC20.stm_low_power() == False:
        print("Module enters Sleep Mode!")
  
  
  
  