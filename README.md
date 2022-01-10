# DFRobot_BC20_Gravity
- [中文版](./README_CN.md)

This Gravity: I2C & UART BC20 NB-IoT & GNSS communication module embraces NB-IoT low-power cellular communication and GPS/BeiDou precise positioning function. As long as the device is located in the area covered by  NB-IoT signal, the data collected by the development board or the device can be easily uploaded into the cloud, no matter indoor or outdoor. This module can also be remotely controlled by sending commands through the cloud, realizing "IOT" through communication and control between the cloud and the real device. It is especially applicable to the environmental monitoring station, bike-sharing, vehicle positioning tracker, and other outdoor IoT application scenarios.

Besides, the equipped GPS/BeiDou positioning function can help obtain precise geographical coordinates and timing information and monitor the device's physical location in real-time by placing the positioning antenna outdoors. Users can visually know the module operating status through the onboard RGB indicator. To work well with general Arduino, micro:bit, control board, Raspberry Pi, and other types of 3.3V/5V development boards, this module employs Gravity I2C & UART standard interface and supports all kinds of development boards that users generally used.

![正反面svg效果图](./resources/images/TEL0130.png)

## Product Link (https://www.dfrobot.com/)

  SKU: TEL0130

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

This library provides the acquisition and parsing of satellite data, which contains the interpretation and data parsing of GGA, GLL, GSA, GSV, RMC and VTG in GPS & BeiDou satellite data; it also provides DFRobot's EASY-IOT and ALIYUN's IoT communication routines based on MQTT protocol.

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
  /**
   * @fn powerOn
   * @brief Enable NB module
   * @return Bool type, indicate returning init status
   * @retval 1 Succeeded
   * @retval 0 Failed
   */
  bool powerOn(void);

  /**
   * @fn configKeepalive
   * @brief 配置心跳包超时发送时间
   * @return Bool type, indicate the status of configuring keepalive time
   * @retval 1 Succeeded
   * @retval 0 Failed
   */
  bool configKeepalive(char* alivetime);

  /**
   * @fn checkBC20
   * @brief Check whether BC20 exists
   * @return Bool type, indicate BC20 existing status
   * @retval 1 Existed
   * @retval 0 Not exist
   */
  bool checkBC20(void);

  /**
   * @fn checkStmStauts
   * @brief Check whether STM32 exists
   * @return Bool type, indicate STM32 existing status
   * @retval 1 Existed
   * @retval 0 Not exist
   */
  bool checkStmStauts(void);

  /**
   * @fn clearGPS
   * @brief Clear the GPS information stored in RAM
   */
  void clearGPS(void);

  /**
   * @fn checkNBCard
   * @brief Check whether NB card exists
   * @return Bool type, indicate STM32 existing status
   * @retval 1 Existed
   * @retval 0 Not exist
   */
  bool checkNBCard(void);

  /**
   * @fn getSQ
   * @brief Get the current NB network signal quality
   */
  void getSQ(void);

  /**
   * @fn getGSN
   * @brief Get IMEI information
   */
  void getGSN(uint8_t cmd=0);

  /**
   * @fn getGATT
   * @brief Check whether the device is connected to the nearby NB base station
   * @return uint8_t type, get the module connection status
   * @retval 1 Connected
   * @retval 0 Connecting
   */
  uint8_t getGATT(void);

  /**
   * @fn getIMI
   * @brief Get IMSI
   * @return uint8_t * type, the pointer to identity array
   */
  uint8_t *getIMI(void);

  /**
   * @fn getCLK
   * @brief Get the current network time
   * @return String type, the time is output as a character string
   */
  String getCLK(void);

  /**
   * @fn rest
   * @brief Module soft reset
   * @return Bool type, indicate whether the reset succeeded
   * @retval 1 Succeeded
   * @retval 0 Failed
   */
  bool rest(uint8_t mode = 1);

  /**
   * @fn getQCCID
   * @brief get USIM card identification number
   * @return String type, USIM card identification number
   */
  String getQCCID(void);

  /*!
   * @fn getQCCID
   * @brief Set low-power mode
   * @param mode
   * @n      0 Disable Sleep Mode.
   * @n      1 Enable light sleep and deep sleep, wakeup by PSM_EINT (Falling Edge).
   * @n      2 Enable light sleep only, wakeup by Main UART.
   * @return Bool type
   * @retval 1 Succeeded
   * @retval 0 Failed
   */
  bool setQSCLK(uint8_t mode);

  /*!
   * @fn getQGNSSC
   * @brief Get GNSS enabling status
   * @return uint8_t type
   * @retval 1 Enabled
   * @retval 0 Disabled
   */
  uint8_t getQGNSSC(void);

  /*!
   * @fn setQGNSSC
   * @brief Set whether to enable GNSS
   * @param mode
   * @n 	1 Enabled
   * @n 	0 Disabled
   * @return Bool type
   * @retval 1 Enabled
   * @retval 0 Disabled
   */
  bool setQGNSSC(uint8_t mode);

  /*!
   * @fn getQGNSSRD
   * @brief Get all the GNSS information
   * @return uint8_t type
   * @retval 1 The getting succeeded
   * @retval 0 The getting failed
   */
  uint8_t getQGNSSRD(void);

  /*!
   * @fn getQGNSSRD2
   * @brief Get all the GNSS information (designed for boards with smaller RAM like Arduino and UNO)
   * @return uint8_t type
   * @retval 1 The getting succeeded
   * @retval 0 The getting failed
   */
  uint8_t getQGNSSRD2(void);

  /*!
   * @fn getQGNSSRD
   * @brief Get the GNSS information of one type
   * @param sth
   * @n		 NMEA_GGA
   * @n		 NMEA_GLL
   * @n		 NMEA_GSA
   * @n		 NMEA_GSV
   * @n		 NMEA_RMC
   * @n		 NMEA_VTG
   * @return Bool type
   * @retval 1 The getting succeeded
   * @retval 0 The getting failed
   */
  bool getQGNSSRD(char* sth);

  /**
   * @fn setAliyunserver
   * @brief Set information about Aliyun connection
   * @param ProductKey
   * @param IPAddress
   * @param port
   * @param connectID
   * @return Bool type
   * @retval 1 The setting succeeded
   * @retval 0 The setting failed
   */
  bool setAliyunserver(char*ProductKey,char* IPAddress,char* port,char connectID = '0');

  /**
   * @fn connect_Aliyun
   * @brief Connect to Aliyun
   * @param ProductKey
   * @param DeviceName
   * @param DeviceSecret
   * @return Bool type
   * @retval 1 The connecting succeeded
   * @retval 0 The connecting failed
   */
  bool connect_Aliyun(char* ProductKey,char* DeviceName,char* DeviceSecret);

  /**
   * @fn openMQTT
   * @brief Open MQTT connecting channel
   * @param connectID
   * @param Server
   * @param Port
   * @return Bool type
   * @retval 1 Opening succeeded
   * @retval 0 Opening failed
   */
  bool openMQTT(char connectID, char* Server, char* Port);

  /**
   * @fn closeMQTT
   * @brief Close MQTT connecting channel
   * @param connectID
   * @return Bool type
   * @retval 1 Closing succeeded
   * @retval 0 Closing failed
   */
  bool closeMQTT(uint8_t connectID);

  /**
   * @fn setServer
   * @brief Set MQTT server information
   * @param IPAddress
   * @param port
   * @param connectID
   * @return Bool type
   * @retval 1 The setting succeeded
   * @retval 0 The setting failed
   */
  bool setServer(char* IPAddress,char* port,char connectID = '0');

  /**
   * @fn connected
   * @brief Whether the device is connected to the server
   * @return Bool type
   * @retval 1 Connected
   * @retval 0 Not connected
   */
  bool connected(void);

  /**
   * @fn connectServer
   * @brief Connect to server
   * @param connectID
   * @param clientID
   * @param UserName
   * @param PassWord
   * @return Bool type
   * @retval 1 The connecting succeeded
   * @retval 0 The connecting failed
   */
  bool connectServer(char connectID, char* clientID, char* UserName, char* PassWord);

  /**
   * @fn connect
   * @brief Try to connect to MQTT
   * @param clientID
   * @param username
   * @param password
   * @param connectID
   * @return Bool type
   * @retval 1 The connecting succeeded
   * @retval 0 The connecting failed
   */
  bool connect(char * clientID, char * username,char * password,char connectID ='0');

  /**
   * @fn getQMTCONN
   * @brief Used to detect the connection between the device and the server
   * @return Bool type
   * @retval 1 The getting succeeded
   * @retval 0 The getting failed
   */
  bool getQMTCONN(void);

  /**
   * @fn subTopic
   * @brief Subscribe MQTT information
   * @param connectID
   * @param msgID
   * @param topic
   * @param qos
   * @return Bool type
   * @retval 1 The subscription succeeded
   * @retval 0 The subscription failed
   */
  bool subTopic(char connectID, char msgID, char* topic, char qos);

  /**
   * @fn publish
   * @brief 发布MQTT信息
   * @param topic
   * @param msg
   * @return bool类型
   * @retval 1 发布成功
   * @retval 0 发布失败
   */
  bool publish(char* topic,char* msg);

  /**
   * @fn pubMessage
   * @brief 发布MQTT信息
   * @param connectID
   * @param msgID
   * @param qos
   * @param retain
   * @param topic
   * @param msg
   * @return bool类型
   * @retval 1 发布成功
   * @retval 0 发布失败
   */
  bool pubMessage(char connectID,char msgID, char qos, char retain, char* topic, char* msg);

  /**
   * @fn setCallback
   * @brief 设置订阅模式下MQTT信息的回调函数
   */
  void setCallback(void (*call)(char*, uint8_t*, unsigned int));

  /**
   * @fn loop
   * @brief 订阅模式下循环接收数据
   */
  void loop(void);

  /**
   * @fn configSleepMode
   * @brief 配置BC20模块进入睡眠模式
   * @param mode
   * @n     eSleepMode_Disable,
   * @n     eSleepMode_DeepSleep,
   * @n     eSleepMode_Light
   * @return bool类型
   * @retval 1 发布成功
   * @retval 0 发布失败
   */
  bool configSleepMode(eSleepMode_t mode);

  /**
   * @fn BC20Wakeup
   * @brief 唤醒BC20模块
   * @return bool类型
   * @retval 1 唤醒成功
   * @retval 0 唤醒失败
   */
  bool BC20Wakeup(void);

  /**
   * @fn setPSMMode
   * @brief 设置BC20进入PSM模式
   * @param mode
   * @n     ePSM_OFF
   * @n     ePSM_ON
   * @n     ePSM_OFF_ResetParam
   * @return bool类型
   * @retval 1 唤醒成功
   * @retval 0 唤醒失败
   */
  bool setPSMMode(ePSM_t status);

  /**
   * @fn getNum
   * @brief 获取字符串中的数据段
   * @param str 等待分析的字符串
   * @n     ePSM_OFF
   * @n     ePSM_ON
   * @n     ePSM_OFF_ResetParam
   * @return uint8_t类型
   */
  uint8_t getNum(char* str);

  /**
   * @fn removeSthString
   * @brief 从一串字符中移除某一部分字符串
   * @param sth 等待分析的字符串
   * @param str 作为保留的字符串
   * @return char*类型 剩余的字符串
   */
  char*removeSthString(char* sth, char* str);

  /**
   * @fn removeSthString
   * @brief 从一串字符中移除某一部分字符串
   * @param sth 等待分析的字符串
   * @param str 作为移除的字符串
   * @return String类型 剩余的字符串
   */
  String removeSthString(String sth, String str);

  /**
   * @fn GetSthfrontString
   * @brief 从一串字符中获取某一部分字符串
   * @param sth 等待分析的字符串
   * @param str 作为保留的字符串
   * @return char*类型 保留的字符串
   */
  char* GetSthfrontString(char* sth, char* str);

  /**
   * @fn GetSthfrontString
   * @brief 从一串字符中获取某一部分字符串
   * @param sth 等待分析的字符串
   * @param str 作为保留的字符串
   * @return String类型 保留的字符串
   */
  String GetSthfrontString(String sth, String str);

  /**
   * @fn CheckRecData
   * @brief 检查从NB模组中获取的数据中是否有这个字符串
   * @param str 等待分析的字符串
   * @return bool类型
   * @retval 1 唤醒成功
   * @retval 0 唤醒失败
   */
  bool CheckRecData(char* str);

  /**
   * @fn flushBC20Serial
   * @brief 清空串口收到的所有数据
   */
  void flushBC20Serial(void);

  /**
   * @fn getRecData
   * @brief Gets information about a parameter from the returned data.For example, the CIMI number of the SIM card
   * @param INFO
   */
  void getRecData(uint8_t INFO);

  /**
   * @fn getRecDataforNum
   * @brief 获取指定字符串中哪一个的数据
   * @param num
   * @param buf
   */
  void getRecDataforNum(uint8_t num, uint8_t* &buf);

  /**
   * @fn getRecDataforNum
   * @brief 获取指定字符串中哪一个的数据,并且不检查数据是否规范
   * @param num
   * @param buf
   */
  void getRecDataforNum_NoCheck(uint8_t num, uint8_t* &buf);

  /**
   * @fn getIntforString
   * @brief Send the command and get the number specified in the returned command
   * @param CMD 用来设置在哪个命令后的数字
   * @param basic 等待分析的数据
   * @param n 获取几个数据
   * @return uint8_t类型
   */
  uint8_t getIntforString(String CMD,String basic,uint8_t n);

  /**
   * @fn getSatelliteInformation
   * @brief Given a satellite data, which satellite does it start with, how many satellites do you have
   * @param start 开始的字符
   * @param num 获取几颗卫星的数据
   * @param str 给定的卫星数据字符串
   * @param sys 等待写入flash的数据
   * @return uint8_t类型
   */
  void getSatelliteInformation(uint8_t start, uint8_t num, char* str, char* sys);

  /**
   * @fn LED_ON
   * @brief 打开模组的LED灯
   */
  void LED_ON(void);

  /**
   * @fn LED_OFF
   * @brief 关闭模组的LED灯
   */
  void LED_OFF(void);

  /**
   * @fn changeColor
   * @brief 改变模组的LED灯的颜色
   * @param newColor
   * @n     RED
   * @n     BLUE
   * @n     GREEN
   * @n     YELLOW
   * @n     PURPLE
   * @n     CYAN
   * @n     WHITE
   */
  void changeColor(uint8_t newColor);

  /**
   * @fn controlLED
   * @brief 控制LED灯的所有操作
   * @param chr 控制命令
   */
  void controlLED(char * chr);

  /**
   * @fn controlLED
   * @brief 控制LED灯的所有操作
   * @param chr 控制命令
   */
  void controlLED(String str);

  /**
   * @fn stmLowpower
   * @brief 控制STM32进入低功耗模式
   * @return bool类型
   * @retval 1 唤醒成功
   * @retval 0 唤醒失败
   */
  bool stmLowpower(void);

  /**
   * @fn stmWakeup
   * @brief 控制STM32唤醒
   * @param Awake_Pin 控制触发唤醒STM32的引脚
   * @return bool类型
   * @retval 1 唤醒成功
   * @retval 0 唤醒失败
   */
  bool stmWakeup(uint8_t Awake_Pin);

  /**
   * @fn sendATCMD
   * @brief 主控向模组发送数据，由子类来具体实现
   * @param str 
   */
  virtual void sendATCMD(char* str) =0;

  /**
   * @fn sendATCMD
   * @brief 主控向模组发送数据，由子类来具体实现
   * @param str
   */
  virtual void sendATCMD(String str) =0;

  /**
   * @fn sendATCMD
   * @brief 主控向模组发送数据，由子类来具体实现
   * @param num
   */
  virtual void sendATCMD(uint8_t num) =0;

  /**
   * @fn sendATCMD
   * @brief 主控向模组发送数据，由子类来具体实现
   * @param str
   * @param num
   */
  virtual void sendATCMD(String str,uint8_t num) =0;

  /**
   * @fn sendATCMD
   * @brief 主控向模组发送数据，由子类来具体实现
   * @param str
   * @param cmd
   */
  virtual void sendATCMD(String str,String cmd) =0;

  /**
   * @fn readData
   * @brief 从模组获取数据
   * @return String类型
   */
  virtual String readData(void) =0;

  /**
   * @fn readData
   * @brief 从模组获取数据
   * @param timeout 持续时间内一直读取
   */
  virtual void receviceATCMD(uint32_t timeout) =0;

  /**
   * @fn sendATCMDBychar
   * @brief 使用字符的方式给模组发送数据
   * @param str 
   */
  virtual void sendATCMDBychar(char str) =0;

  /**
   * @fn available
   * @brief 判断模组是否有数据返回
   * @return bool类型
   * @retval 1 有数据返回
   * @retval 0 没有数据返回
   */
  virtual bool available(void)=0;
  
```  

## Compatibility

主板               | 通过  | 未通过   | 未测试   | 备注
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32           |      √       |              |             | 

## History

- 2021/12/17 - 1.0.0 版本

## Credits

Written by Peng Kaixing(kaixing.peng@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))
