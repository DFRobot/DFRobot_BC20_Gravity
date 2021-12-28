# DFRobot_BC20_Gravity
- [English Version](./README.md)

Gravity：I2C & UART BC20 NB-IoT & GNSS通信模块是具有NB-IoT低功耗蜂窝通信和GPS/BeiDou双星精确定位功能的物联网通信模块。只要设备所在地区在NB-IoT信号覆盖范围内，无论在室内外均可轻松将开发板或设备采集的各类数据上传至云端，当然也可以通过云端发送指令来远程控制设备，实现云端与真实设备的双向通信与控制，实现“物联”，尤其适用于环境监控站、共享单车、车载定位追踪器等户外物联网应用场景。

此外，模块带有GPS/BeiDou双星精确定位功能，只要将定位天线置于室外即可获取精确的地理坐标和授时信息，实时监控设备的物理位置。用户可通过板载RGB指示灯，清晰了解模块的各类工作状态。为了兼容常见的Arduino、micro:bit、掌控和树莓派等各类3.3V/5V开发板，模块还采用了Gravity I2C & UART复合标准接口，并对这些创客用户常用的开发板在软件上作了全面支持。

![正反面svg效果图](./resources/images/TEL0130.png)

## 产品链接(https://www.dfrobot.com/)
  SKU: TEL0130

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性y)
* [历史](#历史)
* [创作者](#创作者)

## 概述

这个库分别提供了对卫星数据的获取和解析，包含GPS和北斗卫星数据中的GGA、GLL、GSA、GSV、RMC、VTG解释以及数据解析；同时提供了包括DFRobot
的EASY—IOT和ALIYUN的基于MQTT协议的物联网通信例程

## 库安装

使用此库前，请首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件夹并在该文件夹中运行演示。

## Methods

```C++
  /**
   * @fn powerOn
   * @brief 使能NB模组
   * @return bool类型，表示返回初始化的状态
   * @retval 1 成功
   * @retval 0 失败
   */
  bool powerOn(void);

  /**
   * @fn configKeepalive
   * @brief 配置心跳包超时发送时间
   * @return bool类型，表示配置心跳时间的状态
   * @retval 1 成功
   * @retval 0 失败
   */
  bool configKeepalive(char* alivetime);

  /**
   * @fn checkBC20
   * @brief 检测BC20是否存在
   * @return bool类型，表示BC20存在的状态
   * @retval 1 存在
   * @retval 0 不存在
   */
  bool checkBC20(void);

  /**
   * @fn checkStmStauts
   * @brief 检测STM32是否存在
   * @return bool类型，表示STM32存在的状态
   * @retval 1 存在
   * @retval 0 不存在
   */
  bool checkStmStauts(void);

  /**
   * @fn clearGPS
   * @brief 清空RAM中的存储的卫星信息
   */
  void clearGPS(void);

  /**
   * @fn checkNBCard
   * @brief 检测NB移动卡是否存在
   * @return bool类型，表示STM32存在的状态
   * @retval 1 存在
   * @retval 0 不存在
   */
  bool checkNBCard(void);

  /**
   * @fn getSQ
   * @brief 获取此时NB网络信号强度
   */
  void getSQ(void);

  /**
   * @fn getGSN
   * @brief 获取国际移动设备识别码信息
   */
  void getGSN(uint8_t cmd=0);

  /**
   * @fn getGATT
   * @brief 检测设备是否已经连接上附近的NB基站
   * @return uint8_t类型，获取模块连接状态
   * @retval 1 已连接
   * @retval 0 正在连接
   */
  uint8_t getGATT(void);

  /**
   * @fn getIMI
   * @brief 获取国际移动用户识别码
   * @return uint8_t *类型，识别码数组的指针
   */
  uint8_t *getIMI(void);

  /**
   * @fn getCLK
   * @brief 获取此时的网络时间
   * @return String类型，时间以字符串的形式输出
   */
  String getCLK(void);

  /**
   * @fn rest
   * @brief 模块软复位
   * @return bool类型，复位操作是否成功
   * @retval 1 成功
   * @retval 0 失败
   */
  bool rest(uint8_t mode = 1);

  /**
   * @fn getQCCID
   * @brief get USIM card identification number
   * @return String类型，USIM card identification number
   */
  String getQCCID(void);

  /*!
   * @fn getQCCID
   * @brief 设置低功耗模式
   * @param mode
   * @n      0 Disable Sleep Mode.
   * @n      1 Enable light sleep and deep sleep, wakeup by PSM_EINT (Falling Edge).
   * @n      2 Enable light sleep only, wakeup by Main UART.
   * @return bool类型
   * @retval 1 成功
   * @retval 0 失败
   */
  bool setQSCLK(uint8_t mode);

  /*!
   * @fn getQGNSSC
   * @brief 获取GNSS是否被打开
   * @return uint8_t类型
   * @retval 1 已经打开
   * @retval 0 没有打开
   */
  uint8_t getQGNSSC(void);

  /*!
   * @fn setQGNSSC
   * @brief 设置GNSS是否打开
   * @param mode
   * @n 	1 打开
   * @n 	0 关闭
   * @return bool类型
   * @retval 1 已经打开
   * @retval 0 没有打开
   */
  bool setQGNSSC(uint8_t mode);

  /*!
   * @fn getQGNSSRD
   * @brief 获取所有的卫星信息
   * @return uint8_t类型
   * @retval 1 获取成功
   * @retval 0 获取失败
   */
  uint8_t getQGNSSRD(void);

  /*!
   * @fn getQGNSSRD2
   * @brief 获取所有的卫星信息（为了arduino uno等RAM空间比较小的特制）
   * @return uint8_t类型
   * @retval 1 获取成功
   * @retval 0 获取失败
   */
  uint8_t getQGNSSRD2(void);

  /*!
   * @fn getQGNSSRD
   * @brief 获取某一种的卫星信息
   * @param sth
   * @n		 NMEA_GGA
   * @n		 NMEA_GLL
   * @n		 NMEA_GSA
   * @n		 NMEA_GSV
   * @n		 NMEA_RMC
   * @n		 NMEA_VTG
   * @return bool类型
   * @retval 1 获取成功
   * @retval 0 获取失败
   */
  bool getQGNSSRD(char* sth);

  /**
   * @fn setAliyunserver
   * @brief 设置阿里云连接的相关信息
   * @param ProductKey
   * @param IPAddress
   * @param port
   * @param connectID
   * @return bool类型
   * @retval 1 设置成功
   * @retval 0 设置失败
   */
  bool setAliyunserver(char*ProductKey,char* IPAddress,char* port,char connectID = '0');

  /**
   * @fn connect_Aliyun
   * @brief 连接阿里云
   * @param ProductKey
   * @param DeviceName
   * @param DeviceSecret
   * @return bool类型
   * @retval 1 连接成功
   * @retval 0 连接失败
   */
  bool connect_Aliyun(char* ProductKey,char* DeviceName,char* DeviceSecret);

  /**
   * @fn openMQTT
   * @brief 打开MQTT连接通道
   * @param connectID
   * @param Server
   * @param Port
   * @return bool类型
   * @retval 1 打开成功
   * @retval 0 打开失败
   */
  bool openMQTT(char connectID, char* Server, char* Port);

  /**
   * @fn closeMQTT
   * @brief 关闭MQTT连接通道
   * @param connectID
   * @return bool类型
   * @retval 1 关闭成功
   * @retval 0 关闭失败
   */
  bool closeMQTT(uint8_t connectID);

  /**
   * @fn setServer
   * @brief 设置MQTT服务器信息
   * @param IPAddress
   * @param port
   * @param connectID
   * @return bool类型
   * @retval 1 设置成功
   * @retval 0 设置失败
   */
  bool setServer(char* IPAddress,char* port,char connectID = '0');

  /**
   * @fn connected
   * @brief 设备是否已经连接服务器
   * @return bool类型
   * @retval 1 已经连接
   * @retval 0 未连接
   */
  bool connected(void);

  /**
   * @fn connectServer
   * @brief 连接服务器
   * @param connectID
   * @param clientID
   * @param UserName
   * @param PassWord
   * @return bool类型
   * @retval 1 连接成功
   * @retval 0 连接失败
   */
  bool connectServer(char connectID, char* clientID, char* UserName, char* PassWord);

  /**
   * @fn connect
   * @brief 开始尝试连接MQTT
   * @param clientID
   * @param username
   * @param password
   * @param connectID
   * @return bool类型
   * @retval 1 连接成功
   * @retval 0 连接失败
   */
  bool connect(char * clientID, char * username,char * password,char connectID ='0');

  /**
   * @fn getQMTCONN
   * @brief Used to detect the connection between the device and the server
   * @return bool类型
   * @retval 1 获取成功
   * @retval 0 获取失败
   */
  bool getQMTCONN(void);

  /**
   * @fn subTopic
   * @brief 订阅MQTT信息
   * @param connectID
   * @param msgID
   * @param topic
   * @param qos
   * @return bool类型
   * @retval 1 订阅成功
   * @retval 0 订阅失败
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

## 兼容性

主板               | 通过  | 未通过   | 未测试   | 备注
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32           |      √       |              |             | 

## 历史

- 2021/12/17 - 1.0.0 版本

## 创作者

Written by Peng Kaixing(kaixing.peng@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))
