/*!
 * @file DFRobot_BC20_Gravity.h
 * @brief 这是一个基于MQTT的物联网和卫星信息的综合模块
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      [PengKaixing](kaixing.peng@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-16
 * @url https://github.com/DFRobot/DFRobot_BC20_Gravity
 */

#ifndef __DFROBOT_BC20__
#define __DFROBOT_BC20__
#define OPENDBG    1
#include "Arduino.h"
#include "DFRobot_BC20AT.h"
#include "DFRobot_queue.h"
#ifndef ARDUINO_ESP32_DEV
#include "SoftwareSerial.h"
#endif
#include "Wire.h"
#include "EEPROM.h"
#define DBG(sth)   Serial.print("DBG:");Serial.print(__LINE__);Serial.print("--------");Serial.println(sth)
#define ON   1
#define OFF  0
#define SN      0
#define IMEI    1
#define IMEISV  2
#define SVN     3
extern char *ret;
/**
 * @struct sSIMCard_t
 * @brief SIM卡IMEI信息
 */
typedef struct
{
  uint8_t *IMEI_NUM;
}sSIMCard_t;
extern sSIMCard_t sSIMCard;

/**
 * @struct sRecData_t
 * @brief 模块返回数据
 */
typedef struct
{
  uint8_t dataNum;
}sRecData_t;
extern sRecData_t sRecData;

/**
 * @struct sSQ_t
 * @brief MQTT信号强度
 */
typedef struct
{
  uint8_t rssi;
  uint8_t ber;
}sSQ_t;
extern sSQ_t sSQ;

/**
 * @struct sGSN_t
 * @brief 国际移动设备信息
 */
typedef struct
{
  String sn;
  String imei;
  char* imeisv;
  char* svn;
}sGSN_t;
extern sGSN_t sGSN;

/**
 * @struct sGLL_t
 * @brief MQTT信息
 */
typedef struct
{
  char *LatitudeVal(void)
  {
    int addr=0;     
    if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
    }
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0);
	}
	char*a=ret; 	
	return a;
  };

  char *LatitudeDir(void)
  {
	int addr=0+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
		ret[i] =(char)EEPROM.read(i+0+11);
	}
	char*a=ret; 	
	return a;
  };

  char *LongitudeVal(void)
  {
    int addr=0+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11);
	}
	char*a=ret; 	
	return a;
  };

  char *LongitudeDir(void)
  {
	int addr=0+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11);
	}
	char*a=ret; 	
	return a;
  };

  char *UTC_Time(void)
  {
    int addr=0+11+11+11+11;     
    if(ret != NULL)
    {
      free(ret);
	  ret = NULL;
    }
    ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };

  char *DataStatus(void)
  {
	int addr=0+11+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };

  char *PositionMode(void)
  {
	int addr=0+11+11+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };		
}sGLL_t;
extern sGLL_t sGLL;

/**
 * @struct sGGA_t
 * @brief GPS信息
 */
typedef struct
{
  char *UTC_Time(void)
  {
    int addr=0;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0);
	}
	char*a=ret; 	
	return a;
  };

  char *LatitudeVal(void)
  {
	int addr=0+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11);
	}
	char*a=ret; 	
	return a;
  };

  char *LatitudeDir(void)
  {
	int addr=0+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11);
	}
	char*a=ret; 	
	return a;
  };

  char *LongitudeVal(void)
  {
	int addr=0+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11);
	}
	char*a=ret; 	
	return a;
  };

  char *LongitudeDir(void)
  {
	int addr=0+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };

  char *Status(void)
  {
	int addr=0+11+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };

  char *StatelliteNum(void)
  {
	int addr=0+11+11+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };

  char *HDOP(void)
  {
	int addr=0+11+11+11+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };

  char *Altitude(void)
  {
	int addr=0+11+11+11+11+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };

  char *GeoID_Separation(void)
  {
	int addr=0+11+11+11+11+11+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11+11+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };

  char *DGPS_Age(void)
  {
	int addr=0+11+11+11+11+11+11+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11+11+11+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };

  char *DGPS_StationID(void)
  {
	int addr=0+11+11+11+11+11+11+11+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11+11+11+11+11+11+11+11);
	}
	char*a=ret; 	
	return a;
	};		
}sGGA_t;
extern sGGA_t sGGA;

