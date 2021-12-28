# -*- coding: utf-8 -*
'''!
  @file Subscribe_Topic.py
  @brief You can subscribe to the EASY-IOT topic by filling in the information about the EASY-IOT platform
  @n     By using the EASY-IOT platform to publish messages, you can see the corresponding topic messages
  @n     on the serial monitor
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

#Configure device certificate information
Iot_id = "your_Iot_id"
Client_ID  = "your_Client_ID"
Iot_pwd    = "your_Iot_pwd"

#Configure the domain name and port number
EasyIot_SERVER = "182.254.130.180"
PORT = "1883"

#Set the Topic you need to publish to
sub_topic = "your_subTopic"

#Each time the module receive a message, this function will be called.
#It will print the message and corresponding topic.
def callback():
  print("Recevice [Topic:"+BC20.topic+"] ")
  receivedData=BC20.payload
  print(receivedData)
  if receivedData=="open_red_LED":
    BC20.change_color(RED)
    BC20.led_on()
  elif receivedData=="close_red_LED": 
    BC20.led_off()

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
BC20.set_server(EasyIot_SERVER, PORT)
print("Server is available!")

#Conect to DFRobot Easy-IoT
ConnectCloud()

BC20.set_callback(callback)

while True:
  BC20.loop()