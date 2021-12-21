# -*- coding: utf-8 -*
'''!
  @file DFRobot_BC20.py
  @brief 这是一个基于MQTT的物联网和卫星信息的综合模块
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT License (MIT)
  @author      [PengKaixing](kaixing.peng@dfrobot.com)
  @version  V1.0
  @date  2019-07-16
  @url https://github.com/DFRobot/DFRobot_BC20_Gravity
'''

import serial
import time
import ctypes
import smbus
import RPi.GPIO as GPIO

from enum import Enum

ser = serial.Serial("/dev/ttyAMA0", 9600)

class Node:
  def __init__(self):
    self.handle=0
    self.datalen=0
    self.data="" 
    self.next=None
    
front=Node()
rear=Node()
front=None
rear=None
color='W' 

class sGSV(ctypes.Structure):
  _fields_= [('PRN',ctypes.c_char_p),
             ('Elev',ctypes.c_char_p),
             ('Azim',ctypes.c_char_p),
             ('SNR',ctypes.c_char_p),
             ('Status',ctypes.c_char_p),
             ('SYS',ctypes.c_char_p)]

class sSAT_t(ctypes.Structure):
  _fields_=[('NUM',ctypes.c_int),
            ('USE',ctypes.c_int),
            ('data',sGSV*40)]  

class sGSAD(ctypes.Structure):
  _fields_=[('Mode',ctypes.c_char_p),
            ('FixStatus',ctypes.c_char_p),
            ('Statellite_CH',(ctypes.c_char_p)*12),     
            ('PDOP',ctypes.c_char_p),
            ('HDOP',ctypes.c_char_p), 
            ('VDOP',ctypes.c_char_p),
            ('GNSS_SystemID',ctypes.c_char_p)]

            
class sGSA_t(ctypes.Structure):
  _fields_=[('NUM',ctypes.c_int),
            ('data',sGSAD*2)]          

class sRMC_t(ctypes.Structure):
  _fields_=[('UTC_Time',ctypes.c_char_p),
            ('DataStatus',ctypes.c_char_p),
            ('LatitudeVal',ctypes.c_char_p),
            ('LatitudeDir',ctypes.c_char_p),
            ('LongitudeVal',ctypes.c_char_p),
            ('LongitudeDir',ctypes.c_char_p),
            ('GroundSpeed',ctypes.c_char_p),
            ('GroundHeading',ctypes.c_char_p),
            ('UTC_Date',ctypes.c_char_p),
            ('MagDeclination',ctypes.c_char_p),
            ('MagDeclinationDir',ctypes.c_char_p),
            ('PositioningMode',ctypes.c_char_p),
            ('NaviStatus',ctypes.c_char_p)]
            
class sCLK_t(ctypes.Structure):
  _fields_=[('Year',ctypes.c_int),
            ('Month',ctypes.c_int),
            ('Day',ctypes.c_int),
            ('Hour',ctypes.c_int),
            ('Minute',ctypes.c_int),
            ('Second',ctypes.c_int),
            ('TimeEquation',ctypes.c_int),
            ('Mode',ctypes.c_char_p)]

class sVTG_t(ctypes.Structure):
  _fields_=[('GroundCourse_True',ctypes.c_char_p),
            ('GroundCourse_Mag',ctypes.c_char_p),
            ('GroundCourse_Knots',ctypes.c_char_p),
            ('GroundCourse_Kmh',ctypes.c_char_p),
            ('PositioningMode',ctypes.c_char_p)]

class sGGA_t(ctypes.Structure):
  _fields_=[('UTC_Time',ctypes.c_char_p),
            ('LatitudeVal',ctypes.c_char_p),
            ('LatitudeDir',ctypes.c_char_p),
            ('LongitudeVal',ctypes.c_char_p),
            ('LongitudeDir',ctypes.c_char_p),
            ('Status',ctypes.c_char_p),
            ('StatelliteNum',ctypes.c_char_p),
            ('HDOP',ctypes.c_char_p),
            ('Altitude',ctypes.c_char_p),
            ('GeoID_Separation',ctypes.c_char_p),
            ('DGPS_Age',ctypes.c_char_p),
            ('DGPS_StationID',ctypes.c_char_p)]
 
class sGLL_t(ctypes.Structure):
  _fields_=[('LatitudeVal',ctypes.c_char_p),
           ('LatitudeDir',ctypes.c_char_p),
           ('LongitudeVal',ctypes.c_char_p),
           ('LongitudeDir',ctypes.c_char_p),
           ('UTC_Time',ctypes.c_char_p),
           ('DataStatus',ctypes.c_char_p),
           ('PositionMode',ctypes.c_char_p)]

class sGGNS_t(ctypes.Structure):
  _fields_=[('NUM',ctypes.c_int),
            ('LatitudeVal',ctypes.c_float),
            ('LatitudeDir',ctypes.c_char_p),
            ('LongitudeVal',ctypes.c_float),
            ('LongitudeDir',ctypes.c_char_p),
            ('Altitude',ctypes.c_float),
            ('Speed',ctypes.c_float),
            ('Heading',ctypes.c_float),
            ('Statellite_CH',((ctypes.c_char_p)*12)*2),
            ('NUM',ctypes.c_char_p),
            ('PDOP',ctypes.c_char_p),
            ('HDOP',ctypes.c_char_p),
            ('VDOP',ctypes.c_char_p),
            ('StatelliteNum',ctypes.c_int)]                      