struct sGSAD
{
  uint8_t NUM;
  char *Mode(void)
  {
    int addr=NUM*72;     
    if(ret != NULL)
	{
      free(ret);
      ret = NULL;
    }
    ret = (char *)malloc(5);
    memset(ret,'\0',5);
    for(int i = 0; i < 4; i++)
	{
	  ret[i] =(char)EEPROM.read(addr+i);
    }
    char*a=ret; 		
    return a;
  };

  String FixStatus(void)
  {
    int addr=NUM*72+4;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
    ret = (char *)malloc(5);
    memset(ret,'\0',5);
	for(int i = 0; i < 4; i++)
	{
	  ret[i] =(char)EEPROM.read(addr+i);
	}
    char*a=ret;
	if(strcmp(a,"1")==0){
		return "No fix";
	}else if(strcmp(a,"2")==0){
		return "2D fix";
	}else if(strcmp(a,"3")==0){
		return "3D fix";
	}     
  };	

  char *Statellite_CH(int j)
  {
    int addr=NUM*72+4+4+j*4;     
    if(ret != NULL)
	{
      free(ret);
      ret = NULL;
    }
    ret = (char *)malloc(5);
    memset(ret,'\0',5);
    for(int i = 0; i < 4; i++)
	{
      ret[i] =(char)EEPROM.read(addr+i);
    }
    char*a=ret; 		
    return a;
  };	

  char *PDOP(void)
  {
	int addr=NUM*72+4+4+4*12;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
    ret = (char *)malloc(5);
    memset(ret,'\0',5);
    for(int i = 0; i < 4; i++){
	  ret[i] =(char)EEPROM.read(addr+i);
    }
    char*a=ret; 		
    return a;
  };	
  
  char *HDOP(void)
  {
	int addr=NUM*72+4+4+12*4+4;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(5);
	memset(ret,'\0',5);
	for(int i = 0; i < 4; i++)
	{
	  ret[i] =(char)EEPROM.read(addr+i);
	}
	char*a=ret; 		
	return a;
  };

  char *VDOP(void)
  {
	int addr=NUM*72+4+4+12*4+4+4;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(5);
	memset(ret,'\0',5);
	for(int i = 0; i < 4; i++)
	{
	  ret[i] =(char)EEPROM.read(addr+i);
	}
	char*a=ret; 		
	return a;
  };	
  
  String GNSS_SystemID(void)
  {
	int addr=NUM*72+4+4+12*4+4+4+4;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(5);
	memset(ret,'\0',5);
	for(int i = 0; i < 1; i++)
	{
	  ret[i] =(char)EEPROM.read(addr+i);
	}
	char*a=ret; 
    if(strcmp(a,"1"))
	{
	  return("GPS");
	}else if(strcmp(a,"4")){
	  return("BeiDou");
	}else{
	  return a;
	}
  };	
};

/**
 * @struct sGSA_t
 * @brief GSA信息
 */
typedef struct
{
  uint8_t NUM;
  sGSAD data[2];
}sGSA_t;
extern sGSA_t sGSA;

/**
 * @struct sRMC_t
 * @brief RMC信息
 */
