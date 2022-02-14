# DFRobot_BC20_Gravity
- [中文版](./README_CN.md)

The Gravity:I2C & UART BC20 NB-IoT & GNSS is an IoT communication module with NB-IoT low-power cellular communication and GPS/BeiDou precise positioning functions. As long as your device is within the NB-IoT signal converage area, the data collected by the development board or the device can be easily uploaded into the cloud whether it is indoor or outdoor. This module supports the bidirectional communication and control between cloud and real device by sending commands from cloud to remotely control device, by which to realize "connecting things". It is especially applicable to the environmental monitoring station, bike-sharing, vehicle positioning tracker, and other outdoor IoT application scenarios.

Besides, the equipped GPS/BeiDou dual mode positioning function can help obtain precise geographical coordinates and timing information so as to monitor the device's physical location in real-time when the positioning antenna is placed outdoor. The onboard RGB indicator provides users with visual device working status. The module works well with 3.3V/5V development boards like Arduino, micro:bit, control board, Raspberry Pi, etc. It employs Gravity I2C & UART standard interface and supports commonly-used development boards in software.

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

This library provides the examples of the acquisition and parsing of satellite data, which contains the interpretation and data parsing of GGA, GLL, GSA, GSV, RMC and VTG in GPS & BeiDou satellite data; it also provides DFRobot's EASY-IOT and ALIYUN's IoT communication examples based on MQTT protocol.

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
   * @brief Configure keepalive packet sending interval time
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
   * @return Bool type, indicate NB card existing status
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
   * @brief Get IMEI number information
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
   * @brief Get IMSI code
   * @return uint8_t * type, the pointer to identity code array
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
   * @brief Get GNSS status
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
   * @retval 1 Getting data succeeded
   * @retval 0 Getting data failed
   */
  uint8_t getQGNSSRD(void);

  /*!
   * @fn getQGNSSRD2
   * @brief Get all the GNSS information(designed for boards with smaller RAM like Arduino UNO, etc.)
   * @return uint8_t type
   * @retval 1 Getting data succeeded
   * @retval 0 Getting data failed
   */
  uint8_t getQGNSSRD2(void);

  /*!
   * @fn getQGNSSRD
   * @brief Get one type of satellite information
   * @param sth
   * @n		 NMEA_GGA
   * @n		 NMEA_GLL
   * @n		 NMEA_GSA
   * @n		 NMEA_GSV
   * @n		 NMEA_RMC
   * @n		 NMEA_VTG
   * @return Bool type
   * @retval 1 Getting data succeeded
   * @retval 0 Getting data failed
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
   * @brief Open MQTT connection channel
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
   * @brief Close MQTT connection channel
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
   * @brief Publish MQTT message
   * @param topic
   * @param msg
   * @return Bool type
   * @retval 1 The publishing succeeded
   * @retval 0 The publishing failed
   */
  bool publish(char* topic,char* msg);

  /**
   * @fn pubMessage
   * @brief Publish MQTT message
   * @param connectID
   * @param msgID
   * @param qos
   * @param retain
   * @param topic
   * @param msg
   * @return Bool type
   * @retval 1 The publishing succeeded
   * @retval 0 The publishing failed
   */
  bool pubMessage(char connectID,char msgID, char qos, char retain, char* topic, char* msg);

  /**
   * @fn setCallback
   * @brief Set call back function of MQTT message in subscription mode
   */
  void setCallback(void (*call)(char*, uint8_t*, unsigned int));

  /**
   * @fn loop
   * @brief Receive data on a loop in subscription mode
   */
  void loop(void);

  /**
   * @fn configSleepMode
   * @brief Set BC20 module sleep mode
   * @param mode
   * @n     eSleepMode_Disable,
   * @n     eSleepMode_DeepSleep,
   * @n     eSleepMode_Light
   * @return Bool type
   * @retval 1 Succeeded
   * @retval 0 Failed
   */
  bool configSleepMode(eSleepMode_t mode);

  /**
   * @fn BC20Wakeup
   * @brief Wake up BC20 module
   * @return Bool type
   * @retval 1 The waking up succeeded
   * @retval 0 The waking up failed
   */
  bool BC20Wakeup(void);

  /**
   * @fn setPSMMode
   * @brief Set BC20 to enter PSM mode
   * @param mode
   * @n     ePSM_OFF
   * @n     ePSM_ON
   * @n     ePSM_OFF_ResetParam
   * @return Bool type
   * @retval 1 The setting succeeded
   * @retval 0 The setting failed
   */
  bool setPSMMode(ePSM_t status);

  /**
   * @fn getNum
   * @brief Get the data segment in a character string
   * @param str The character string to be analyzed
   * @n     ePSM_OFF
   * @n     ePSM_ON
   * @n     ePSM_OFF_ResetParam
   * @return uint8_t type
   */
  uint8_t getNum(char* str);

  /**
   * @fn removeSthString
   * @brief Remove sth from a char string 
   * @param sth The character string to be analyzed
   * @param str The removed character string
   * @return char* type, character string remained
   */
  char*removeSthString(char* sth, char* str);

  /**
   * @fn removeSthString
   * @brief Remove sth from a char string
   * @param sth The character string to be analyzed
   * @param str The removed character string
   * @return String type, character string remained
   */
  String removeSthString(String sth, String str);

  /**
   * @fn GetSthfrontString
   * @brief Get sth from a char string 
   * @param sth The character string to be analyzed
   * @param str The Reserved character string
   * @return char* type, character string reserved
   */
  char* GetSthfrontString(char* sth, char* str);

  /**
   * @fn GetSthfrontString
   * @brief Get sth from a char string 
   * @param sth The character string to be analyzed
   * @param str The reserved character string
   * @return String type, character string reserved 
   */
  String GetSthfrontString(String sth, String str);

  /**
   * @fn CheckRecData
   * @brief Check whether the character string is present in the data obtained from NB module
   * @param str The character string to be analyzed
   * @return Bool type
   * @retval 1 Existed
   * @retval 0 Not exist
   */
  bool CheckRecData(char* str);

  /**
   * @fn flushBC20Serial
   * @brief Clear all the data that the serial port received
   */
  void flushBC20Serial(void);

  /**
   * @fn getRecData
   * @brief Gets information about a parameter from the returned data. For example, the CIMI number of the SIM card
   * @param INFO
   */
  void getRecData(uint8_t INFO);

  /**
   * @fn getRecDataforNum
   * @brief Get data from a specified character string
   * @param num
   * @param buf
   */
  void getRecDataforNum(uint8_t num, uint8_t* &buf);

  /**
   * @fn getRecDataforNum
   * @brief Get data from a specified character string, and not check whether the data is standardized
   * @param num
   * @param buf
   */
  void getRecDataforNum_NoCheck(uint8_t num, uint8_t* &buf);

  /**
   * @fn getIntforString
   * @brief Send the command and get the number specified in the returned command
   * @param CMD Set command to be parsed 
   * @param basic The data to be analyzed
   * @param n The number of data to be obtained 
   * @return uint8_t type
   */
  uint8_t getIntforString(String CMD,String basic,uint8_t n);

  /**
   * @fn getSatelliteInformation
   * @brief Given a satellite data, which satellite does it start with, how many satellites do you have
   * @param start The starting character
   * @param num The number of satellites to get data from 
   * @param str Data character string of the given satellite 
   * @param sys Data to be written to Flash 
   * @return uint8_t type
   */
  void getSatelliteInformation(uint8_t start, uint8_t num, char* str, char* sys);

  /**
   * @fn LED_ON
   * @brief Turn on LED of the module
   */
  void LED_ON(void);

  /**
   * @fn LED_OFF
   * @brief Turn off LED of the module
   */
  void LED_OFF(void);

  /**
   * @fn changeColor
   * @brief Change the LED color of the module
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
   * @brief Control LED totally
   * @param chr Control command
   */
  void controlLED(char * chr);

  /**
   * @fn controlLED
   * @brief Control LED totally
   * @param chr Control command
   */
  void controlLED(String str);

  /**
   * @fn stmLowpower
   * @brief Control STM32 to enter low-power mode
   * @return Bool type
   * @retval 1 Succeeded
   * @retval 0 Failed
   */
  bool stmLowpower(void);

  /**
   * @fn stmWakeup
   * @brief Control STM32 waking up
   * @param Awake_Pin Control the pin triggering STM32 waking-up
   * @return Bool type
   * @retval 1 The waking-up succeeded
   * @retval 0 The waking-up failed
   */
  bool stmWakeup(uint8_t Awake_Pin);

  /**
   * @fn sendATCMD
   * @brief The MCU send data to the module, implemented by subclass
   * @param str 
   */
  virtual void sendATCMD(char* str) =0;

  /**
   * @fn sendATCMD
   * @brief The MCU send data to the module, implemented by subclass
   * @param str
   */
  virtual void sendATCMD(String str) =0;

  /**
   * @fn sendATCMD
   * @brief The MCU send data to the module, implemented by subclass
   * @param num
   */
  virtual void sendATCMD(uint8_t num) =0;

  /**
   * @fn sendATCMD
   * @brief The MCU send data to the module, implemented by subclass
   * @param str
   * @param num
   */
  virtual void sendATCMD(String str,uint8_t num) =0;

  /**
   * @fn sendATCMD
   * @brief The MCU send data to the module, implemented by subclass
   * @param str
   * @param cmd
   */
  virtual void sendATCMD(String str,String cmd) =0;

  /**
   * @fn readData
   * @brief Get data from the module
   * @return String type
   */
  virtual String readData(void) =0;

  /**
   * @fn readData
   * @brief Get data from the module
   * @param timeout Read repeatedly within the duration
   */
  virtual void receviceATCMD(uint32_t timeout) =0;

  /**
   * @fn sendATCMDBychar
   * @brief Send char data to the module
   * @param str 
   */
  virtual void sendATCMDBychar(char str) =0;

  /**
   * @fn available
   * @brief Check whether there is available data returned from module
   * @return Bool type
   * @retval 1 Yes
   * @retval 0 No
   */
  virtual bool available(void)=0;
  
```  

## Compatibility

MCU               | Work Well  | Work Wrong   | Untested   | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32           |      √       |              |             | 

## History

- 2021/12/17 - 1.0.0 version

## Credits

Written by Peng Kaixing(kaixing.peng@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))