class DFRobot_BC20(object):
  '''!
    @brief 这是一个基于MQTT的物联网和卫星信息的综合模块类
  '''
  def __init__(self): 
    #e_Mode 
    self.eSleepMode_Disable="0"
    self.eSleepMode_DeepSleep="1"
    self.eSleepMode_Light="2" 
    #sGSN_t
    self.sn=""
    self.imei=""
    self.imeisv="" 
    self.svn=""
    #sSIMCard
    self.IMEI_NUM=""
    #sCLK_t
    self.Year=0
    self.Month=0
    self.Day=0
    self.Hour=0
    self.Minute=0
    self.Second=0
    self.Mode=""
    self.TimeEquation=0
    #sSQ
    self.rssi=0
    #mqtt_Connec
    self.mqttConneced=0
    #callback_data
    self.topic=""
    self.payload=""
    self.callback=None
    #sSAT
    self.sSAT=sSAT_t()
    #sGSA
    self.sGSA=sGSA_t()
    #sRMC
    self.sRMC=sRMC_t()
    #sCLK
    self.sCLK=sCLK_t()
    #sVTG
    self.sVTG=sVTG_t()
    #sGGA
    self.sGGA=sGGA_t()
    #sGLL
    self.sGLL=sGLL_t()
    #sGGNS
    self.sGGNS=sGGNS_t()
    
    self._TAUValue = "10000010"
    self._AcTValue = "01000011"
         
  def enqueue(self,handle,data):
    print(data)
    '''!
      @brief 数据入队函数
    '''
    global front
    global rear
    new_data=Node()  
    new_data.datalen=len(data)
    new_data.handle=handle  
    new_data.data = data
    if rear==None:      
      front = new_data
    else:
      rear.next = new_data    
    rear = new_data         
    rear.next = None    

  def dequeue(self):   
    '''!
      @brief 数据出队函数
    '''
    global front
    global rear   
    if front == None:
      return
    else:
      node=front
      front = front.next    
      return node

  def flush_queue(self):
    '''!
      @brief 清空队列中的数据
    '''
    global front
    global rear  
    if(rear!=None):  
      front=None    
      rear=None             

  def get_rec_data_for_num(self,num):
    '''!
      @brief   获取指定字符串中哪一个的数据
    '''
    global front
    global rear
    if rear == None:
      return
    else:
      if rear.data=="OK\r\n" :
        p=front
        for i in range(num-1): 
          if p==None:
            return  
          p=p.next    
        return p
  
  def get_rec_data_for_num_no_check(self,num):
    '''
      @brief 获取指定字符串中哪一个的数据,并且不检查数据是否规范
      @param num
    '''
    global front
    global rear
    if rear == None:
      return
    else:
      p=front
      for i in range(num-1): 
        if p==None:
          return  
        p=p.next      
      return p            
        
  def get_rec_data(self,INFO):
    '''!
      @brief  Gets information about a parameter from the returned data.
      @n      For example, the CIMI number of the SIM card
      @param INFO
    '''
    Data=self.get_rec_data_for_num(2)
    if INFO==0:
      if Data !=None:
        self.IMEI_NUM=Data.data      

  def get_Int_for_string(self,CMD,basic,n):
    '''
      @brief Send the command and get the number specified in the returned command
      @param CMD 用来设置在哪个命令后的数字
      @param basic 等待分析的数据
      @param n 获取几个数据
      @return uint8_t类型
    '''
    self.flush_queue()
    self.send_cmd(CMD)
    self.recevice_at_cmd(3000)
    Data=self.get_rec_data_for_num(2)
    if Data != None:
      if n==1: 
        tempStr=Data.data
        tempStr = self.remove_sth_string("+"+basic+":",tempStr);
        tempStr = self.get_sth_front_string("\r\n",tempStr)
        if len(tempStr)>15:
          return 0
        tempStr = int(tempStr) 
        return tempStr
      else :
        return 0
    else:
      return 0    
  
  def change_color(self,newcolor):
    '''
      @brief 改变模组的LED灯的颜色
      @param newColor
      @n     RED
      @n     BLUE
      @n     GREEN
      @n     YELLOW
      @n     PURPLE
      @n     CYAN
      @n     WHITE  
    '''
    global color
    color=newcolor
  
  def led_on(self):
    '''
      @brief 打开模组的LED灯
    '''
    global color
    self.flush_queue()
    self.send_cmd("LED_"+color+"_ON")
    
  def led_off(self):
    '''
      @brief 关闭模组的LED灯
    '''
    self.flush_queue()
    self.send_cmd("LED_W_OFF")    
  
  def check_rec_data(self,str):
    '''
      @brief 检查从NB模组中获取的数据中是否有这个字符串
      @param str 等待分析的字符串
      @return bool类型
      @retval 1 唤醒成功
      @retval 0 唤醒失败
    '''
    p=self.dequeue()
    while p!=None:
      if p.data==str:
        return True  
      p=self.dequeue()  
    return False
    
  def check_BC20(self):
    '''
      @brief 检测BC20是否存在
      @return bool类型，表示BC20存在的状态
      @retval 1 存在
      @retval 0 不存在
    '''
    self.flush_queue()
    self.send_cmd("")
    self.recevice_at_cmd(2000)  
    return self.check_rec_data("OK\r\n")

  def power_on(self):
    '''
      @brief 使能NB模组
      @return bool类型，表示返回初始化的状态
      @retval 1 成功
      @retval 0 失败
    '''
    '''if self.check_BC20():
      return True'''
    self.flush_queue()  
    self.send_cmd("powerOn")
    time.sleep(2)
    if self.check_BC20():
      return True
    return False
    
  def config_sleep_mode(self,mode):
    '''
      @brief 配置BC20模块进入睡眠模式
      @param mode
      @n     eSleepMode_Disable
      @n     eSleepMode_DeepSleep 
      @n     eSleepMode_Light
      @return bool类型
      @retval 1 发布成功
      @retval 0 发布失败
    '''
    self.flush_queue()
    self.send_cmd("QSCLK",str(mode))
    self.recevice_at_cmd(1000)
    return self.check_rec_data("OK\r\n")
  
  def rest(self,mode=1):
    '''
      @brief 模块软复位
      @return bool类型，复位操作是否成功
      @retval 1 成功
      @retval 0 失败
    '''
    self.flush_queue()
    self.send_cmd("QRST",str(mode))
    self.recevice_at_cmd(300)
    time.sleep(1000)
    return True
    
  def check_NB_card(self):
    '''
      @brief 检测NB移动卡是否存在
      @return bool类型，表示STM32存在的状态
      @retval 1 存在
      @retval 0 不存在
    '''
    self.flush_queue()
    self.send_cmd("CIMI")  
    self.recevice_at_cmd(300)
    ret=self.check_rec_data("OK\r\n")
    if ret==False:
      self.rest()
    return ret 

  def remove_sth_string(self,sth,std):  
    '''
      @brief 从一串字符中移除某一部分字符串
      @param sth 等待分析的字符串
      @param str 作为保留的字符串
      @return char*类型 剩余的字符串
    '''
    if std == None:
      return  
    ret=std
    tempInt=ret.find(sth)
    if tempInt != -1:
      ret=ret[tempInt+len(sth):len(ret)]
    return ret
    
  def get_sth_front_string(self,sth,std):
    '''
      @brief 从一串字符中获取某一部分字符串
      @param sth 等待分析的字符串
      @param std 作为保留的字符串
      @return char*类型 保留的字符串
    '''
    if std == None:
      return   
    ret=std
    temp=sth
    tempInt=ret.find(temp)  
    if tempInt != -1:
      ret=ret[0:tempInt]
    return  ret    
        
  def get_GSN(self,cmd):
    '''
      @brief 获取国际移动设备识别码信息
    '''
    self.flush_queue()
    self.send_cmd("CGSN",str(cmd))
    self.recevice_at_cmd(300)
    Data=self.get_rec_data_for_num(2)
    if Data!=None:
      tempStr=Data.data
      tempStr  = self.remove_sth_string("+CGSN: ",tempStr)
      tempStr = self.get_sth_front_string("\r\n",tempStr)
      self.imei=tempStr

  def get_QCCID(self):
    '''
      @brief get USIM card identification number
      @return String类型，USIM card identification number
    '''
    self.flush_queue()
    self.send_cmd("QCCID")
    self.recevice_at_cmd(300)
    Data=self.get_rec_data_for_num(2)
    if Data!=None:
      tempStr=Data.data    
      CCID=self.remove_sth_string("+QCCID: ",tempStr)
      return CCID

  def get_IMI(self):
    '''
      @brief 获取国际移动用户识别码
      @return uint8_t *类型，识别码数组的指针
    '''
    self.flush_queue()
    self.send_cmd("CIMI")    
    self.recevice_at_cmd(300)
    self.get_rec_data(0)
    return self.IMEI_NUM
    
  def get_GATT(self):
    '''
      @brief 检测设备是否已经连接上附近的NB基站
      @return uint8_t类型，获取模块连接状态
      @retval 1 已连接
      @retval 0 正在连接
    '''
    return (self.get_Int_for_string("CGATT?","CGATT",1))
    
  def get_CLK(self):
    '''
      @brief 获取此时的网络时间
      @return String类型，时间以字符串的形式输出
    '''
    self.flush_queue()
    self.send_cmd("CCLK?")   
    self.recevice_at_cmd(300)
    Data=self.get_rec_data_for_num(2)
    if Data != None:
      tempStr = Data.data
      if tempStr.find("+CCLK: ")==-1:
        return
      tempStr = self.remove_sth_string("+CCLK: ",tempStr)
      self.Year =int(self.get_sth_front_string("/",tempStr))
      tempStr  = self.remove_sth_string("/",tempStr)
      self.Month =int(self.get_sth_front_string("/",tempStr))
      tempStr  = self.remove_sth_string("/",tempStr)
      self.Day =int(self.get_sth_front_string(",",tempStr))
      tempStr  = self.remove_sth_string(",",tempStr)
      self.Hour =int(self.get_sth_front_string(":",tempStr))
      tempStr  = self.remove_sth_string(":",tempStr)
      self.Minute =int(self.get_sth_front_string(":",tempStr))
      tempStr  = self.remove_sth_string(":",tempStr)
      self.Second =int(self.get_sth_front_string("GMT",tempStr))
      tempStr  = self.remove_sth_string("GMT+",tempStr)
      tempStr = self.get_sth_front_string("\r",tempStr)
      self.TimeEquation=int(tempStr)
      self.Hour=self.Hour+self.TimeEquation
      tempStr = self.get_sth_front_string("\r\n",tempStr)
    
  def get_SQ(self):
    '''
      @brief 获取此时NB网络信号强度
    '''
    self.flush_queue()
    self.send_cmd("CSQ")    
    self.recevice_at_cmd(300)
    Data=self.get_rec_data_for_num(2)
    if Data!=None:
      tempStr  =Data.data
      if tempStr.find("+CSQ: ")==-1:
        return
      tempStr  =self.remove_sth_string("+CSQ: ",tempStr)
      self.rssi = int(self.get_sth_front_string(",",tempStr))
      tempStr  = self.remove_sth_string(",",tempStr)
      self.ber  = int(self.get_sth_front_string("\r\n",tempStr))

  def open_MQTT(self,connectID,Server,Port):
    '''
      @brief 打开MQTT连接通道
      @param connectID
      @param Server
      @param Port
      @return bool类型
      @retval 1 打开成功
      @retval 0 打开失败
    '''
    temptime=0
    tempStr ="QMTOPEN"+"="+connectID+",\""+Server+"\","+Port
    self.flush_queue()
    self.send_cmd(tempStr)   
    self.recevice_at_cmd(1000)
    if self.check_rec_data("OK\r\n"):
      while True:
        self.flush_queue()
        if temptime > 250:
          return False
        self.recevice_at_cmd(300)
        temptime+=1
        Data=self.get_rec_data_for_num_no_check(2)
        if Data!=None:
          tempStr=Data.data
          if tempStr=="+QMTOPEN: 0,0\r\n":
            return True
    return False       

  def close_MQTT(self,ConnectID):
     '''
       @brief 关闭MQTT连接通道
       @param connectID
       @return bool类型
       @retval 1 关闭成功
       @retval 0 关闭失败
     '''
     self.flush_queue()
     self.send_cmd("QMTCLOSE",str(ConnectID))
     self.recevice_at_cmd(500)
     

  def set_server(self,IPAddress,port,connectID="0"):
    '''
      @brief 设置MQTT服务器信息
      @param IPAddress
      @param port
      @param connectID
      @return bool类型
      @retval 1 设置成功
      @retval 0 设置失败
    '''
    while self.open_MQTT(connectID,IPAddress,port)==False :
      self.close_MQTT(0)
      time.sleep(1)
 
  def publish(self,topic,msg):  
    '''
      @brief 发布MQTT信息
      @param topic
      @param msg
      @return bool类型
      @retval 1 发布成功
      @retval 0 发布失败
    '''
    self.pub_message('0','1','1','0',topic,msg)      
 
  def pub_message(self,connectID,msgID,qos,retain,topic,msg):
    '''
      @brief 发布MQTT信息
      @param connectID
      @param msgID
      @param qos
      @param retain
      @param topic
      @param msg
      @return bool类型
      @retval 1 发布成功
      @retval 0 发布失败
    '''
    self.flush_queue()
    tempStr="QMTPUB"+"="+connectID+","+msgID+","+qos+","+retain+","+"\""+topic+"\","+"\""+msg+"\""
    self.send_cmd(tempStr)
    self.recevice_at_cmd(1000)

  def connected(self):
    '''
      @brief 设备是否已经连接服务器
      @return bool类型
      @retval 1 已经连接
      @retval 0 未连接
    '''
    return self.mqttConneced

  def connect_server(self,clientID,username,password,connectID="0"):
    '''
      @brief 连接服务器
      @param connectID
      @param clientID
      @param UserName
      @param PassWord
      @return bool类型
      @retval 1 连接成功
      @retval 0 连接失败
    '''
    temptime=0
    tempStr="QMTCONN"+"="+connectID+",\""+clientID+"\""+",\""+username+"\""+",\""+password+"\""
    self.flush_queue()
    self.send_cmd(tempStr)
    self.recevice_at_cmd(1000)
    if self.check_rec_data("OK\r\n"):
      while True:
        self.flush_queue()
        if temptime > 250:
          return False
        self.recevice_at_cmd(300)
        temptime+=1
        Data=self.get_rec_data_for_num_no_check(2)
        if Data!=None:
          tempStr=Data.data
          if tempStr=="+QMTCONN: 0,0,0\r\n":
            self.mqttConneced=True
            return True
    return False 

  def get_QMTCONN(self):
    '''
      @brief Used to detect the connection between the device and the server
      @return bool类型
      @retval 1 获取成功
      @retval 0 获取失败
    '''
    self.flush_queue()
    self.send_cmd("QMTCONN?")
    self.recevice_at_cmd(5000)
    Data=self.get_rec_data_for_num(2)
    if Data != None:
      tempStr=Data.data
      if tempStr=="+QMTCONN: 0,3\r\n":
        return True
      else:
        return False
    return False

  def sub_topic(self,connectID,msgID,topic,qos):
    '''
      @brief 订阅MQTT信息
      @param connectID
      @param msgID
      @param topic
      @param qos
      @return bool类型
      @retval 1 订阅成功
      @retval 0 订阅失败
    '''
    tempStr="QMTSUB"+"="+connectID+","+msgID+",\""+topic+"\","+qos
    self.flush_queue()
    self.send_cmd(tempStr)    
    self.recevice_at_cmd(3000)
    return self.check_rec_data("OK\r\n")

  def set_callback(self,call):
    '''
      @brief 设置订阅模式下MQTT信息的回调函数
    '''
    self.callback=call
    

  def loop(self):
    '''
      @brief 订阅模式下循环接收数据
    '''
    if self.available():
      tempStr=self.read_data(1000)
      if tempStr.find("+QMTRECV: ") !=-1 :
        tempStr = self.remove_sth_string("+QMTRECV: ",tempStr) 
        tempStr = self.remove_sth_string(",",tempStr)    
        tempStr = self.remove_sth_string(",\"",tempStr)
        self.topic=self.get_sth_front_string("\",",tempStr)
        tempStr = self.remove_sth_string("\",\"",tempStr)
        self.payload=self.get_sth_front_string("\"\r\n",tempStr)
        if self.callback != None:
          self.callback()
      sleep_time = 0.1
      time.sleep(sleep_time)
    else:
      sleep_time=10
      time.sleep(sleep_time)  

  def set_aliyun_server(self,ProductKey,IPAddress,port,connectID="0"):
    '''
      @brief 设置阿里云连接的相关信息
      @param ProductKey
      @param IPAddress
      @param port
      @param connectID
      @return bool类型
      @retval 1 设置成功
      @retval 0 设置失败
    '''
    IPaddress=ProductKey+IPAddress
    while self.open_MQTT(connectID,IPaddress,port) == False:
      self.close_MQTT(0)
      time.sleep(1)
      
  def connect_aliyun(self,ProductKey,DeviceName,DeviceSecret): 
    '''
      @param ProductKey
      @param DeviceName
      @param DeviceSecret
      @return bool类型
      @retval 1 连接成功
      @retval 0 连接失败 
    ''' 
    temptime=0    
    tempStr="QMTCFG"+"=\"ALIAUTH\",0,\""+ProductKey+"\",\""+DeviceName+"\",\""+DeviceSecret+"\""
    self.flush_queue()
    self.send_cmd(tempStr)
    self.recevice_at_cmd(300)
    if self.check_rec_data("OK\r\n") == False:
      return False
    tempStr="QMTCONN=0,\""+DeviceName+"\""
    self.flush_queue()
    self.send_cmd(tempStr)
    self.recevice_at_cmd(300)
    if self.check_rec_data("OK\r\n"):
      while True:
        self.flush_queue()
        if temptime > 250:
          return False
        self.recevice_at_cmd(300)
        temptime+=1
        Data=self.get_rec_data_for_num_no_check(2)
        if Data!=None:
          tempStr=Data.data
          if tempStr.find("ERROR") != -1:
            return False 
          if tempStr=="+QMTCONN: 0,0,0\r\n":
            self.mqttConneced=True
            return True
    return False  
    
  def set_QGNSSC(self,mode):
    '''
      @brief 设置GNSS是否打开
      @param mode
      @n 	1 打开
      @n 	0 关闭
      @return bool类型
      @retval 1 已经打开
      @retval 0 没有打开
    '''
    self.flush_queue()
    self.send_cmd("QGNSSC",str(mode))
    self.recevice_at_cmd(300)
    return self.check_rec_data("OK\r\n") 
    
  def get_QGNSSC(self):
    '''
     @brief 获取GNSS是否被打开 
     @return uint8_t类型
     @retval 1 已经打开
     @retval 0 没有打开
    '''
    return self.get_Int_for_string("QGNSSC?","QGNSSC",1)    

  def set_PSM_mode(self,status):
    '''
      @brief 设置BC20进入PSM模式
      @param mode
      @n     ePSM_OFF
      @n     ePSM_ON
      @n     ePSM_OFF_ResetParam
      @return bool类型
      @retval 1 唤醒成功
      @retval 0 唤醒失败
    '''
    self.flush_queue()
    tempStr="CPSMS"+"="+str(status)+",,,\""+self._TAUValue+"\",\""+self._AcTValue+"\""
    self.recevice_at_cmd(300)
    return self.check_rec_data("OK\r\n") 

  def config_sleep_mode(self,mode):
    '''
      @brief 配置BC20模块进入睡眠模式
      @param mode
      @n     eSleepMode_Disable
      @n     eSleepMode_DeepSleep 
      @n     eSleepMode_Light
      @return bool类型
      @retval 1 发布成功
      @retval 0 发布失败
    '''
    self.set_QSCLK(mode)

  def set_QSCLK(self,mode):
    '''
      @brief 设置低功耗模式
      @param mode
      @n      0 Disable Sleep Mode.
      @n      1 Enable light sleep and deep sleep, wakeup by PSM_EINT (Falling Edge).
      @n      2 Enable light sleep only, wakeup by Main UART.
      @return bool类型
      @retval 1 成功
      @retval 0 失败
    '''
    self.flush_queue()
    self.send_cmd("QSCLK",str(mode))
    self.recevice_at_cmd(300)
    return self.check_rec_data("OK\r\n")

  def stm_low_power(self):
    '''
      @brief 控制STM32进入低功耗模式
      @return bool类型
      @retval 1 唤醒成功
      @retval 0 唤醒失败
    '''
    self.change_color('B')
    self.led_on()
    time.sleep(0.01)
    self.led_off()
    time.sleep(0.01)     
    self.send_cmd("DSLEEP")
    time.sleep(0.01)
    return self.check_BC20()

  def stm_wake_up(self,Awake_Pin):
    '''
      @brief 控制STM32唤醒
      @param Awake_Pin 控制触发唤醒STM32的引脚
      @return bool类型
      @retval 1 唤醒成功
      @retval 0 唤醒失败
    '''
    try:  
      GPIO.setmode(GPIO.BOARD)
      GPIO.setup(Awake_Pin, GPIO.OUT)    
      GPIO.output(Awake_Pin, GPIO.LOW)
    except:
      print("")
    time.sleep(0.1)
    GPIO.output(Awake_Pin, GPIO.HIGH)
    time.sleep(0.1)
    GPIO.output(Awake_Pin, GPIO.LOW)
    return self.check_stm_stauts()
    
  def BC20_wake_up(self):
    '''
      @brief 唤醒BC20模块
      @return bool类型
      @retval 1 唤醒成功
      @retval 0 唤醒失败
    '''
    self.flush_queue()
    self.send_cmd("WakeUp")
    time.sleep(0.3)
    return self.check_BC20()    
    

  def check_stm_stauts(self):
    '''
      @brief 检测STM32是否存在
      @return bool类型，表示STM32存在的状态
      @retval 1 存在
      @retval 0 不存在
    '''
    self.flush_queue()
    self.send_cmd("STMSTATUS")
    self.recevice_at_cmd(300)
    return self.check_rec_data("OK\r\n")

  def get_satellite_Information(self,start,num,_str,sys):
    '''
      @brief Given a satellite data, which satellite does it start with, how many satellites do you have
      @param start 开始的字符
      @param num 获取几颗卫星的数据
      @param str 给定的卫星数据字符串
      @param sys 等待写入flash的数据
      @return uint8_t类型
    '''
    tempStr=_str
    for i in range(num):
      if len(self.get_sth_front_string(",",tempStr))==0:
        self.sSAT.data[i+start].PRN = "N/A"
      else:
        self.sSAT.data[i+start].PRN = self.get_sth_front_string(",",tempStr)  #卫星PRN码编号i+start 
      tempStr =self.remove_sth_string(",",tempStr)  
      if len(self.get_sth_front_string(",",tempStr)) == 0:
        self.sSAT.data[i+start].Elev = "N/A"
      else:
        self.sSAT.data[i+start].Elev = self.get_sth_front_string(",",tempStr) #卫星仰角i+start
      tempStr = self.remove_sth_string(",",tempStr) 
      if len(self.get_sth_front_string(",",tempStr)) == 0: 
        self.sSAT.data[i+start].Azim = "N/A"
      else:
        self.sSAT.data[i+start].Azim = self.get_sth_front_string(",",tempStr) #卫星方位角i+start   
      tempStr = self.remove_sth_string(",",tempStr)
      if len(self.get_sth_front_string(",",tempStr)) == 0:
        self.sSAT.data[i+start].SNR = "N/A"
      else:  
        self.sSAT.data[i+start].SNR = self.get_sth_front_string(",",tempStr) #信噪比i+start
      self.sSAT.data[i+start].SYS = sys
      tempStr = self.remove_sth_string(",",tempStr)
      self.check_satellite_use(i+start)
        
  def check_satellite_use(self,num):
    '''
      @brief 检查哪种卫星使用
      @param num 设置卫星信息列表的第几个数据
    '''
    if self.sSAT.data[num].SYS == "GPS":
      temp = 0
    elif self.sSAT.data[num].SYS == "BeiDou":
      temp = 1   
    for i in range(12):
      if self.sSAT.data[num].PRN == self.sGSA.data[temp].Statellite_CH[i]:
        self.sSAT.data[num].Status = "Y" 
        return     
    self.sSAT.data[num].Status = "N"

  def check_use(self):
    '''
      @brief 检查哪颗卫星可以使用
    '''
    self.sSAT.USE = 0
    for i in range(self.sGSA.NUM):
      for j in range(12):
        if len(self.sGSA.data[i].Statellite_CH[j]) > 0 and (self.sGSA.data[i].Statellite_CH[j] !="N/A"):
          self.sSAT.USE +=1
        
  def get_QGNSSRD(self,cmd):
    '''
      @brief 获取所有的卫星信息
      @return uint8_t类型
      @retval 1 获取成功
      @retval 0 获取失败
    '''
    if len(cmd)>0:
      readnum = 2
      self.flush_queue()
      self.send_cmd("QGNSSRD",cmd)
      self.recevice_at_cmd(5000)
      if cmd == "\"NMEA/GSV\"":
        StartNum = 0x00
        lastTotSEN = 0x00
        self.sSAT.NUM = 0x00
        for i in range(15):
          Data=self.get_rec_data_for_num_no_check(readnum+i)
          if Data != None:
            tempStr=Data.data
            if (tempStr.find("ERROR") != -1) or len(tempStr)<8:
              break 
            if tempStr.find("+QGNSSRD:") != -1:
              tempStr  = self.remove_sth_string("+QGNSSRD: ",tempStr)
            if tempStr.find("$GPGSV,") != -1:
              tempSYS = "GPS"
            elif tempStr.find("$GBGSV,") != -1:
              tempSYS = "BeiDou"
            else:
              tempSYS = "N/A"    
            tempStr = self.remove_sth_string(",",tempStr)
            TotSEN=int(self.get_sth_front_string(",",tempStr)) # 语句的总数目
            tempStr = self.remove_sth_string(",",tempStr)
            NumSEN=int(self.get_sth_front_string(",",tempStr)) # 当前语句序号
            tempStr = self.remove_sth_string(",",tempStr)
            NumSAT=int(self.get_sth_front_string(",",tempStr)) # 可见卫星数
            tempStr = self.remove_sth_string(",",tempStr)
            if TotSEN > 0:
              if NumSEN == 1:
                self.sSAT.NUM += NumSAT
                if self.sSAT.NUM>20:
                  self.sSAT.NUM=19
              if NumSAT /(NumSEN*4) > 0:
                self.get_satellite_Information(StartNum,4,tempStr,tempSYS) 
                StartNum += 4 
              else :
                self.get_satellite_Information(StartNum,(NumSAT-((NumSEN-1)*4)),tempStr,tempSYS)
                StartNum += (NumSAT-((NumSEN-1)*4))
      else:
        Data=self.get_rec_data_for_num(2)
        if Data!=None :
          tempStr  = Data.data
          if len(tempStr) < 10:
            return
        else:
          return 
        tempStr = self.remove_sth_string("+QGNSSRD: ",tempStr)
        if len(tempStr)<10:
          return
        if cmd== "\"NMEA/RMC\"":
          tempStr = self.remove_sth_string("$GNRMC,",tempStr)
          self.sRMC.UTC_Time = self.get_sth_front_string(",",tempStr)
          tempStr = self.remove_sth_string(",",tempStr)
          self.sRMC.DataStatus = self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr)
          self.sRMC.LatitudeVal = self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr)
          self.sRMC.LatitudeDir= self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr)
          self.sRMC.LongitudeVal=self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr)
          self.sRMC.LongitudeDir=self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr)
          self.sRMC.GroundSpeed=self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr)
          self.sRMC.GroundHeading=self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr)
          self.sRMC.UTC_Date=self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr)
          self.sRMC.MagDeclination=self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr)
          self.sRMC.MagDeclinationDir=self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr)        
          self.sRMC.PositioningMode=self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr) 
          self.sRMC.NaviStatus=self.get_sth_front_string("*",tempStr) 
          if self.sRMC.UTC_Time != None:
            timeStr = self.sRMC.UTC_Time
            self.sCLK.Hour = int(timeStr[0:2])      
            timeStr=timeStr[2:len(timeStr)]
            self.sCLK.Minute = int(timeStr[0:2])
            timeStr = timeStr[2:len(timeStr)]
            self.sCLK.Second = int(timeStr[0:2])
          if self.sRMC.UTC_Date != None:
            timeStr = self.sRMC.UTC_Date
            self.sCLK.Day = int(timeStr[0:2])
            timeStr = timeStr[2:len(timeStr)]
            self.sCLK.Month =int(timeStr[0:2])
            timeStr = timeStr[2:len(timeStr)]
            self.sCLK.Year = int(timeStr[0:2]) + 2000
            self.sCLK.Mode = "UTC+0"
        elif cmd == "\"NMEA/VTG\"":
          tempStr = self.remove_sth_string("$GNVTG,",tempStr) 
          self.sVTG.GroundCourse_True = self.get_sth_front_string(",",tempStr)
          tempStr = self.remove_sth_string("T,",tempStr)  
          self.sVTG.GroundCourse_Mag =self.get_sth_front_string(",",tempStr)
          tempStr = self.remove_sth_string("M,",tempStr)
          self.sVTG.GroundCourse_Knots = self.get_sth_front_string(",",tempStr)
          tempStr = self.remove_sth_string("N,",tempStr)
          self.sVTG.GroundCourse_Kmh=self.get_sth_front_string(",",tempStr)
          tempStr = self.remove_sth_string("K,",tempStr)
          self.sVTG.PositioningMode = self.get_sth_front_string("*",tempStr)
        elif cmd == "\"NMEA/GGA\"":
          tempStr = self.remove_sth_string("$GNGGA,",tempStr)
          self.sGGA.UTC_Time=self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr)
          self.sGGA.LatitudeVal=self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr)
          self.sGGA.LatitudeDir=self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr)
          self.sGGA.LongitudeVal=self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr)
          self.sGGA.LongitudeDir=self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr)
          self.sGGA.Status=self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr)
          self.sGGA.StatelliteNum=self.get_sth_front_string(",",tempStr)  
          tempStr =self.remove_sth_string(",",tempStr)
          self.sGGA.HDOP=self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr)
          self.sGGA.Altitude=self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string("M,",tempStr)
          self.sGGA.GeoID_Separation=self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string("M,",tempStr)
          self.sGGA.DGPS_Age = self.get_sth_front_string(",",tempStr)
          tempStr =self.remove_sth_string(",",tempStr)
          self.sGGA.DGPS_StationID = self.get_sth_front_string("*",tempStr)                                                              
        elif cmd == "\"NMEA/GSA\"":
          self.sGSA.NUM = 0
          for i in range(4):
            if tempStr.find("$GNGSA,") != -1 :
              self.sGSA.NUM = i+1
              tempStr = self.remove_sth_string("$GNGSA,",tempStr)
              self.sGSA.data[i].Mode = self.get_sth_front_string(",",tempStr)
              tempStr =self.remove_sth_string(",",tempStr)
              self.sGSA.data[i].FixStatus = self.get_sth_front_string(",",tempStr)
              tempStr =self.remove_sth_string(",",tempStr)
              for j in range(12):
                self.sGSA.data[i].Statellite_CH[j] = self.get_sth_front_string(",",tempStr)
                tempStr=self.remove_sth_string(",",tempStr)
              self.sGSA.data[i].PDOP = self.get_sth_front_string(",",tempStr)
              tempStr=self.remove_sth_string(",",tempStr)
              self.sGSA.data[i].HDOP = self.get_sth_front_string(",",tempStr)
              tempStr=self.remove_sth_string(",",tempStr)
              self.sGSA.data[i].VDOP = self.get_sth_front_string(",",tempStr)
              tempStr=self.remove_sth_string(",",tempStr)
              self.sGSA.data[i].GNSS_SystemID = self.get_sth_front_string("*",tempStr)
              for j in range(12):
                if len(self.sGSA.data[i].Statellite_CH[j]) == 0:
                  self.sGSA.data[i].Statellite_CH[j] = "N/A"
              Data=self.get_rec_data_for_num(3+i) 
              if Data != None : 
                tempStr  =Data.data
              else :
                return             
          self.check_use()
        elif cmd == "\"NMEA/GLL\"":
          tempStr=self.remove_sth_string("$GNGLL,",tempStr)
          self.sGLL.LatitudeVal=self.get_sth_front_string(",",tempStr)
          tempStr=self.remove_sth_string(",",tempStr)
          self.sGLL.LatitudeDir=self.get_sth_front_string(",",tempStr)
          tempStr=self.remove_sth_string(",",tempStr)
          self.sGLL.LongitudeVal=self.get_sth_front_string(",",tempStr)
          tempStr=self.remove_sth_string(",",tempStr)
          self.sGLL.LongitudeDir=self.get_sth_front_string(",",tempStr)
          tempStr=self.remove_sth_string(",",tempStr)
          self.sGLL.UTC_Time=self.get_sth_front_string(",",tempStr)
          tempStr=self.remove_sth_string(",",tempStr)
          self.sGLL.DataStatus=self.get_sth_front_string(",",tempStr)
          tempStr=self.remove_sth_string(",",tempStr)
          self.sGLL.PositionMode=self.get_sth_front_string("*",tempStr)                                        
        else:
          print("error")
    else :
      self.get_QGNSSRD("\"NMEA/RMC\"")
      self.sGGNS.LatitudeVal = self.Longitude_conversion(self.sRMC.LatitudeVal)
      self.sGGNS.LatitudeDir = self.sRMC.LatitudeDir
      self.sGGNS.LongitudeVal =self.Longitude_conversion(self.sRMC.LongitudeVal)
      self.sGGNS.LongitudeDir=self.sRMC.LongitudeDir
    
      self.get_QGNSSRD("\"NMEA/VTG\"")
      if self.sVTG.GroundCourse_Kmh !=None:
        self.sGGNS.Speed = float(self.sVTG.GroundCourse_Kmh)
      '''if self.sVTG.GroundCourse_True != None :
        self.sGGNS.Heading =float(self.sVTG.GroundCourse_True)'''
  
      self.get_QGNSSRD("\"NMEA/GGA\"")
      if self.sGGA.Altitude !=None:
        self.sGGNS.Altitude = float(self.sGGA.Altitude)
  
      self.get_QGNSSRD("\"NMEA/GSA\"")
      self.sGGNS.PDOP = self.sGSA.data[0].PDOP 
      self.sGGNS.HDOP = self.sGSA.data[0].HDOP 
      self.sGGNS.VDOP = self.sGSA.data[0].VDOP 
      if self.sGSA.data[0].FixStatus == "2":
        self.sGGNS.FixStatus = "2D fixed"
      elif self.sGSA.data[0].FixStatus == "3" :
        self.sGGNS.FixStatus = "3D fixed" 
      else:
        self.sGGNS.FixStatus = "No fix" 
      self.sSAT.USE=0   
      self.get_QGNSSRD("\"NMEA/GSV\"")
      for i in range(self.sSAT.NUM):
        if self.sSAT.data[i].Status=="Y":
          self.sSAT.USE+=1;
    
  def Longitude_conversion(self,strdata):
    '''
      @brief 从所有的卫星信息中分离出纬度信息
      @param strdata 原始的卫星数据
      @return 分离后的数据
    '''
    tempStr = strdata
    temp=0
    if tempStr !=None :
      if tempStr==self.sRMC.LatitudeVal:
        temp = int(tempStr[0:2])  
        tempStr = tempStr[2:len(tempStr)]
        temp += int(tempStr[0:2])*10.0/60.0/10.0
        tempStr = tempStr[3:len(tempStr)]
        temp += int(tempStr[0:4])*1.0/60.0/10000.0
      elif tempStr== self.sRMC.LongitudeVal:
        temp = int(tempStr[0:3])
        tempStr = tempStr[3:len(tempStr)]
        temp += int(tempStr[0:2])*10.0/60.0/10.0
        tempStr = tempStr[3:len(tempStr)]
        temp += int(tempStr[0:4])*1.0/60.0/10000.0
      else:
        print("error")
    return float(temp)  