typedef struct
{
  char *UTC_Time(void)
  {
	int addr=0;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
		ret[i] =(char)EEPROM.read(i+0);
	}
	char*a=ret; 	
	return a;
  };	
    
  char *DataStatus(void)
  {
	int addr=0+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11);
	}
	char*a=ret; 	
	return a;
  };	

  char *LatitudeVal(void)
  {
	int addr=0+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11);
	}
	char*a=ret; 	
	return a;
  };	

  char *LatitudeDir(void)
  {
	int addr=0+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11);
	}
	char*a=ret; 	
	return a;
  };	

  char *LongitudeVal(void)
  {
	int addr=0+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };	

  char *LongitudeDir(void)
  {
	int addr=0+11+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };	

  char *GroundSpeed(void)
  {
	int addr=0+11+11+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };	

  char *GroundHeading(void)
  {
	int addr=0+11+11+11+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };	

  char *UTC_Date(void)
  {
	int addr=0+11+11+11+11+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };	
    
  char *MagDeclination(void)
  {
	int addr=0+11+11+11+11+11+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11+11+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };	
    
  char *MagDeclinationDir(void)
  {
	int addr=0+11+11+11+11+11+11+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11+11+11+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };	

  char *PositioningMode(void)
  {
	int addr=0+11+11+11+11+11+11+11+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11+11+11+11+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };	

  char *NaviStatus(void)
  {
	int addr=0+11+11+11+11+11+11+11+11+11+11+11+11;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(12);
	memset(ret,'\0',12);
	for(int i = 0; i < 11; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0+11+11+11+11+11+11+11+11+11+11+11+11);
	}
	char*a=ret; 	
	return a;
  };	
}sRMC_t;
extern sRMC_t sRMC;

/**
 * @struct sVTG_t
 * @brief VTG信息
 */
typedef struct
{
  char *GroundCourse_True(void)
  {
	int addr=0;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(6);
	memset(ret,'\0',6);
	for(int i = 0; i < 5; i++)
	{
	  ret[i] =(char)EEPROM.read(i+0);
	}
	char*a=ret; 	
	return a;
  };	

  char *GroundCourse_Mag(void)
  {
	int addr=0+5;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(6);
	memset(ret,'\0',6);
	for(int i = 0; i < 5; i++)
	{
	  ret[i] =(char)EEPROM.read(i+5);
	}
	char*a=ret; 		
	return a;
  };	

  char *GroundCourse_Knots(void)
  {
	int addr=0+5+5;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(6);
	memset(ret,'\0',6);
	for(int i = 0; i < 5; i++)
	{
	  ret[i] =(char)EEPROM.read(i+5+5);
	}
	char*a=ret; 		
	return a;
  };	

  char *GroundCourse_Kmh(void)
  {
	int addr=0+5+5+5;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(6);
	memset(ret,'\0',6);
	for(int i = 0; i < 5; i++)
	{
	  ret[i] =(char)EEPROM.read(i+5+5+5);
	}
	char*a=ret; 		
	return a;
  };	

  char *PositioningMode(void)
  {
	int addr=0+5+5+5+5;     
	if(ret != NULL)
	{
	  free(ret);
	  ret = NULL;
	}
	ret = (char *)malloc(6);
	memset(ret,'\0',6);
	for(int i = 0; i < 5; i++)
	{
	  ret[i] =(char)EEPROM.read(i+5+5+5+5);
	}
	char*a=ret; 		
	return a;
  };	
}sVTG_t;
extern sVTG_t sVTG;

struct sGSV
{
  uint8_t NUM;
  char *PRN(void)
  {
    int addr=NUM*21;     
    if(ret != NULL)
	{
      free(ret);
      ret = NULL;
    }
    ret = (char *)malloc(4);
    memset(ret,'\0',4);
    for(int i = 0; i < 3; i++)
	{
      ret[i] =(char)EEPROM.read(addr+i);
    }
    char*a=ret;      
    return a;
  };
    
  char *Elev(void)
  {
    int addr=(this->NUM)*21+3;     
    if(ret != NULL)
	{
      free(ret);
      ret = NULL;
    }
    ret = (char *)malloc(4);
    memset(ret,'\0',4);
    for(int i = 0; i < 3; i++)
	{
      ret[i] =(char)EEPROM.read(addr+i);
    }
    char*a=ret;      
    return a;
  }; 	

  char *Azim(void)
  {
    int addr=(this->NUM)*21+3+3;     
    if(ret != NULL)
	{
      free(ret);
      ret = NULL;
    }
    ret = (char *)malloc(7);
    memset(ret,'\0',4);
    for(int i = 0; i < 3; i++)
	{
      ret[i] =(char)EEPROM.read(addr+i);
    }
    char*a=ret;      
    return a;
  }; 	

