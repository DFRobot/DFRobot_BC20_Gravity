/*!
 * @file DFRobot_BC20_Gravity.h
 * @brief This is an IoT communication module based on MQTT and satellite information.
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      [PengKaixing](kaixing.peng@dfrobot.com)
 * @version  V1.0.0
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
 * @brief IMEI information of SIM card
 */
typedef struct
{
  uint8_t *IMEI_NUM;
}sSIMCard_t;
extern sSIMCard_t sSIMCard;

/**
 * @struct sRecData_t
 * @brief Module return data
 */
typedef struct
{
  uint8_t dataNum;
}sRecData_t;
extern sRecData_t sRecData;

/**
 * @struct sSQ_t
 * @brief MQTT signal quality
 */
typedef struct
{
  uint8_t rssi;
  uint8_t ber;
}sSQ_t;
extern sSQ_t sSQ;

/**
 * @struct sGSN_t
 * @brief IMEI
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
 * @brief MQTT information
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
 * @brief GPS information
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
 * @brief GSA information
 */
typedef struct
{
  uint8_t NUM;
  sGSAD data[2];
}sGSA_t;
extern sGSA_t sGSA;

/**
 * @struct sRMC_t
 * @brief RMC information
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
 * @brief VTG information
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
 * @brief sSAT information
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
 * @brief CLK information
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
 * @brief GNS information
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
 * @brief SAT information
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
 * @brief GNS information
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
 * @brief Time information
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
 * @brief Interval time information
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
 * @brief Interval time information
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
 * @brief GPS interval time information
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
 * @brief GPS interval time information
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
 * @brief Low power consumption of BC20 module
 */
typedef enum 
{
  ePSM_OFF,
  ePSM_ON,
  ePSM_OFF_ResetParam
}ePSM_t;

/**
 * @enum eSleepMode_t
 * @brief Sleep mode of BC20 module
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
   * @return uint8_t *type, the pointer to identity code array
   */
  uint8_t *getIMI(void);

  /**
   * @fn getCLK
   * @brief Get the current network time
   * @return String type, the time is output as a character string
   */
  String getCLK(void);

  /**
   * @fn rest(uint8_t mode = 1)
   * @brief Module soft reset
   * @return Bool type, indicate whether the reset succeeded
   * @retval 1 Succeeded
   * @retval 0 Failed
   */
  bool rest(uint8_t mode = 1);

  /**
   * @fn getQCCID
   * @brief get USIM card identification number
   * @return String type
   */
  String getQCCID(void);

  /*!
   * @fn setQSCLK
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
   * @brief Get all the GNSS information (designed for boards with smaller RAM like Arduino UNO, etc)
   * @return uint8_t type
   */
  uint8_t getQGNSSRD2(void);

  /*!
   * @fn getQGNSSRD(char* sth)
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
   * @brief Set information for Aliyun connection
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
   * @fn publish(char* topic,char* msg)
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
   * @brief Configure BC20 module sleep mode
   * @param mode
   * @n     eSleepMode_Disable
   * @n     eSleepMode_DeepSleep 
   * @n     eSleepMode_Light
   * @return Bool type
   * @retval 1 The config succeeded
   * @retval 0 The config failed
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
   * @param status
   * @n     ePSM_OFF
   * @n     ePSM_ON
   * @n     ePSM_OFF_ResetParam
   * @return Bool type
   * @retval 1 Succeeded
   * @retval 0 Failed
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
   * @fn removeSthString(char* sth, char* str)
   * @brief Remove sth from a char string 
   * @param sth The character string to be analyzed
   * @param str The removed character string
   * @return char*type, character string remained 
   */
  char*removeSthString(char* sth, char* str);

  /**
   * @fn removeSthString(String sth, String str)
   * @brief Remove sth from a char string 
   * @param sth The character string to be analyzed
   * @param str The removed character string
   * @return String type, character string remained
   */
  String removeSthString(String sth, String str);

  /**
   * @fn GetSthfrontString(char* sth, char* str)
   * @brief Get sth from a char string 
   * @param sth The character string to be analyzed
   * @param str Reserved character string
   * @return char*type, reserved character string
   */
  char* GetSthfrontString(char* sth, char* str);

  /**
   * @fn GetSthfrontString(String sth, String str)
   * @brief Get sth from a char string
   * @param sth The character string to be analyzed
   * @param str Reserved character string
   * @return String type, reserved character string
   */
  String GetSthfrontString(String sth, String str);

  /**
   * @fn CheckRecData
   * @brief Check whether the character string is present in the data obtained from NB module
   * @param str The character string to be analyzed
   * @return Bool type
   * @retval 1 Succeeded
   * @retval 0 Failed
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
   * @brief Get data from one specified character string
   * @param num
   * @param buf
   */
  void getRecDataforNum(uint8_t num, uint8_t* &buf);

  /**
   * @fn getRecDataforNum
   * @brief Get data from one specified character string, and check whether the data is standardized
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
   * @fn controlLED(char * chr)
   * @brief Control LED totally
   * @param chr Control command
   */
  void controlLED(char * chr);

  /**
   * @fn controlLED(String str)
   * @brief Control LED totally
   * @param str Control command
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
   * @param Awake_Pin Control the pin triggering STM32 waking up
   * @return Bool type
   * @retval 1 The waking up succeeded
   * @retval 0 The waking up failed
   */
  bool stmWakeup(uint8_t Awake_Pin);

  /**
   * @fn sendATCMD(char* str)
   * @brief The MCU send data to the module, implemented by subclass
   * @param str
   */
  virtual void sendATCMD(char* str) =0;

  /**
   * @fn sendATCMD(String str)
   * @brief The MCU send data to the module, implemented by subclass
   * @param str
   */
  virtual void sendATCMD(String str) =0;

  /**
   * @fn sendATCMD(uint8_t num)
   * @brief The MCU send data to the module, implemented by subclass
   * @param num
   */
  virtual void sendATCMD(uint8_t num) =0;

  /**
   * @fn sendATCMD(String str,uint8_t num)
   * @brief The MCU send data to the module, implemented by subclass
   * @param str
   * @param num
   */
  virtual void sendATCMD(String str,uint8_t num) =0;

  /**
   * @fn sendATCMD(String str,String cmd)
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
   * @fn receviceATCMD
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
   * @brief Check whether there is data available returned from module
   * @return Bool type
   * @retval 1 Yes
   * @retval 0 No
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