class DFRobot_BC20_Serial(DFRobot_BC20):
  '''
    @brief 串口通信类
  '''
  def __init__(self):
    if ser.isOpen() is False:
      ser.Open()
    super(DFRobot_BC20_Serial, self).__init__()  
        
  def available(self):
    '''
      @brief 判断模组是否有数据返回
      @return bool类型
      @retval 1 有数据返回
      @retval 0 没有数据返回
    '''
    if ser.inWaiting() !=0:
      return True
    return False
  
  def send_cmd(self,CMD,arg=""):
    '''
      @brief 主控向模组发送数据，由子类来具体实现
      @param str
      @param CMD
    '''
    if arg=="":
      if(len(CMD)>0) is True:
        ser.write("AT+"+CMD+"\r\n")
      else:
        ser.write("AT\r\n")
    else:
        ser.write("AT+"+CMD+"="+arg+"\r\n")
    time.sleep(0.5)    
  
  def read_data(self,timeout):
    '''
      @brief 从模组获取数据
    '''
    recv=""
    ltime=int(round(time.time() * 1000))
    while(int(round(time.time() * 1000))-ltime)<=timeout:
      count = ser.inWaiting()
      if count != 0:
        recv += ser.read(count)
        if recv.find("OK\r\n")!= -1:
          break   
    return  recv        
     
  def recevice_at_cmd(self,timeout):
    '''
      @brief 从模组获取数据
      @param timeout 持续时间内一直读取
    '''
    ID=0
    recv=""
    ltime=int(round(time.time() * 1000))
    while((int(round(time.time() * 1000))-ltime)<=timeout):
      count = ser.inWaiting()
      if count != 0:
        recv += ser.read(count)
        if recv.find("OK\r\n")!= -1:
          break
    if len(recv)>0:     
      tempInt=recv.find("\r\n")
      while (tempInt >= 0):
        if tempInt != -1:
          self.enqueue(ID,recv[0:tempInt+2])
          recv=recv[tempInt+2:len(recv)]
          ID +=1
        tempInt=recv.find("\r\n")  
      