  char *SNR(void)
  {
    int addr=(this->NUM)*21+3+3+3;     
    if(ret != NULL)
	{
      free(ret);
      ret = NULL;
    }
    ret = (char *)malloc(4);
    memset(ret,'\0',4);
    for(int i = 0; i < 3; i++)
	{
      ret[i] =(char)EEPROM.read(addr+i);
    }
    char*a=ret;      
    return a;
  }; 	

  char *Status(void)
  {
    int addr=(this->NUM)*21+3+3+3+3;     
    if(ret != NULL)
	{
      free(ret);
      ret = NULL;
    }
    ret = (char *)malloc(4);
    memset(ret,'\0',4);
    for(int i = 0; i < 3; i++)
	{
      ret[i] =(char)EEPROM.read(addr+i);
    }
    char*a=ret;      
    return a;
  };	  

  char *SYS(void)
  {
    int addr=(this->NUM)*21+3+3+3+3+3;     
    if(ret != NULL)
	{
      free(ret);
      ret = NULL;
    }
    ret = (char *)malloc(7);
    memset(ret,'\0',7);
    for(int i = 0; i < 6; i++)
	{
      ret[i] =(char)EEPROM.read(addr+i);
    }
    char*a=ret;      
    return a;
  };	
};

/**
 * @struct sSAT_t
 * @brief sSAT信息
 */
typedef struct
{
  uint8_t NUM;
  uint8_t USE;
  sGSV data[40];
}sSAT_t;
extern sSAT_t sSAT;

/**
 * @struct sCLK_t
 * @brief CLK信息
 */
typedef struct
{
  uint16_t Year;
  uint8_t  Month;
  uint8_t  Day;
  int  Hour;
  uint8_t  Minute;
  uint8_t  Second;
  char*  Mode;
  int TimeEquation;
}sCLK_t;
extern sCLK_t sCLK;

/**
 * @struct sGGNS_t2
 * @brief GNS信息
 */
typedef struct
{
  uint8_t NUM;
  float LatitudeVal;
  float LongitudeVal;
  float Altitude;
  uint8_t StatelliteNum;
  float HDOP;

  char*LatitudeDir(void)
  {
    return (sGGA.LatitudeDir());
  }

  char*LongitudeDir(void)
  {
    return (sGGA.LongitudeDir());
  }

  String Status(void)
  {
    if(strcmp(sGGA.Status(),"2")){
	  return "DGPS";
	}else if(strcmp(sGGA.Status(),"1")){
	  return "GNSS";
	}else{
	  return "Not fixed";
	}
  }	
}sGGNS_t2;
extern sGGNS_t2 sGGNS2;

struct sGSV2
{
  char* PRN;
  char* Elev;
  char* Azim;
  char* SNR;
  char* Status;
  char* SYS;
};

/**
 * @struct sSAT_t2
 * @brief SAT信息
 */
typedef struct
{
  uint8_t NUM;
  uint8_t USE=0;
  sGSV2 data[40];
}sSAT_t2;
extern sSAT_t2 sSAT2;

/**
 * @struct sGGNS_t
 * @brief GNS信息
 */
typedef struct
{
  uint8_t NUM;	
  float LatitudeVal;
  String LatitudeDir;
  float LongitudeVal;
  String LongitudeDir;
  float Altitude;
  float Speed;
  float Heading;
  String FixStatus;
  String Statellite_CH[2][12];
  String PDOP;
  String HDOP;
  String VDOP;
  uint8_t StatelliteNum;
}sGGNS_t;
extern sGGNS_t sGGNS;

/**
 * @enum eTAUunit_t
 * @brief 时间信息
 */
typedef enum 
{
  eTAUunit_10M,  
  eTAUunit_1H,   
  eTAUunit_10H,  
  eTAUunit_2S,   
  eTAUunit_30S,  
  eTAUunit_1M,   
  eTAUunit_320H, 
  eTAUunit_stop  
} eTAUunit_t;

/**
 * @enum eAcTunit_t
 * @brief 间隔时间信息
 */