class DFRobot_BC20_IIC(DFRobot_BC20): 
  '''
    @brief IIC通信类
  '''
  def __init__(self,addr):
    self._addr = addr
    self.i2c = smbus.SMBus(1)
    super(DFRobot_BC20_IIC, self).__init__()  
  def BC20_get_regs(self,reg,lenth):
    '''
      @brief 从模组获取数据
    '''
    try:  
      rslt=[]
      for i in range(lenth):
        rslt.append(0)
      for i in range(lenth):  
        rslt[i] = self.i2c.read_byte_data(self._addr,reg+i)  
      return rslt
    except:
      return [0]         
    
  def BC20_set_regs(self,reg,data):
    '''
      @brief 主控向模组发送数据，由子类来具体实现
      @param reg 寄存器地址
      @param data 待写入的数据
    '''
    print(data)
    try:
      if data != None:
        data=[ord(c) for c in data]
        if len(data)>31:
          for i in range(len(data)):  
            self.i2c.write_byte_data(self._addr,reg,data[i])
        else :
          self.i2c.write_i2c_block_data(self._addr,reg,data)     
    except:
      print("ERROR!")
      
  def available(self):
    '''
      @brief 判断模组是否有数据返回
      @return bool类型
      @retval 1 有数据返回
      @retval 0 没有数据返回
    '''
    recv=self.BC20_get_regs(0x00,1)
    if recv[0]>0:
      return True
    return False

  def send_cmd(self,CMD,arg=""): 
    '''
      @brief 主控向模组发送数据，由子类来具体实现
      @param str
      @param CMD
    '''
    if arg=="":
      if(len(CMD)>0) is True:
        temp="AT+"+CMD+"\r\n"
        self.BC20_set_regs(0x00,temp)
      else:
        temp="AT\r\n"
        self.BC20_set_regs(0x00,temp)
    else:
      temp="AT+"+CMD+"="+arg+"\r\n"
      self.BC20_set_regs(0x00,temp)  

  def read_data(self,timeout):
    '''
      @brief 从模组获取数据
    '''
    recv=""
    ltime=int(round(time.time() * 1000))
    while((int(round(time.time() * 1000))-ltime)<=timeout):
      count = self.BC20_get_regs(0x00,1)
      if count[0] != 0:
        Recv = self.BC20_get_regs(0x01,count[0])
        recv += str(bytearray(Recv))           
        if recv.find("OK\r\n")!= -1:
          break
    return  recv 
 
  def recevice_at_cmd(self,timeout):
    '''
      @brief 从模组获取数据
      @param timeout 持续时间内一直读取
    '''
    ID=0
    recv=""
    ltime=int(round(time.time() * 1000))
    while((int(round(time.time() * 1000))-ltime)<=timeout):
      count = self.BC20_get_regs(0x00,1)
      if count[0] != 0: 
        Recv = self.BC20_get_regs(0x01,count[0])
        recv += str(bytearray(Recv))         
        if recv.find("OK\r\n")!= -1:
          break
    if len(recv)>0:
      if recv.find("+IP:") != -1:
        return  
      tempInt=recv.find("\r\n")
      while (tempInt >= 0):
        if tempInt != -1:
          self.enqueue(ID,recv[0:tempInt+2])
          recv=recv[tempInt+2:len(recv)]
          ID +=1
        tempInt=recv.find("\r\n")      
       
             