typedef enum 
{
  eAcTunit_2S,        
  eAcTunit_1M,        
  eAcTunit_decihours, 
  eAcTunit_stop       
} eAcTunit_t;

/**
 * @enum eeDRXValue_t
 * @brief 间隔时间信息
 */
typedef enum 
{
  eeDRXValue_20_48,  //20.48 seconds
  eeDRXValue_40_96,  //40.96 seconds
  eeDRXValue_81_92,  //81.92 seconds
  eeDRXValue_163_84, //163.84 seconds
  eeDRXValue_327_68, //327.68 seconds
  eeDRXValue_655_36, //655.36 seconds
  eeDRXValue_1310_72,//1310.72 seconds
  eeDRXValue_2621_44,//2621.44 seconds
  eeDRXValue_5242_88,//5242.88 seconds
  eeDRXValue_10485_76//10485.76 seconds
} eeDRXValue_t;

/**
 * @enum eeDRXValue_t
 * @brief GPS间隔时间信息
 */
typedef enum
{
  eNWProvidedValue_20_48,  //20.48 seconds
  eNWProvidedValue_40_96,  //40.96 seconds
  eNWProvidedValue_81_92,  //81.92 seconds
  eNWProvidedValue_163_84, //163.84 seconds
  eNWProvidedValue_327_68, //327.68 seconds
  eNWProvidedValue_655_36, //655.36 seconds
  eNWProvidedValue_1310_72,//1310.72 seconds
  eNWProvidedValue_2621_44,//2621.44 seconds
  eNWProvidedValue_5242_88,//5242.88 seconds
  eNWProvidedValue_10485_76//10485.76 seconds
} eNWProvidedValue_t;

/**
 * @enum ePTWValue_t
 * @brief GPS间隔时间信息
 */
typedef enum 
{
  ePTWValue_2_56, //2.56  seconds
  ePTWValue_5_12, //5.12  seconds
  ePTWValue_7_68, //7.68  seconds
  ePTWValue_10_24,//10.24 seconds
  ePTWValue_12_8, //12.8  seconds
  ePTWValue_15_36,//15.36 seconds
  ePTWValue_17_92,//17.92 seconds
  ePTWValue_20_48,//20.48 seconds
  ePTWValue_23_04,//23.04 seconds
  ePTWValue_25_6, //25.6  seconds
  ePTWValue_28_16,//28.16 seconds
  ePTWValue_30_72,//30.72 seconds
  ePTWValue_33_28,//33.28 seconds
  ePTWValue_35_84,//35.84 seconds
  ePTWValue_38_4, //38.4  seconds
  ePTWValue_40_96 //40.96 seconds
} ePTWValue_t;

/**
 * @enum ePSM_t
 * @brief BC20模块的低功耗
 */
typedef enum 
{
  ePSM_OFF,
  ePSM_ON,
  ePSM_OFF_ResetParam
}ePSM_t;

/**
 * @enum eSleepMode_t
 * @brief BC20模块的睡眠模式
 */
typedef enum 
{
  eSleepMode_Disable,
  eSleepMode_DeepSleep,
  eSleepMode_Light
}eSleepMode_t;

class DFRobot_BC20
{
public:
  String Echo_OFF = SET_ECHO_0;
  String Echo_ON = SET_ECHO_1;
  bool mqttConneced = false;
  DFRobot_BC20(void);
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
   * @fn rest(uint8_t mode = 1)
   * @brief 模块软复位
   * @return bool类型，复位操作是否成功
   * @retval 1 成功
   * @retval 0 失败
   */
  bool rest(uint8_t mode = 1);

  /**
   * @fn getQCCID
   * @brief get USIM card identification number
   * @return String类型
   */
  String getQCCID(void);

  /*!
   * @fn setQSCLK
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
   */
  uint8_t getQGNSSRD2(void);

  /*!
   * @fn getQGNSSRD(char* sth)
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
   * @fn publish(char* topic,char* msg)
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
   * @n     eSleepMode_Disable
   * @n     eSleepMode_DeepSleep 
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
   * @param status
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
   * @fn removeSthString(char* sth, char* str)
   * @brief 从一串字符中移除某一部分字符串
   * @param sth 等待分析的字符串
   * @param str 作为保留的字符串
   * @return char*类型 剩余的字符串
   */
  char*removeSthString(char* sth, char* str);

  /**
   * @fn removeSthString(String sth, String str)
   * @brief 从一串字符中移除某一部分字符串
   * @param sth 等待分析的字符串
   * @param str 作为移除的字符串
   * @return String类型 剩余的字符串
   */
  String removeSthString(String sth, String str);

  /**
   * @fn GetSthfrontString(char* sth, char* str)
   * @brief 从一串字符中获取某一部分字符串
   * @param sth 等待分析的字符串
   * @param str 作为保留的字符串
   * @return char*类型 保留的字符串
   */
  char* GetSthfrontString(char* sth, char* str);

  /**
   * @fn GetSthfrontString(String sth, String str)
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
   * @fn controlLED(char * chr)
   * @brief 控制LED灯的所有操作
   * @param chr 控制命令
   */
  void controlLED(char * chr);

  /**
   * @fn controlLED(String str)
   * @brief 控制LED灯的所有操作
   * @param str 控制命令
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
   * @fn sendATCMD(char* str)
   * @brief 主控向模组发送数据，由子类来具体实现
   * @param str
   */
  virtual void sendATCMD(char* str) =0;

  /**
   * @fn sendATCMD(String str)
   * @brief 主控向模组发送数据，由子类来具体实现
   * @param str
   */
  virtual void sendATCMD(String str) =0;

  /**
   * @fn sendATCMD(uint8_t num)
   * @brief 主控向模组发送数据，由子类来具体实现
   * @param num
   */
  virtual void sendATCMD(uint8_t num) =0;

  /**
   * @fn sendATCMD(String str,uint8_t num)
   * @brief 主控向模组发送数据，由子类来具体实现
   * @param str
   * @param num
   */
  virtual void sendATCMD(String str,uint8_t num) =0;

  /**
   * @fn sendATCMD(String str,String cmd)
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
   * @fn receviceATCMD
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
  char color = 'R';
  private:
  void (*callback)(char*, uint8_t*, unsigned int);
  void (*PSMcallback)(void);
  String _TAUValue = "";
  String _AcTValue = "";
};

class DFRobot_BC20_IIC : public DFRobot_BC20
{
public:
  DFRobot_BC20_IIC(uint8_t addr);
  void sendATCMD(char *str);
  void sendATCMD(String str);
  void sendATCMD(uint8_t num);
  void sendATCMD(String str, uint8_t num);
  void sendATCMD(String str, String cmd);
  String readData(void);
  void receviceATCMD(uint32_t timeout);
  void sendATCMDBychar(char str);
  bool available(void);
private:
  int IIC_addr;
};

class DFRobot_BC20_Serial:public DFRobot_BC20
{
public:
  DFRobot_BC20_Serial(HardwareSerial*SSerial1);
  ~DFRobot_BC20_Serial(void){};
  void sendATCMD(char* str);
  void sendATCMD(String str);
  void sendATCMD(uint8_t num);
  void sendATCMD(String str,uint8_t num);
  void sendATCMD(String str,String cmd);
  String readData(void);
  void receviceATCMD(uint32_t timeout);
  void sendATCMDBychar(char str);
  bool available(void);
private:	
  HardwareSerial*SSerial;
};

#ifndef ARDUINO_ESP32_DEV
class DFRobot_BC20_SW_Serial:public DFRobot_BC20
{
public:
  DFRobot_BC20_SW_Serial(SoftwareSerial* ss);
  void sendATCMD(char* str);
  void sendATCMD(String str);
  void sendATCMD(uint8_t num);
  void sendATCMD(String str,uint8_t num);
  void sendATCMD(String str,String cmd);
  String readData(void);
  void receviceATCMD(uint32_t timeout);
  void sendATCMDBychar(char str);
  bool available(void);
private:
  SoftwareSerial* SSerial;
};
#endif
#endif
