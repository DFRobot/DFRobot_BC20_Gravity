/*!
 * @file DFRobot_BC20_Gravity.cpp
 * @brief This is an IoT communication module based on MQTT and satellite information.
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      [PengKaixing](kaixing.peng@dfrobot.com)
 * @version  V1.0.0
 * @date  2019-07-16
 * @url https://github.com/DFRobot/DFRobot_BC20_Gravity
 */

#include "DFRobot_BC20_Gravity.h"
#include "DFRobot_queue.h"
#include "hardwareSerial.h"
#define POWERKEY    15  
#define SETKEY      13
#define PSW_EINT    5  

char *ret = NULL;
sSIMCard_t sSIMCard;
sRecData_t sRecData;
sSQ_t sSQ;
sGSN_t sGSN;
sGLL_t sGLL;
sGGA_t sGGA;
sGSA_t sGSA;
sRMC_t sRMC;
sVTG_t sVTG;
sCLK_t sCLK;
sGGNS_t sGGNS;
sGGNS_t2 sGGNS2;
sSAT_t sSAT;
sSAT_t2 sSAT2;
char* ret1=NULL;
uint8_t Flag=0;

uint8_t DFRobot_BC20::getNum(char* str)
{
  if(strcmp(str,NMEA_RMC)==0){
    return 0;
  }else if(strcmp(str,NMEA_VTG)==0){
    return 1;
  }else if(strcmp(str,NMEA_GGA)==0){
    return 2;
  }else if(strcmp(str,NMEA_GSA)==0){
    return 3;
  }else if(strcmp(str,NMEA_GSV)==0){
	return 4;
  }else if(strcmp(str,NMEA_GLL)==0){
    return 5;
  }else{
    return 255;
  }
}

int indexOf(char *str1,char *str2)  
{  
  char *p=str1;  
  int i=0;  
  p=strstr(str1,str2);  
  if(p==NULL){
	return -1;
  }else{  
    while(str1!=p)  
    {  
      str1++;  
      i++;  
    }  
  }  
  return i;  
} 

void substring(char *dest,char *src,int start,int end)  
{  
  int i=start;  
  if(start>strlen(src))
  {
	return;
  }
  if(end>strlen(src))
  {
	end = strlen(src);
  }   
  while(i<end)  
  {     
    dest[i-start]=src[i];  
    i++;  
  }  
  dest[i-start]='\0';  
  return;  
} 

String DFRobot_BC20::removeSthString(String sth, String str)
{
  String ret = str;
  int tempInt = 0;
  tempInt = ret.indexOf(sth);
  if(tempInt != -1)
  {
    ret = ret.substring(tempInt+sth.length(),ret.length());
  }
  return ret;
}

char* DFRobot_BC20::removeSthString(char* sth, char* str)
{
  char* ret = str;
  int tempInt = 0;
  tempInt =indexOf(ret,sth);
  if(tempInt != -1)
  {
    substring(ret,ret,tempInt+strlen(sth),strlen(ret));
  }
  return ret;
}

/*Returns the string preceding the given string*/
String DFRobot_BC20::GetSthfrontString(String sth, String str)
{
  String ret = str;
  String temp = sth;
  uint8_t tempInt = 0;
  tempInt = ret.indexOf(temp);
  if(tempInt != -1)
  {
    ret = ret.substring(0,tempInt);
  }
  return ret;
}

/*Returns the string preceding the given string*/
char* DFRobot_BC20::GetSthfrontString(char* sth, char* str)
{
  if(ret1!=NULL)
  {
  	free(ret1);
  	ret1=NULL;
  }
  ret1=(char*)malloc(strlen(str)+1);
  ret1[strlen(str)]='\0';
  memcpy(ret1,str,strlen(str));
  char* temp = sth;
  uint8_t tempInt = 0;
  tempInt = indexOf(ret1,temp);
  if(tempInt != -1)
  {
    substring(ret1,ret1,0,tempInt);
  }
  return ret1;
}

/*Check if there is a corresponding string in the data received in the queue*/
bool DFRobot_BC20::CheckRecData(char* str)
{
  bool ret = false;
  static struct sQueueData *p = NULL;
  p = cuappDequeue();
  while(p != NULL)
  {
    if(strncmp((const char* )p->data,str,strlen(str)) == 0)
	{
	  ret = true;				
    }
    free(p);
    p = cuappDequeue(); 
  }
  return ret;
}

/*Clear the BC20 serial port of unprocessed data and receive queue data*/
void DFRobot_BC20::flushBC20Serial(void)
{
  receviceATCMD(1);
  CheckRecData((char *)"");
}

void DFRobot_BC20::getRecData(uint8_t INFO)
{
  static struct sQueueData *p;
  static struct sQueueData *q;
  do{
    p = cuappDequeue();
    if(strncmp((const char* )p->data,"\r\n",2) == 0)
	{
      free(p);
	  p=NULL;
      break;
    }
	q=cuappDequeue();
	if(p==NULL)
	{
	  free(p);
	  p=NULL;
	  break;
	}
    free(p);
	p=NULL;		
  }while(p != NULL);
  switch(INFO){
    case CIMI_INFO:
      if(sSIMCard.IMEI_NUM == NULL){
        sSIMCard.IMEI_NUM = (uint8_t *)malloc(15+1);
      }else{
        free(sSIMCard.IMEI_NUM);
	  	sSIMCard.IMEI_NUM = NULL;
        sSIMCard.IMEI_NUM = (uint8_t *)malloc(15+1);
      }
      memset((sSIMCard.IMEI_NUM),'\0',16);
      memcpy((sSIMCard.IMEI_NUM),q->data, 15);
	  free(q);
	  q=NULL;
      break;
    default:
	  free(q);
	  q=NULL;		
      break;
  }
  flushBC20Serial();
}

/*Gets the number of received data*/
void DFRobot_BC20::getRecDataforNum(uint8_t num, uint8_t* &buf)
{
  static struct sQueueData *p = NULL;
  p = getQueueTail();
  if(strncmp((const char* )p->data,"OK\r\n",4) == 0)
  {
    p = getQueueHead();
    if(p == NULL)
	{
      return;
    }
    for(uint8_t i = 1; i < num; i++)
	{
      p = p->next;
      if(p == NULL)
	  {
        return;
      }
    }
    if(p != NULL)
	{
      if(buf != NULL)
	  {
        free(buf);
      }
      buf = (uint8_t *)malloc((p->len) +1);
	  if(buf==NULL)
	  {
	  	free(buf);
	  	return;
	  }
      memset(buf,'\0',(p->len)+1);
      memcpy(buf,p->data,p->len);
    }
  } 
}

/*Gets the number of received data*/
void DFRobot_BC20::getRecDataforNum_NoCheck(uint8_t num, uint8_t* &buf)
{
  static struct sQueueData *p = NULL;
  p = getQueueHead();
  if(p == NULL)
  {
    return;
  }
  if((p->len)<3)
  {
    p=p->next;
    if(p == NULL)
    {
      return;
    }		
  }	
  for(uint8_t i = 1; i < num; i++)
  {
    p = p->next;
    if(p == NULL)
	{
      return;
    }
  }
  if(buf != NULL)
  {
  	free(buf);
  	buf = NULL;
  }	
  if(p != NULL)
  {
    buf = (uint8_t *)malloc((p->len) +1);
    if(buf == NULL)
	{
      free(buf);
      buf = NULL;
    }
    memset(buf,'\0',(p->len)+1);
    memcpy(buf,p->data,p->len);
  }
}

uint8_t DFRobot_BC20::getIntforString(String CMD,String basic,uint8_t n)
{
  uint8_t *data=NULL;
  String tempStr;
  int a=0;
  flushBC20Serial();
  sendATCMD(CMD);
  receviceATCMD(3000);
  getRecDataforNum(2,data);
  tempStr  = (char *)data;
  if(data != NULL)
  {
    free(data);
  	data=NULL;
  }
  if( n == 1){
    tempStr  = removeSthString("+"+basic+": ",tempStr);
  	a=GetSthfrontString("\r\n",tempStr).toInt();
  	flushBC20Serial();
    return a;
  }else{
  	flushBC20Serial();
    return 0; 
  }
}

DFRobot_BC20::DFRobot_BC20(void)
{
  pinMode(PSW_EINT,OUTPUT);
  pinMode(POWERKEY,OUTPUT);
  digitalWrite(POWERKEY, LOW);
}

bool DFRobot_BC20::powerOn(void)
{
  if(available())
  {
  	readData();
  }
  flushBC20Serial();
  if(checkBC20())
  {
    return true;
  }
  sendATCMD((char *)"powerOn");
  delay(300);
  sendATCMD((char *)"");
  if(checkBC20())
  {
    return true;
  }
  return false;
}

bool DFRobot_BC20::configKeepalive(char* alivetime)
{
  uint8_t len=strlen(alivetime);
  char* cmd=(char*)malloc(26+len+1);
  if(cmd==NULL)
  {
    free(cmd);
    cmd=NULL;
    return false;
  }
  memset(cmd,'\0',21+len+1);
  memcpy(cmd,"QMTCFG=\"KEEPALIVE\",0,",21);
  memcpy(cmd+21,alivetime,len);
  memcpy(cmd+21+len,"\r\n",2);
  sendATCMD(cmd);
  free(cmd);
  cmd=NULL;
  receviceATCMD(3000);
  return CheckRecData(AT_OK);
}

bool DFRobot_BC20::checkBC20(void)
{
  sendATCMD(CHECK_BC20);
  receviceATCMD(300);
  return CheckRecData(AT_OK);
}

bool DFRobot_BC20::checkStmStauts(void)
{
  flushBC20Serial();
  sendATCMD((char *)"STMSTATUS");
  receviceATCMD(300);
  return CheckRecData(AT_OK);
}

bool DFRobot_BC20::checkNBCard(void)
{
  bool ret = false;
  sendATCMD(CHECK_NB_CARD);
  receviceATCMD(5000);
  ret = CheckRecData(AT_OK);
  if(!ret)
  {
    rest();
  }
  return ret;
}

void DFRobot_BC20 :: getSQ(void)
{
  uint8_t *data=NULL;
  int tempInt = 0;
  String tempStr="";
  flushBC20Serial();
  sendATCMD(GET_SQ);
  receviceATCMD(300);
  getRecDataforNum(2,data);
  tempStr  = (char *)data;
  if(data != NULL){
    free(data);
    data=NULL;
  }else{
    return;
  }
  tempStr  = removeSthString("+CSQ: ",tempStr);
  sSQ.rssi = GetSthfrontString(",",tempStr).toInt();
  tempStr  = removeSthString(",",tempStr);
  sSQ.ber  = GetSthfrontString("\r\n",tempStr).toInt();
  flushBC20Serial();
}

void DFRobot_BC20 :: clearGPS(void)
{
  if(ret!=NULL)
  {
    free(ret);
    ret=NULL;       
  }	
}

void DFRobot_BC20 :: getGSN(uint8_t cmd)
{
  if(available())
  {
  	readData();
  }
  uint8_t *data=NULL;
  int tempInt = 0;
  String tempStr="";
  flushBC20Serial();
  sendATCMD(GET_GSN,cmd);
  receviceATCMD(300);
  getRecDataforNum(2,data);
  tempStr  = (char *)data;
  if(data != NULL)
  {
    free(data);
  	data=NULL;
  }
  if(cmd){
  	tempStr  = removeSthString("+CGSN: ",tempStr);
  	tempStr = GetSthfrontString("\r\n",tempStr);
  	sGSN.imei=tempStr;			
  }else{
    sGSN.sn = tempStr;
  }	
}

static uint8_t ConvertUint8(String num, uint8_t bit)
{
  uint8_t ret = 0;
  String temp = "";
  for(uint8_t i = bit; i > 0; i--)
  {
    temp = num.substring(i-1,i);
    if(temp.toInt() == 1)
	{
      ret |= 1<<(bit-i);
    }
  }
  return ret;
}

/*!
 * @return Indicates the state of PDP context activation.
 *     0 Detached
 *     1 Attached
 */
uint8_t DFRobot_BC20 :: getGATT(void)
{
  if(available())
  {
  	readData();
  }
  return getIntforString(GET_GATT,SET_GATT,1);
}

uint8_t * DFRobot_BC20 :: getIMI(void)
{
  if(available())
  {
  	readData();
  }
  uint8_t* data;
  flushBC20Serial();
  sendATCMD(GET_IMI);
  receviceATCMD(300);
  getRecData(CIMI_INFO);
  return (uint8_t *)sSIMCard.IMEI_NUM;
}

/*!
 * @return time
 * The format is "yy/MM/dd,hh:mm:ss±zz",
 */
String DFRobot_BC20 :: getCLK(void)
{
  uint8_t *data=NULL;
  String tempStr="";
  String retStr = "";
  flushBC20Serial();
  sendATCMD(GET_CLK);
  receviceATCMD(300);
  getRecDataforNum(2,data);
  tempStr  = (char *)data;
  if(data != NULL)
  {
    free(data);
  	data=NULL;
  }
  tempStr  = removeSthString("+CCLK: ",tempStr);
  retStr = tempStr;
  sCLK.Year = GetSthfrontString("/",tempStr).toInt();
  tempStr  = removeSthString("/",tempStr);
  sCLK.Month = GetSthfrontString("/",tempStr).toInt();
  tempStr  = removeSthString("/",tempStr);
  sCLK.Day = GetSthfrontString(",",tempStr).toInt();
  tempStr  = removeSthString(",",tempStr);
  sCLK.Hour = GetSthfrontString(":",tempStr).toInt();
  tempStr  = removeSthString(":",tempStr);
  sCLK.Minute = GetSthfrontString(":",tempStr).toInt();
  tempStr  = removeSthString(":",tempStr);
  sCLK.Second = GetSthfrontString("GMT",tempStr).toInt();
  tempStr  = removeSthString("GMT",tempStr);
  sCLK.TimeEquation = tempStr.toInt();
  sCLK.Hour = sCLK.Hour+sCLK.TimeEquation;
  tempStr = GetSthfrontString("\r\n",tempStr);
  return retStr;
}

/*!
 * @return true or false.
 */
bool DFRobot_BC20 :: rest(uint8_t mode)
{
  flushBC20Serial();
  sendATCMD(SET_QRST,mode);
  receviceATCMD(300);
  delay(1000);
  return true;
}

/*!
 * @return USIM card identification number
 */
String DFRobot_BC20 :: getQCCID(void)
{
  uint8_t *data=NULL;
  String CCID = "";
  flushBC20Serial();
  sendATCMD(GET_QCCID);
  receviceATCMD(300);
  getRecDataforNum(2,data);
  CCID = removeSthString((char *)"+QCCID: ", (char *)data);
  if(data != NULL)
  {
    free(data);
  	data=NULL;
  }
  return CCID;
}

bool DFRobot_BC20 :: setQSCLK(uint8_t mode)
{
  flushBC20Serial();
  sendATCMD(SET_QSCLK,mode);
  receviceATCMD(300);
  return CheckRecData(AT_OK);
}

uint8_t DFRobot_BC20 :: getQGNSSC(void)
{
  return getIntforString(GET_QGNSSC,SET_QGNSSC,1);
}

bool DFRobot_BC20 :: setQGNSSC(uint8_t mode)
{
  flushBC20Serial();
  sendATCMD(SET_QGNSSC,mode);
  receviceATCMD(300);
  return CheckRecData(AT_OK);
}

static float Longitude_conversion(String str)
{
  float temp = 0;
  String tempStr = str;
  if(str.length() > 0){
    if((strcmp(str.c_str(),sRMC.LatitudeVal())==0)||(strcmp(str.c_str(),sGGA.LatitudeVal())==0)){
      temp = tempStr.substring(0,2).toInt();
      tempStr = tempStr.substring(2,tempStr.length());
      temp += (tempStr.substring(0,2).toInt())*10.0/60.0/10.0;
      tempStr = tempStr.substring(3,tempStr.length());
      temp += (tempStr.substring(0,4).toInt())*1.0/60.0/10000.0;
    }else if((strcmp(str.c_str(),sRMC.LongitudeVal())==0)||(strcmp(str.c_str(),sGGA.LongitudeVal())==0)){
      temp = tempStr.substring(0,3).toInt();
      tempStr = tempStr.substring(3,tempStr.length());
      temp += (tempStr.substring(0,2).toInt())*10.0/60.0/10.0;
      tempStr = tempStr.substring(3,tempStr.length());
      temp += (tempStr.substring(0,4).toInt())*1.0/60.0/10000.0;
    }
  }
  return temp;
}

uint8_t DFRobot_BC20 :: getQGNSSRD(void)
{
  uint8_t size; 
  for(int i=0;i<40;i++)
  {
  	if(sSAT2.data[i].PRN !=NULL)
  	{
  	  free(sSAT2.data[i].PRN);
  	  sSAT2.data[i].PRN=NULL;
  	}
  	if(sSAT2.data[i].Elev !=NULL)
  	{
  	  free(sSAT2.data[i].Elev);
  	  sSAT2.data[i].Elev=NULL;
  	}
  	if(sSAT2.data[i].Azim !=NULL)
  	{
  	  free(sSAT2.data[i].Azim);
  	  sSAT2.data[i].Azim=NULL;
  	}
  	if(sSAT2.data[i].SNR !=NULL)
  	{
  	  free(sSAT2.data[i].SNR);
  	  sSAT2.data[i].SNR=NULL;
  	}
  	if(sSAT2.data[i].Status !=NULL)
  	{
  	  free(sSAT2.data[i].Status);
  	  sSAT2.data[i].Status=NULL;
  	}
  	if(sSAT2.data[i].SYS !=NULL)
  	{
  	  free(sSAT2.data[i].SYS);
  	  sSAT2.data[i].SYS=NULL;
  	}		
  }
  getQGNSSRD(NMEA_RMC);
  sGGNS.LatitudeVal = Longitude_conversion(sRMC.LatitudeVal());
  sGGNS.LatitudeDir = sRMC.LatitudeDir();
  sGGNS.LongitudeVal = Longitude_conversion(sRMC.LongitudeVal());
  sGGNS.LongitudeDir = sRMC.LongitudeDir();
  getQGNSSRD(NMEA_VTG);
  sGGNS.Speed = atof(sVTG.GroundCourse_Kmh());
  sGGNS.Heading = atof(sVTG.GroundCourse_True());	
  getQGNSSRD(NMEA_GGA);
  sGGNS.Altitude=atof(sGGA.Altitude());
  getQGNSSRD(NMEA_GSA);
  for (uint8_t i = 0; i < 2; i++) 
  {
	for (uint8_t j = 0; j < 12; j++)
	{
	  sGGNS.Statellite_CH[i][j]=sGSA.data[i].Statellite_CH(j);
	  delay(1);
	}
  }
  sGGNS.PDOP = sGSA.data[0].PDOP();
  sGGNS.HDOP = sGSA.data[0].HDOP();
  sGGNS.VDOP = sGSA.data[0].VDOP();
  sGGNS.FixStatus = sGSA.data[0].FixStatus();
  getQGNSSRD(NMEA_GSV);
  sSAT2.USE=0;
  for(int i=0;i<sSAT.NUM;i++)
  {
	size=strlen(sSAT.data[i].PRN());
	sSAT2.data[i].PRN=(char*)malloc(size+1);
	if(sSAT2.data[i].PRN==NULL)
	{
	  free(sSAT2.data[i].PRN);
	  sSAT2.data[i].PRN=NULL;
	  return 0;
	}
	memset(sSAT2.data[i].PRN,'\0',size+1);
	memcpy(sSAT2.data[i].PRN,sSAT.data[i].PRN(),size);
	size=strlen(sSAT.data[i].Elev());
	sSAT2.data[i].Elev=(char*)malloc(size+1);
	if(sSAT2.data[i].Elev==NULL)
	{
	  free(sSAT2.data[i].Elev);
	  sSAT2.data[i].Elev=NULL;
	  return 0;
	}
	memset(sSAT2.data[i].Elev,'\0',size+1);
	memcpy(sSAT2.data[i].Elev,sSAT.data[i].Elev(),size);
	size=strlen(sSAT.data[i].Azim());
	sSAT2.data[i].Azim=(char*)malloc(size+1);
	if(sSAT2.data[i].Azim==NULL)
	{
	  free(sSAT2.data[i].Azim);
	  sSAT2.data[i].Azim=NULL;
	  return 0;
	}
	memset(sSAT2.data[i].Azim,'\0',size+1);
	memcpy(sSAT2.data[i].Azim,sSAT.data[i].Azim(),size);
	size=strlen(sSAT.data[i].SNR());
	sSAT2.data[i].SNR=(char*)malloc(size+1);
	if(sSAT2.data[i].SNR==NULL)
	{
	  free(sSAT2.data[i].SNR);
	  sSAT2.data[i].SNR=NULL;
	  return 0;
	}
	memset(sSAT2.data[i].SNR,'\0',size+1);
	memcpy(sSAT2.data[i].SNR,sSAT.data[i].SNR(),size);
	size=strlen(sSAT.data[i].SYS());
	sSAT2.data[i].SYS=(char*)malloc(size+1);
	if(sSAT2.data[i].SYS==NULL)
	{
	  free(sSAT2.data[i].SYS);
	  sSAT2.data[i].SYS=NULL;
	  return 0;
	}
	memset(sSAT2.data[i].SYS,'\0',size+1);
	memcpy(sSAT2.data[i].SYS,sSAT.data[i].SYS(),size);
	size=strlen(sSAT.data[i].Status());
	sSAT2.data[i].Status=(char*)malloc(size+1);
	if(sSAT2.data[i].Status==NULL)
	{
	  free(sSAT2.data[i].Status);
	  sSAT2.data[i].Status=NULL;
	  return 0;
	}
	memset(sSAT2.data[i].Status,'\0',size+1);
	memcpy(sSAT2.data[i].Status,sSAT.data[i].Status(),size);
	if(strcmp(sSAT2.data[i].Status,"Y")==0)
	{
	  (sSAT2.USE)++;
	}
	if(ret!=NULL)
	{
	  free(ret);
	  ret=NULL;
	}
  }	
  return 1;
}

uint8_t DFRobot_BC20 :: getQGNSSRD2(void)
{
  char* timeStr;
  char tempdata[5]={'0'};
  getQGNSSRD(NMEA_GGA);
  sGGNS2.LatitudeVal = Longitude_conversion(sGGA.LatitudeVal());
  sGGNS2.LongitudeVal = Longitude_conversion(sGGA.LongitudeVal());
  sGGNS2.Altitude=atof(sGGA.Altitude());
  sGGNS2.StatelliteNum=atoi(sGGA.StatelliteNum());
  sGGNS2.HDOP=atof(sGGA.HDOP());
  timeStr = sGGA.UTC_Time();
  substring(tempdata,timeStr,0,2);
  sCLK.Hour=atoi(tempdata);
  substring(timeStr,timeStr,2,strlen(timeStr));
  substring(tempdata,timeStr,0,2);
  sCLK.Minute=atoi(tempdata);				
  substring(timeStr,timeStr,2,strlen(timeStr));
  substring(tempdata,timeStr,0,2);
  sCLK.Second=atoi(tempdata);	
  return 1;
}

static void CheckSatelliteUse(uint8_t num)
{
  uint8_t temp = 0;
  char* tempdata;
  char*d;
  int addr;
  if(strcmp(sSAT.data[num].SYS(),"GPS")==0){	
    temp = 0;
  }else if(strcmp(sSAT.data[num].SYS(),"BeiDou")==0){			
    temp = 1;
  }	
  for(uint8_t i =0; i < 2; i++)
  {
  	for(uint8_t j =0; j < 12; j++){
  	  if(strcmp(sSAT.data[num].PRN(),(sGGNS.Statellite_CH[i][j]).c_str())==0)
	  {
  	  	sSAT.data[num].NUM=num;
  	  	addr=(sSAT.data[num].NUM)*21+3+3+3+3;
		tempdata = (char *)"Y";
		d=tempdata;
  	  	for(int j=0;j<strlen(d);j++)
		{
  	  	  EEPROM.write(addr+j,d[j]);
  	  	}            
  	  	return;
  	  }
  	}
  }
  sSAT.data[num].NUM=num;
  addr=(sSAT.data[num].NUM)*21+3+3+3+3;
  tempdata = (char *)"N";
  d=tempdata;
  for(int j=0;j<strlen(d);j++)
  {
    EEPROM.write(addr+j,d[j]);
  }  	
}
 
void DFRobot_BC20::getSatelliteInformation(uint8_t start, uint8_t num, char* str, char* sys)
{   
  char* tempStr = str;
  int addr;
  char*d;
  char* tempdata;
  for(uint8_t i = 0; i < num;i++)
  {
    if(strlen(GetSthfrontString((char*)",",tempStr)) == 0)
	{
	  sSAT.data[i+start].NUM=i+start;
	  addr=(sSAT.data[i+start].NUM)*21;
	  d = (char *)"N/A";
	  for(int j=0;j<strlen(d);j++)
	  {
	    EEPROM.write(addr+j,d[j]);
	  }	
    }else
	{
	  sSAT.data[i+start].NUM=i+start;
	  addr=(sSAT.data[i+start].NUM)*21;
	  tempdata=GetSthfrontString((char*)",",tempStr);
	  d=tempdata;
	  for(int j=0;j<strlen(d);j++)
	  {
	    EEPROM.write(addr+j,d[j]);
	  }				
    }
	tempStr = removeSthString((char *)",", tempStr);
	if (strlen(GetSthfrontString((char *)",", tempStr)) == 0)
	{
	  sSAT.data[i+start].NUM=i+start;
	  addr=(sSAT.data[i+start].NUM)*21+3;
	  d = (char *)"N/A";
	  for(int j=0;j<strlen(d);j++)
	  {
	    EEPROM.write(addr+j,d[j]);
	  }				
    }
	else
	{
	  sSAT.data[i+start].NUM=i+start;
	  addr=(sSAT.data[i+start].NUM)*21+3;
	  tempdata = GetSthfrontString((char *)",", tempStr);
	  d=tempdata;
	  for(int j=0;j<strlen(d);j++)
	  {
	    EEPROM.write(addr+j,d[j]);
	  }				
    }
	tempStr = removeSthString((char *)",", tempStr);
	if (strlen(GetSthfrontString((char *)",", tempStr)) == 0)
	{
	  sSAT.data[i+start].NUM=i+start;
	  addr=(sSAT.data[i+start].NUM)*21+3+3;
	  d = (char *)"N/A";
	  for(int j=0;j<strlen(d);j++)
	  {
	    EEPROM.write(addr+j,d[j]);
	  }				
    }
	else
	{
	  sSAT.data[i+start].NUM=i+start;
	  addr=(sSAT.data[i+start].NUM)*21+3+3;
	  tempdata = GetSthfrontString((char *)",", tempStr);
	  d=tempdata;
	  for(int j=0;j<strlen(d);j++)
	  {
	    EEPROM.write(addr+j,d[j]);
	  }			  
    }
	tempStr = removeSthString((char *)",", tempStr);
	if ((strlen(GetSthfrontString((char *)",", tempStr)) == 0) || (strlen(GetSthfrontString((char *)",", tempStr)) > 2))
	{
	  sSAT.data[i+start].NUM=i+start;
	  addr=(sSAT.data[i+start].NUM)*21+3+3+3;
	  d = (char *)"N/A";
	  for(int j=0;j<strlen(d);j++)
	  {
	    EEPROM.write(addr+j,d[j]);
	  }			
    }
	else
	{
	  sSAT.data[i+start].NUM=i+start;
	  addr=(sSAT.data[i+start].NUM)*21+3+3+3;
	  tempdata = GetSthfrontString((char *)",", tempStr);
	  d=tempdata;
	  for(int j=0;j<strlen(d);j++)
	  {
	    EEPROM.write(addr+j,d[j]);
	  }				
    }	
	sSAT.data[i+start].NUM=i+start;
	addr=(sSAT.data[i+start].NUM)*21+3+3+3+3+3;
	tempdata=sys;
	d=tempdata;
	for(int j=0;j<strlen(d);j++)
	{
	  EEPROM.write(addr+j,d[j]);
	}
	tempStr = removeSthString((char *)",", tempStr);
	CheckSatelliteUse(i+start);
  }
}

// Calculate the amount in use
static void CheckUse()
{
  sSAT.USE = 0x00;
  for(uint8_t i =0; i < sGSA.NUM;i++)
  {
    for(uint8_t j =0; j < 12; j++)
	{
  	  if((strlen(sGSA.data[i].Statellite_CH(j))> 0) &&(strcmp(sGSA.data[i].Statellite_CH(j),"N/A")==0))
	  {
        sSAT.USE++;
      }
    }
  }
}

bool DFRobot_BC20 :: getQGNSSRD(char* cmd)
{
#ifdef ARDUINO_ESP32_DEV	
  EEPROM.begin(1024);
#endif	
  for(int i=0;i<1024;i++)
  EEPROM.write(i,'\0');
  if(available())
  {
    readData();
  }
  uint8_t *data=NULL;
  char* timeStr;
  uint8_t NumSAT=0;
  uint8_t NumSEN=0;
  uint8_t StartNum=0;
  uint8_t lastTotSEN=0;
  uint8_t TotSEN = 0;
  uint8_t readnum = 2;
  char* tempdata=NULL;
  char*d=NULL;
  char* t_addr=NULL;
  int addr;
  char* tempStr=NULL;
  char *tempSYS;
  flushBC20Serial();
  sendATCMD(SET_QGNSSRD,cmd);
  receviceATCMD(5000); 	
  if(strcmp(cmd,NMEA_GSV)==0)
  {
    StartNum = 0x00;
    lastTotSEN = 0x00;
    sSAT.NUM = 0x00;
    for(uint8_t i = 0; i < 10; i++)
	{
      getRecDataforNum_NoCheck(readnum+i,data);
	  if(strlen((char*)data)<5)
	  {
	  	if(ret1!=NULL)
	  	{
	  	  free(ret1);
	  	  ret1=NULL;				
	  	}			
	  	free(data);
	  	data=NULL;
	  	return false;
	  }				
	  t_addr =(char*)malloc(strlen((char*)data)+1);
	  if(t_addr==NULL)
	  {
        free(data);
        data = NULL;				
	  	free(t_addr);
	  	return false;
	  }
	  memset(t_addr,'\0',strlen((char*)data)+1);
	  memcpy(t_addr,(char*)data,strlen((char*)data));
	  tempStr = t_addr;			
      if(data != NULL)
	  {
        free(data);
        data = NULL;
      }
	  else
	  {
		if(ret1!=NULL)
		{
		  free(ret1);
		  ret1=NULL;				
		}				
		free(t_addr);
		t_addr=NULL;
		free(data);
        data = NULL;
        return false;
      } 		
      if((readnum + i) == 2)
	  {
        tempStr  = removeSthString((char*)"+QGNSSRD: ",tempStr);
      }
      if(indexOf(tempStr,(char*)"$GPGSV,") != -1){
		  tempSYS = (char *)"GPS";
	  }else if(indexOf(tempStr,(char*)"$GBGSV,") != -1){
		  tempSYS = (char *)"BeiDou";
	  }else{
		  tempSYS = (char *)"N/A";
	  }
	  tempStr = removeSthString((char *)",", tempStr);
	  tempdata = GetSthfrontString((char *)",", tempStr);
	  TotSEN = atoi(tempdata);
	  tempStr = removeSthString((char *)",", tempStr);
	  tempdata = GetSthfrontString((char *)",", tempStr);
	  NumSEN = atoi(tempdata);
	  tempStr = removeSthString((char *)",", tempStr);
	  tempdata = GetSthfrontString((char *)",", tempStr);
	  NumSAT = atoi(tempdata);
	  tempStr = removeSthString((char *)",", tempStr);
	  if(TotSEN > 0)
	  {
        if(NumSEN == 1)
		{
          sSAT.NUM += NumSAT;
#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_LEONARDO) || defined(ARDUINO_AVR_MEGA2560)
		  if(sSAT.NUM>11)
		  sSAT.NUM=11;
		  if(Flag==1)
		  {
		  	sSAT.NUM=6;
		  }	
#else 
	      if(sSAT.NUM>17)   
		  {
		    sSAT.NUM = 17;
		  } 
#endif					
        }
        if(NumSAT /(NumSEN*4) > 0)
		{
          getSatelliteInformation(StartNum,4,tempStr,tempSYS);
          StartNum += 4;
        }
		else
		{
          getSatelliteInformation(StartNum,(NumSAT-((NumSEN-1)*4)),tempStr,tempSYS);
          StartNum += (NumSAT-((NumSEN-1)*4));
        }
      }
	  if(ret1!=NULL)
	  {
	  	free(ret1);
	  	ret1=NULL;				
	  }			
	  free(t_addr);
	  t_addr=NULL;			
	}
      return true;
  }
  else
  {		
    getRecDataforNum(2,data);		
	t_addr =(char*)malloc(strlen((char*)data)+1);
	memset(t_addr,'\0',strlen((char*)data)+1);
	memcpy(t_addr,(char*)data,strlen((char*)data));        
	if(data != NULL)
	{			
      free(data);
      data = NULL;
	}
	tempStr=t_addr;
	if(strlen(tempStr)<30)
	{
	  free(tempStr);
	  tempStr=NULL;
	  return 0;
	}
	tempStr = removeSthString((char *)"+QGNSSRD:", tempStr);
	switch(getNum(cmd))
	{			
      case 0://NMEA_RMC
        tempStr = removeSthString((char*)"$GNRMC,",tempStr);
	  	addr=0;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
	  	for(int j=0;j<strlen(d);j++)
		{
	  	  EEPROM.write(addr+j,d[j]);
	  	}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
	  	for(int j=0;j<strlen(d);j++)
		{
	  	  EEPROM.write(addr+j,d[j]);
	  	}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
	  	for(int j=0;j<strlen(d);j++)
		{
	  	  EEPROM.write(addr+j,d[j]);
	  	}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
	  	for(int j=0;j<strlen(d);j++)
		{
	  	  EEPROM.write(addr+j,d[j]);
	  	}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11+11+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11+11+11+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11+11+11+11+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11+11+11+11+11+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11+11+11+11+11+11+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11+11+11+11+11+11+11+11+11+11;
		tempdata = GetSthfrontString((char *)"*", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}					  
        timeStr = sRMC.UTC_Time();
		substring(tempdata,timeStr,0,2);
		sCLK.Hour=atoi(tempdata);				
		substring(timeStr,timeStr,2,strlen(timeStr));
		substring(tempdata,timeStr,0,2);
		sCLK.Minute=atoi(tempdata);				
		substring(timeStr,timeStr,2,strlen(timeStr));
		substring(tempdata,timeStr,0,2);
		sCLK.Second=atoi(tempdata);
		timeStr = sRMC.UTC_Date();
		substring(tempdata,timeStr,0,2);
		sCLK.Day=atoi(tempdata);				
		substring(timeStr,timeStr,2,strlen(timeStr));
		substring(tempdata,timeStr,0,2);
		sCLK.Month=atoi(tempdata);				
		substring(timeStr,timeStr,2,strlen(timeStr));
		substring(tempdata,timeStr,0,2);
		sCLK.Year=atoi(tempdata)+2000;				
        break;				
      case 1:/*NMEA_VTG*/
        tempStr = removeSthString((char*)"$GNVTG,",tempStr);						
		addr=0;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)"T,", tempStr);
		addr=0+5;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)"M,", tempStr);
		addr=0+5+5;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)"N,", tempStr);
		addr=0+5+5+5;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)"K,", tempStr);
		addr=0+5+5+5+5;
		tempdata = GetSthfrontString((char *)"*", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		} 				
        break;
      case 2:/*NMEA_GGA*//*待定*/			
        tempStr = removeSthString((char*)"$GNGGA,",tempStr);				
		addr=0;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11+11+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11+11+11+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)"M,", tempStr);
		addr=0+11+11+11+11+11+11+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)"M,", tempStr);
		addr=0+11+11+11+11+11+11+11+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11+11+11+11+11+11+11+11+11;
		tempdata = GetSthfrontString((char *)"*", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}		
        break; 
      case 3:/*NMEA_GSA*/			
        sGSA.NUM = 0;				
        for(int i = 0; i < 2; i++)
		{					
          if(indexOf(tempStr,(char*)"$GNGSA") != -1)
		  {						
            sGSA.NUM = i+1;
			tempStr = removeSthString((char *)",", tempStr);
			sGSA.data[i].NUM=i;
		  	addr=(sGSA.data[i].NUM)*72;
			tempdata = GetSthfrontString((char *)",", tempStr);
			d=tempdata;
		  	for(int j=0;j<strlen(d);j++)
			{
		  	  EEPROM.write(addr+j,d[j]);
		  	}
			tempStr = removeSthString((char *)",", tempStr);
			addr=(sGSA.data[i].NUM)*72+4;
			tempdata = GetSthfrontString((char *)",", tempStr);
			d=tempdata;
		  	for(int j=0;j<strlen(d);j++)
			{
		  	  EEPROM.write(addr+j,d[j]);
		  	}
			tempStr = removeSthString((char *)",", tempStr);
			for(int j = 0; j < 12; j++)
			{
		  	  addr=(sGSA.data[i].NUM)*72+4+4+j*4;
			  tempdata = GetSthfrontString((char *)",", tempStr);
			  d=tempdata;
			  for(int k=0;k<strlen(d);k++)
			  {
			    EEPROM.write(addr+k,d[k]);
			  }
			  tempStr = removeSthString((char *)",", tempStr);
			}						
			addr=(sGSA.data[i].NUM)*72+4+4+4*12;
			tempdata = GetSthfrontString((char *)",", tempStr);
			d=tempdata;
			for(int j=0;j<strlen(d);j++)
			{
			  EEPROM.write(addr+j,d[j]);
			}
			tempStr = removeSthString((char *)",", tempStr);
			addr=(sGSA.data[i].NUM)*72+4+4+4*12+4;
			tempdata = GetSthfrontString((char *)",", tempStr);
			d=tempdata;
			for(int j=0;j<strlen(d);j++)
			{
			  EEPROM.write(addr+j,d[j]);
			}
			tempStr = removeSthString((char *)",", tempStr);
			addr=(sGSA.data[i].NUM)*72+4+4+4*12+4+4;
			tempdata = GetSthfrontString((char *)",", tempStr);
			d=tempdata;
			for(int j=0;j<strlen(d);j++)
			{
			  EEPROM.write(addr+j,d[j]);
			}
			tempStr = removeSthString((char *)",", tempStr);
			addr=(sGSA.data[i].NUM)*72+4+4+4*12+4+4+4;
			tempdata = GetSthfrontString((char *)"*", tempStr);
			d=tempdata;
			EEPROM.write(addr,d[0]);
            for(int j = 0; j < 12; j++)
			{
              if(strlen(sGSA.data[i].Statellite_CH(j)) == 0)
			  {
				addr=(sGSA.data[i].NUM)*72+4+4+j*4;
				d = (char *)"N/A";
				for(int j=0;j<strlen(d);j++)
				{
				  EEPROM.write(addr+j,d[j]);
				}								
              }
            }						
          }					
		  free(t_addr);
		  t_addr=NULL;				
 		  getRecDataforNum(3+i,data);						
		  if(data != NULL)
		  {
		  	t_addr =(char*)malloc(strlen((char*)data)+1);						
		  	if(t_addr==NULL)
		  	{
		  	  free(t_addr);
		  	  return false;
		  	}
			memset(t_addr, '\0', strlen((char *)data) + 1);
			memcpy(t_addr,data,strlen((char*)data));
		  	tempStr=t_addr;						
		  	free(data);
		  	data = NULL;
		  }
		  else
		  {
		  	return false;
		  }
        }				
        CheckUse();
		if(t_addr!=NULL)
		{
		  free(t_addr);
		  return false;
		}				
        break;
      case 4://NMEA_GSV
      case 5:/* NMEA_GLL */
		  tempStr = removeSthString((char *)"$GNGLL,", tempStr);
		  addr = 0;
		  tempdata = GetSthfrontString((char *)",", tempStr);
		  d = tempdata;
		  for (int j = 0; j < strlen(d); j++)
		  {
			  EEPROM.write(addr + j, d[j]);
	    }
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
	    for(int j=0;j<strlen(d);j++)
	    {
	      EEPROM.write(addr+j,d[j]);
	    }
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
	    for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11+11+11;
		tempdata = GetSthfrontString((char *)",", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}
		tempStr = removeSthString((char *)",", tempStr);
		addr=0+11+11+11+11+11+11;
		tempdata = GetSthfrontString((char *)"*", tempStr);
		d=tempdata;
		for(int j=0;j<strlen(d);j++)
		{
		  EEPROM.write(addr+j,d[j]);
		}					  
        break;
      default:
        break;				
    }		
	free(t_addr);
	t_addr=NULL;
  }
  flushBC20Serial();
  return 1;
}


bool DFRobot_BC20 ::setAliyunserver(char*ProductKey,char* IPAddress,char* port,char connectID)
{
  char*IPaddress=(char*)malloc(strlen(ProductKey)+strlen(IPAddress)+1);
  if(IPaddress==NULL)
  {
  	free(IPaddress);
  	IPaddress=NULL;
  	return false;
  }
  memset(IPaddress,'\0', strlen(ProductKey) + strlen(IPAddress) + 1);
  memcpy(IPaddress,ProductKey,strlen(ProductKey));
  memcpy(IPaddress+strlen(ProductKey),IPAddress,strlen(IPAddress));
  while(false==openMQTT(connectID,IPaddress,port))
  {
    closeMQTT(0);
    delay(1000);
  }
  free(IPaddress);
  IPaddress=NULL;
  return true;	
}

bool DFRobot_BC20 ::connect_Aliyun(char* ProductKey,char* DeviceName,char* DeviceSecret)
{
  uint8_t* data=NULL;
  uint8_t timeout=0;
  String tempStr;
  uint8_t ProductKey_len=strlen(ProductKey);
  uint8_t DeviceName_len=strlen(DeviceName);
  uint8_t DeviceSecret_len=strlen(DeviceSecret);
  char* tempdata=(char*)malloc(13+ProductKey_len+DeviceName_len+DeviceSecret_len+15);
  if(tempdata==NULL)
  {
  	free(tempdata);
  	tempdata=NULL;
  	return false;
  }
  memset(tempdata, '\0', 6 + ProductKey_len + DeviceName_len + DeviceSecret_len + 15);
  memcpy(tempdata,GET_QMTCFG,6);
  memcpy(tempdata + 6, (char *)"=\"", 2);
  memcpy(tempdata + 8, (char *)"ALIAUTH", 7);
  memcpy(tempdata+8+7,"\",0,\"",5);
  memcpy(tempdata+8+7+5,ProductKey,ProductKey_len);
  ProductKey=NULL;
  memcpy(tempdata+8+7+5+ProductKey_len,"\",\"",3);
  memcpy(tempdata+8+7+5+ProductKey_len+3,DeviceName,DeviceName_len);
  memcpy(tempdata+8+7+5+ProductKey_len+3+DeviceName_len,"\",\"",3);
  memcpy(tempdata+8+7+5+ProductKey_len+3+DeviceName_len+3,DeviceSecret,DeviceSecret_len);
  DeviceSecret=NULL;
  memcpy(tempdata+8+7+5+ProductKey_len+3+DeviceName_len+3+DeviceSecret_len,"\"",1);
  flushBC20Serial();
  sendATCMD((char*)tempdata);
  free(tempdata);
  tempdata=NULL;
  receviceATCMD(300);
  if(!CheckRecData(AT_OK))
  {
    return false;
  }
  tempdata=(char*)malloc(13+DeviceName_len);
  if(tempdata==NULL)
  {
    free(tempdata);
    tempdata=NULL;
    return false;
  }
  memset(tempdata,'\0',13+DeviceName_len);
  memcpy(tempdata,SET_QMTCONN,7);
  memcpy(tempdata+7,"=0,\"",4);
  memcpy(tempdata+11,DeviceName,DeviceName_len);
  DeviceSecret=NULL;
  memcpy(tempdata+11+DeviceName_len,"\"",1);
  flushBC20Serial();
  sendATCMD((char*)tempdata);
  free(tempdata);
  tempdata=NULL;
  receviceATCMD(5000);
  if(CheckRecData(AT_OK))
  {
  	while(1)
  	{
  	  receviceATCMD(300);
  	  timeout++;
  	  if(timeout>250)
  	  {
  	  	return false;
  	  }			
  	  getRecDataforNum_NoCheck(1,data);
  	  tempStr  = (char *)data;
  	  if(tempStr.length()>0)
	  {
  	  	if(data != NULL)
		{
  	  	  free(data);
  	  	  data = NULL;
  	  	}
  	  	if(tempStr.equals("+QMTCONN: 0,0,0\r\n"))
		{
  	  	  this->mqttConneced = true;
  	  	  delay(1000);
  	  	  return true;
  	  	}
  	  }
  	}
  } 
  return false;
}

bool DFRobot_BC20 :: openMQTT(char connectID, char* Server, char* Port)
{
  uint8_t *data=NULL;
  char * tempChar=NULL;
  String tempStr="";
  uint8_t temptime = 0;
  uint8_t ServerLen = strlen(Server);
  uint8_t ALLlen=strlen(SET_QMTOPEN)+4+ServerLen+2+strlen(Port);
  tempChar = (char*)malloc(ALLlen+1);
  if(tempChar == NULL)
  {
    free(tempChar);
    return 0;
  }
  memset(tempChar,'\0',ALLlen+1);
  memcpy(tempChar,SET_QMTOPEN,strlen(SET_QMTOPEN));
  memcpy(tempChar+strlen(SET_QMTOPEN),"=",1);
  tempChar[strlen(SET_QMTOPEN)+1] = connectID;
  memcpy(tempChar+strlen(SET_QMTOPEN)+2,",\"",2);
  memcpy(tempChar+strlen(SET_QMTOPEN)+4,Server,ServerLen);
  memcpy(tempChar+strlen(SET_QMTOPEN)+4+ServerLen,"\",",2);
  memcpy(tempChar+strlen(SET_QMTOPEN)+4+ServerLen+2,Port,strlen(Port)); 
  flushBC20Serial();
  sendATCMD(tempChar);
  free(tempChar);
  tempChar=NULL;
  receviceATCMD(5000);	 
  if(CheckRecData(AT_OK))
  {
    while(1)
	{
	  receviceATCMD(100);
      if(temptime > 250)
	  {
        return false;
      }
      temptime++;
      getRecDataforNum_NoCheck(1,data);
	  CheckRecData((char *)"");
	  tempStr  = (char *)data;
      if(data != NULL)
	  {
        free(data);
        data = NULL;
      }
      if(tempStr.equals("+QMTOPEN: 0,0\r\n"))
	  {
        return true;
      }
    } 
  }
  return false; 
}

bool DFRobot_BC20 :: closeMQTT(uint8_t connectID)
{
  flushBC20Serial();
  sendATCMD(SET_QMTCLOSE,connectID);
  receviceATCMD(500);
  return CheckRecData(AT_OK);
}

bool DFRobot_BC20::connected(void)
{
  return this->mqttConneced;
}

bool DFRobot_BC20 :: connectServer(char connectID, char* clientID, char* UserName, char* PassWord)
{	
  uint8_t * data=NULL;
  uint8_t timeout=0;
  String tempStr;
  char * tempChar=NULL;
  uint8_t clientID_len=strlen(clientID);
  uint8_t UserName_len=strlen(UserName);
  uint8_t PassWord_len=strlen(PassWord);  
  tempChar = (char*)malloc(strlen(SET_QMTCONN)+1+1+2+clientID_len+2+1+UserName_len-1+2+1+PassWord_len+2);
  if(tempChar == NULL)
  {
    free(tempChar);
    return false;
  }
  memset(tempChar,'\0',strlen(SET_QMTCONN)+1+1+2+clientID_len+2+1+UserName_len-1+2+1+PassWord_len+2);
  memcpy(tempChar,SET_QMTCONN,strlen(SET_QMTCONN));
  memcpy(tempChar+strlen(SET_QMTOPEN),"=",1);
  tempChar[strlen(SET_QMTOPEN)+1] = connectID;
  memcpy(tempChar+strlen(SET_QMTCONN)+1+1,",\"",2);
  memcpy(tempChar+strlen(SET_QMTCONN)+1+1+2,clientID,clientID_len);
  memcpy(tempChar+strlen(SET_QMTCONN)+1+1+2+clientID_len,"\",",2);
  memcpy(tempChar+strlen(SET_QMTCONN)+1+1+2+clientID_len+2,"\"",1);
  memcpy(tempChar+strlen(SET_QMTCONN)+1+1+2+clientID_len+2+1,UserName,UserName_len);
  memcpy(tempChar+strlen(SET_QMTCONN)+1+1+2+clientID_len+2+1+UserName_len,"\",",2);
  memcpy(tempChar+strlen(SET_QMTCONN)+1+1+2+clientID_len+2+1+UserName_len+2,"\"",1);
  memcpy(tempChar+strlen(SET_QMTCONN)+1+1+2+clientID_len+2+1+UserName_len+2+1,PassWord,PassWord_len);
  memcpy(tempChar+strlen(SET_QMTCONN)+1+1+2+clientID_len+2+1+UserName_len+2+1+PassWord_len,"\"",1); 
  flushBC20Serial();
  sendATCMD(tempChar);
  free(tempChar);
  tempChar=NULL;
  receviceATCMD(5000);
  if(CheckRecData(AT_OK))
  {
	while(1)
	{
	  receviceATCMD(300);
	  timeout++;
	  if(timeout>250)
	  {
	  	return false;
	  }			
	  getRecDataforNum_NoCheck(1,data);
	  CheckRecData((char *)"");
	  tempStr  = (char *)data;
	  if(tempStr.length()>0)
	  if(data != NULL)
	  {
	  	free(data);
	  	data = NULL;
	  }
	  if(tempStr.equals("+QMTCONN: 0,0,0\r\n"))
	  {
	  	this->mqttConneced = true;
	  	delay(1000);
	  	return true;
	  }
	}
  } 
  return false;
}

bool DFRobot_BC20 :: connect(char * clientID, char * username,char * password,char connectID)
{
  return connectServer(connectID,clientID,username,password);
}

bool DFRobot_BC20 :: setServer(char* IPAddress, char* port, char connectID)
{
  while(false==openMQTT(connectID,IPAddress,port))
  {
    closeMQTT(0);
    delay(1000);
  }
  return true;
}

bool DFRobot_BC20 :: getQMTCONN(void)
{
  uint8_t* data=NULL;
  String tempstr;
  flushBC20Serial();
  sendATCMD(GET_QMTCONN);
  receviceATCMD(5000);
  getRecDataforNum(2,data);
  if(data!=NULL)
  {
    tempstr=(char*)data;		
    free(data);
    data=NULL;
    return 0;
  }
  if(tempstr.equals("+QMTCONN: 0,3\r\n"))
  {
    return true;
  }
  else
  {
    return false;
  } 		
}

bool DFRobot_BC20 :: subTopic(char connectID, char msgID, char* topic, char qos){
  char* tempdata=NULL;
  uint8_t* data=NULL;
  String tempStr;
  uint8_t timeout=0;
  uint8_t topic_len=strlen(topic);
  uint8_t cmd_len=strlen(SET_QMTSUB);
  uint8_t ALL_len=cmd_len+1+1+1+1+2+topic_len+2+1;
  tempdata=(char*)malloc(ALL_len+1);
  if(tempdata==NULL)
  {
  	free(tempdata);
  	return false;
  }
  memset(tempdata,'\0',ALL_len+1);	
  memcpy(tempdata,SET_QMTSUB,cmd_len);
  memcpy(tempdata+cmd_len,"=",1);
  tempdata[cmd_len+1] = connectID;
  memcpy(tempdata+cmd_len+1+1,",",1);
  tempdata[cmd_len+1+1+1] = msgID;
  memcpy(tempdata+cmd_len+1+1+1+1,",\"",2);
  memcpy(tempdata+cmd_len+1+1+1+1+2,topic,topic_len);
  memcpy(tempdata+cmd_len+1+1+1+1+2+topic_len,"\",",2);
  tempdata[cmd_len+1+1+1+1+2+topic_len+2] = qos;	
  flushBC20Serial();
  sendATCMD((char*)tempdata);
  free(tempdata);
  tempdata=NULL;
  receviceATCMD(10000);
  if(CheckRecData(AT_OK))
  {
	while(1)
	{
	  receviceATCMD(300);
	  timeout++;
	  if(timeout>250)
	  {
	  	return false;
	  }			
	  getRecDataforNum_NoCheck(1,data);
	  CheckRecData((char *)"");
	  tempStr  = (char *)data;
	  if(tempStr.length()>0)
	  if(data != NULL)
	  {
	  	free(data);
	  	data = NULL;
	  }
	  if((tempStr.equals("+QMTSUB: 0,1,0,1\r\n"))||(tempStr.equals("+QMTSUB: 0,1,0,0\r\n")))
	  {
	  	this->mqttConneced = true;
	  	delay(1000);
	  	return true;
	  }
	}
  }
  return false;
}

bool DFRobot_BC20::publish(char* topic,char* msg)
{
  return pubMessage('0','1','1','0',topic,msg);		
}

bool DFRobot_BC20 :: pubMessage(char connectID, char msgID, char qos, char retain, char* topic, char* msg)
{		
  char * tempChar=NULL;
  uint8_t* data;
  String tempStr;
  uint8_t timeout;
  uint8_t topic_len=strlen(topic);
  uint8_t msg_len=strlen(msg);
  uint8_t cmd_len=strlen(SET_QMTPUB);
  tempChar=(char*)malloc(cmd_len+1+1+1+1+1+1+1+1+2+topic_len+3+msg_len+2);
  if(tempChar == NULL)
  {
    free(tempChar);
    tempChar==NULL;
    return 1;
  }
  memset(tempChar,'\0',cmd_len+1+1+1+1+1+1+1+1+2+topic_len+3+msg_len+2);
  memcpy(tempChar,SET_QMTPUB,cmd_len);
  memcpy(tempChar+cmd_len,"=",1);
  tempChar[cmd_len+1] = connectID;
  memcpy(tempChar+cmd_len+1+1,",",1);
  tempChar[cmd_len+1+1+1] = msgID;
  memcpy(tempChar+cmd_len+1+1+1+1,",",1);
  tempChar[cmd_len+1+1+1+1+1] = qos;
  memcpy(tempChar+cmd_len+1+1+1+1+1+1,",",1);
  tempChar[cmd_len+1+1+1+1+1+1+1] = retain;
  memcpy(tempChar+cmd_len+1+1+1+1+1+1+1+1,",\"",2);
  memcpy(tempChar+cmd_len+1+1+1+1+1+1+1+1+2,topic,topic_len);
  memcpy(tempChar+cmd_len+1+1+1+1+1+1+1+1+2+topic_len,"\",\"",3);
  memcpy(tempChar+cmd_len+1+1+1+1+1+1+1+1+2+topic_len+3,msg,msg_len);
  memcpy(tempChar+cmd_len+1+1+1+1+1+1+1+1+2+topic_len+3+msg_len,"\"",1);   
  flushBC20Serial();
  sendATCMD((char*)tempChar);
  free(tempChar);
  tempChar=NULL;
  receviceATCMD(5000);
  return true; 
}

void DFRobot_BC20 :: setCallback(void (*call)(char*, uint8_t*, unsigned int))
{
  this->callback = call;
}

void DFRobot_BC20 :: loop(void)
{
  String tempdata;
  char* tempStr=NULL;
  if(available())
  {
  	tempdata=readData();
  	tempStr=(char*)malloc(80);
  	if(tempStr==NULL)
  	{
  	  if(ret!=NULL)
  	  {
  	  	free(ret);
  	  	ret=NULL;
  	  }			
  	  free(tempStr);
  	  return;
  	}
  	memset(tempStr,'\0',80);
  	memcpy(tempStr,tempdata.c_str(),tempdata.length());
	if (indexOf(tempStr, (char *)"+QMTRECV: ") != -1)
	{
 	  tempStr = removeSthString((char*)"+QMTRECV: ",tempStr);
	  char* Topic;
	  char*a;
	  Topic=(char*)malloc(60);
	  if(Topic==NULL)
	  {
	  	if(ret!=NULL)
	  	{
	  		free(ret);
	  		ret=NULL;
	  	}			
	  	free(tempStr);
	  	tempStr=NULL;
	  	free(Topic);
	  	Topic=NULL;			
	  	return;			
	  }
	  memset(Topic,'\0',60);
	  char* RecData;
	  tempStr = removeSthString((char *)",", tempStr);
	  tempStr = removeSthString((char *)",\"", tempStr);
	  a = GetSthfrontString((char *)"\",", tempStr);
	  memcpy(Topic,a,strlen(a));
	  tempStr = removeSthString((char *)"\",\"", tempStr);
	  RecData = GetSthfrontString((char *)"\"\r\n", tempStr);
	  if(callback!=NULL)
	  {
	  	callback((char *)(Topic),(uint8_t *)(RecData),strlen(RecData));
	  }
	  free(Topic);
	  Topic=NULL;
	  if(ret!=NULL)
	  {
	  	free(ret);
	  	ret=NULL;
	  }
	  free(tempStr);
	  tempStr=NULL;		
	}
	else
	{
	  if(ret!=NULL)
	  {
	  	free(ret);
	  	ret=NULL;
	  }			
	  free(tempStr);
	  return;			
	} 
  }	
}

bool DFRobot_BC20::configSleepMode(eSleepMode_t mode)
{
  return setQSCLK(mode);
}

bool DFRobot_BC20::BC20Wakeup(void)
{
  flushBC20Serial();
  char *str = (char *)"WakeUp";
  sendATCMD(str);
  delay(300);
  return(checkBC20());
}

static String ConvertString(uint8_t num, uint8_t bit)
{
  String ret = "";
  for(int i = bit; i > 0; i--)
  {
    if(num & (0x01<<i-1))
	{
      ret += '1';
    }
	else
	{
      ret += '0';
    }
  }
  return ret;
}

bool DFRobot_BC20::setPSMMode(ePSM_t status)
{
  char s;
  switch(status)
  {
  	case 0:
  		s='0';
  		break;
  	case 1:
  		s='1';
  		break;
  	case 2:
  		s='2';
  		break;	
  	default:
  		break;
  }
  char* strdata=NULL;
  strdata=(char*)malloc(32);
  if(strdata==NULL)
  {
	free(strdata);
	strdata=NULL;
	return false;
  }
  memset(strdata,'\0',32);
  memcpy(strdata,SET_PSMS,5);
  strdata[5]='=';
  strdata[6]=s;
  memcpy(strdata+7,",,,\"",4);
  memcpy(strdata+11,"10000010",8);
  memcpy(strdata+19,"\",\"",3);
  memcpy(strdata+22,"00010000",8);
  memcpy(strdata+30,"\"",1);
  flushBC20Serial();
  sendATCMD(strdata);
  free(strdata);
  strdata=NULL;
  receviceATCMD(300);
  return CheckRecData(AT_OK);
}

void DFRobot_BC20::controlLED(char * str)
{
  sendATCMD((char *)str);
}

void DFRobot_BC20::LED_ON(void)
{
  uint8_t size=0;
  char color=this->color;
  size=1;
  LED_OFF();
  char* str=NULL;
  str=(char*)malloc(8+size);
  if(str==NULL)
  {
  	free(str);
  	str=NULL;
  	return;
  }
  memset(str,'\0',8+size);
  memcpy(str,"LED_",4);
  str[4]=this->color;
  memcpy(str+4+size,"_ON",3);
  controlLED((char*)str);
  free(str);
  str=NULL;	
}

void DFRobot_BC20::LED_OFF(void)
{
  char* str;
  str = (char *)"LED_W_OFF";
  controlLED((char*)str);	
}

void DFRobot_BC20::changeColor(uint8_t newColor)
{
  switch(newColor)
  {
  	case 0:
  	  this->color='R';
  	  break;
  	case 1:
  	  this->color='B';
  	  break;
  	case 2:
  	  this->color='G';
  	  break;
  	case 3:
  	  this->color='Y';
  	  break;
  	case 4:
  	  this->color='P';
  	  break;
  	case 5:
  	  this->color='C';
  	  break;
  	case 6:
  	  this->color='W';
  	  break;
  	default:
  	  break;
  }
  return;	
}

bool DFRobot_BC20::stmLowpower(void)
{
  controlLED((char*)"LED_G_ON");
  delay(10);
  controlLED((char *)"LED_G_OFF");
  delay(10);
  sendATCMD((char *)"DSLEEP");
  delay(10);
  return(checkBC20());
}

bool DFRobot_BC20::stmWakeup(uint8_t Awake_Pin)
{
  pinMode(Awake_Pin,OUTPUT);
  digitalWrite(Awake_Pin,LOW);
  delay(100);
  digitalWrite(Awake_Pin,HIGH);
  delay(100);
  digitalWrite(Awake_Pin,LOW);
  return(checkStmStauts());
}

DFRobot_BC20_Serial::DFRobot_BC20_Serial(HardwareSerial*SSerial1)
:SSerial(SSerial1)
{
  SSerial->begin(9600);
}

void DFRobot_BC20_Serial::sendATCMD(String str){
  if(str.length() > 0)
  {
    SSerial->println("AT+"+str);
  }
  else
  {
    SSerial->println("AT"+str);
  }
  delay(500);
}

void DFRobot_BC20_Serial::sendATCMD(char* str)
{
  if(strlen(str) > 0)
  {
    SSerial->print("AT+");
    SSerial->println(str);
  }
  else
  {
    SSerial->println("AT");
  }
  delay(500);
}


void DFRobot_BC20_Serial::sendATCMDBychar(char str)
{
  SSerial->print(str);
}

void DFRobot_BC20_Serial::sendATCMD(String str,uint8_t num)
{
  SSerial->print("AT+"+str+"=");
  SSerial->println(num);
  delay(500);
}

void DFRobot_BC20_Serial::sendATCMD(String str,String cmd)
{
  SSerial->print("AT+"+str+"=");
  SSerial->println(cmd);
}

void DFRobot_BC20_Serial::sendATCMD(uint8_t num)
{
  SSerial->println(num);
  delay(500);
}

bool DFRobot_BC20_Serial::available(void)
{
  if(SSerial->available()> 0)
  {
	return true;
  }
  else
  {
	return false;
  }
}

String DFRobot_BC20_Serial::readData(void)
{
  String tempData="";
  uint32_t nowtime = millis();
  while(millis() - nowtime < 1000)
  {
    while(SSerial->available() > 0)
	{
      tempData += (char)SSerial->read();
  	  delay(1);
    }
  }
  return tempData;
}

// Receive the command data returned by BC20
void DFRobot_BC20_Serial::receviceATCMD(uint32_t timeout)
{
  String tempData="";
  int tempInt;
  uint8_t tempNum = 0;
  uint32_t nowtime = millis();
  while(millis() - nowtime < timeout)
  {
    while(SSerial->available() > 0)
  	{
      tempData += (char)(SSerial->read());
    }
    if((tempData.indexOf("OK\r\n") != -1))
	{
      break;
    }
  }
  if(tempData.length() > 0)
  {	
    do{
      tempInt = tempData.indexOf("\r\n");
      if(tempInt != -1)
	  {
        cuappEnqueue((uint8_t *)((tempData.substring(0,tempInt+2)).c_str()),tempInt+2,tempNum);
        tempData = tempData.substring(tempInt + 2, tempData.length());
        tempNum ++;
      }
    }while(tempInt >= 0);
    sRecData.dataNum = tempNum-1;
  }
}

DFRobot_BC20_IIC::DFRobot_BC20_IIC(uint8_t addr)
:IIC_addr(addr)
{
  Wire.begin();
}

void DFRobot_BC20_IIC::sendATCMD(char* str)
{
  int count=0;
  uint8_t str_len=strlen(str);
  uint8_t* tempdata;
  uint8_t IIC_len=30;
  tempdata=(uint8_t*)malloc(str_len+3);
  if(tempdata==NULL)
  {
  	free(tempdata);
  	return;
  }
  if(strlen(str)> 0)
  {
	memcpy(tempdata,"AT+",3);
	memcpy(tempdata+3,str,str_len);	
	str_len+=3;
	if(str_len>IIC_len)
	{
	  while(str_len>IIC_len)
	  {
	  	Wire.beginTransmission(IIC_addr);
	  	Wire.write(0x00);
	  	Wire.write(tempdata+IIC_len*count,IIC_len);
	  	Wire.endTransmission();
	  	count++;
	  	str_len-=IIC_len;				
	  }				
	  Wire.beginTransmission(IIC_addr);
	  Wire.write(0x00);			
	  Wire.write(tempdata+IIC_len*count,str_len);
	  Wire.write(0x0D);
	  Wire.write(0x0A);
	  Wire.endTransmission();
	}
	else
	{
	  Wire.beginTransmission(IIC_addr);
	  Wire.write(0x00);
	  Wire.write(tempdata,str_len);				
	  Wire.write(0x0D);
	  Wire.write(0x0A);
	  Wire.endTransmission();		
	}		
  }
  else
  {
	Wire.beginTransmission(IIC_addr);
	Wire.write(0x00);
	Wire.write((uint8_t*)"AT",2);
	Wire.write(0x0D);
	Wire.write(0x0A);
	Wire.endTransmission();	
  }
  free(tempdata);
  tempdata=NULL;
  delay(500);		
} 

void DFRobot_BC20_IIC::sendATCMD(String str)
{
  String temp;
  if(str.length() > 0)
  {
  	temp="AT+"+str;			
  	uint8_t data[temp.length()+1];
  	temp.toCharArray((char*)data,temp.length()+1);
  	if(temp.length()>30)
  	{
  	  Wire.beginTransmission(IIC_addr);
  	  Wire.write(0x00);
  	  Wire.write(data,30);
  	  Wire.endTransmission(); 				
  	  Wire.beginTransmission(IIC_addr);
  	  Wire.write(0x00);	
  	  Wire.write(data+30,temp.length()-30);
  	  Wire.write(0x0D);
  	  Wire.write(0x0A);
  	  Wire.endTransmission();				
  	}
	else
	{
  	  Wire.beginTransmission(IIC_addr);
  	  Wire.write(0x00);
  	  Wire.write(data,temp.length());			
  	  Wire.write(0x0D);
  	  Wire.write(0x0A);
  	  Wire.endTransmission(); 		
  	}
  }
  else
  {
	temp="AT"+str;
	uint8_t data[temp.length()+1];
	temp.toCharArray((char*)data,temp.length()+1);
	Wire.beginTransmission(IIC_addr);
	Wire.write(0x00);
	Wire.write(data,temp.length());
	Wire.write(0x0D);
	Wire.write(0x0A);
	Wire.endTransmission();		
  } 
  delay(500);
}

void DFRobot_BC20_IIC::sendATCMDBychar(char str)
{
  Wire.beginTransmission(IIC_addr);
  Wire.write(0x00);
  Wire.write(str);
  Wire.endTransmission();
  delay(500);
}

void DFRobot_BC20_IIC::sendATCMD(String str,uint8_t num)
{
  str="AT+"+str+"=";
  uint8_t data[str.length()+1];
  str.toCharArray((char*)data,str.length()+1);
  Wire.beginTransmission(IIC_addr);
  Wire.write(0x00);
  Wire.write(data,str.length());
  Wire.write(num+0x30);
  Wire.write(0x0D);
  Wire.write(0x0A);
  Wire.endTransmission();	
  delay(500);
}

void DFRobot_BC20_IIC::sendATCMD(String str,String cmd)
{
  str="AT+"+str+"="+cmd;
  uint8_t data[str.length()+1];
  data[str.length()]='\0';
  str.toCharArray((char*)data,str.length()+1);
  Wire.beginTransmission(IIC_addr);
  Wire.write(0x00);    
  Wire.write(data,str.length());
  Wire.write(0x0D);
  Wire.write(0x0A);
  Wire.endTransmission();	
  delay(500);
}

void DFRobot_BC20_IIC::sendATCMD(uint8_t num)
{
  Wire.beginTransmission(IIC_addr);
  Wire.write(0x00);    
  Wire.write(num+0x30);
  Wire.write(0x0D);
  Wire.write(0x0A);
  Wire.endTransmission();
  delay(500);
}

bool DFRobot_BC20_IIC::available(void)
{
  uint8_t len = 0;
  Wire.beginTransmission(IIC_addr);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(IIC_addr,1);
  len = Wire.read();	
  if(len > 0)
  {
    return true;
  }
  return false;
}
String DFRobot_BC20_IIC::readData(void)
{
  String tempData;
  int a_addr=1;
  int num=0;
  int len = 0;
  int tempInt;
  uint8_t tempNum = 0;
  uint32_t nowtime = millis();
  int IIC_Len = 32;
  while(millis() - nowtime < 5000)
  {
	Wire.beginTransmission(IIC_addr);
	Wire.write(0x00);
	Wire.endTransmission();		
	Wire.requestFrom(IIC_addr,1);
	len = Wire.read();			
 	if(len==255)
	{
	  return tempData;
	}	
	if(len > 0)
	{
	  Wire.beginTransmission(IIC_addr);
	  Wire.write(0x01);
	  Wire.endTransmission();			
	  while(len!=0)
	  {
		if(len > IIC_Len)
		{		
		  Wire.requestFrom(IIC_addr,IIC_Len);
		  for(int i=0;i<IIC_Len;i++)
		  {
		    tempData+=(char)Wire.read();
		  }
		  len -= IIC_Len;	
		  if(a_addr > IIC_Len)
		  {
		    a_addr = IIC_Len;
		  }				
		}
		else
		{
		  Wire.requestFrom(IIC_addr,len);
		  for(int i=0;i<len;i++)
		  {
		  	tempData+=(char)Wire.read();
		  }
		  len=0;
		}				
	  }				
	  if((tempData.indexOf("OK\r\n") != -1))
	  {
		break;
      }
    }
  }	
  return tempData;
}

// Receive the command data returned by BC20
void DFRobot_BC20_IIC::receviceATCMD(uint32_t timeout)
{
  String tempData;
  int a_addr=1;
  int num=0;
  uint8_t flag=0;
  int len = 0;
  int tempInt;
  uint8_t tempNum = 0;
  uint32_t nowtime = millis();
  int  IIC_Len = 32;
  while(millis() - nowtime < timeout)
  {
	Wire.beginTransmission(IIC_addr);
	Wire.write(0x00);
	Wire.endTransmission();		
	Wire.requestFrom(IIC_addr,1);
	len = Wire.read();
#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_LEONARDO)	|| defined(ARDUINO_AVR_MEGA2560)
	if(len>0)
	{
	  num++;			
	}
	if(((num>6)&&(len==0))||(flag==1))
	{
	  sRecData.dataNum = tempNum-1;
	  return;
	}
#else 
	if(flag==1)
	{
	  sRecData.dataNum = tempNum-1;
	  return;
	}
#endif		
    if(len==255)
    {
      return;
    }	
	if(len > 0)
	{
	  Wire.beginTransmission(IIC_addr);
	  Wire.write(0x01);
	  Wire.endTransmission();			
	  while(len!=0)
	  {
		if(len > IIC_Len)
		{		
		  Wire.requestFrom(IIC_addr,IIC_Len);
		  for(int i=0;i<IIC_Len;i++)
		  {
#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_LEONARDO)	|| defined(ARDUINO_AVR_MEGA2560)		
		    if(num<7)
		    {
		      tempData+=(char)Wire.read();
		    }
		    else
		    {
		      Wire.read();
		    }	
#else 
		    tempData+=(char)Wire.read();
#endif						
		  }
		  len -= IIC_Len;	
		  if(a_addr > IIC_Len)
		  {
		  	a_addr = IIC_Len;
		  }				
		}
		else
		{
		  Wire.requestFrom(IIC_addr,len);
		  for(int i=0;i<len;i++)
		  {
#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_LEONARDO)	|| defined(ARDUINO_AVR_MEGA2560)					
		    if(num<7)
		    {
		      tempData+=(char)Wire.read();
		    }
		    else
		    {
		      Wire.read();
		    }	
#else 
			tempData+=(char)Wire.read();
#endif
		  }
		  len=0;
		}
		if((tempData.indexOf("\r\n") != -1))
		{
			break;
		}	
	  }
#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_LEONARDO)	|| defined(ARDUINO_AVR_MEGA2560)			
      if((num>5)&&(flag==0))
      {
	    tempData="OK\r\n";
      }
#endif	
      if((tempData.indexOf("\r\n") != -1))
	  {
	    if(tempData.length() > 0)
	    {
		  do{
		    tempInt = tempData.indexOf("\r\n");
		    if(tempInt != -1)
			{
		  	  cuappEnqueue((uint8_t *)((tempData.substring(0,tempInt+2)).c_str()),tempInt+2,tempNum);						
		  	  tempNum ++;
		  	  if((tempData.indexOf("OK\r\n") != -1))					
		  		flag=1;											
		  	  tempData="";											
		    }
		  }while(tempInt >= 0);						 
		}
	  }			
	}		
  }
}

#ifndef ARDUINO_ESP32_DEV
DFRobot_BC20_SW_Serial::DFRobot_BC20_SW_Serial(SoftwareSerial* ss)
:SSerial(ss)
{
  SSerial->begin(9600);
}

void DFRobot_BC20_SW_Serial::sendATCMD(char* str)
{	
  if(strlen(str) > 0)
  {
    SSerial->print("AT+");
    SSerial->println(str);
  }
  else
  {
    SSerial->println("AT");
  }
  delay(500);
}

void DFRobot_BC20_SW_Serial::sendATCMD(String str)
{	
  if(str.length() > 0)
  {
    SSerial->println("AT+"+str);
  }
  else
  {
    SSerial->println("AT");
  }
  delay(500);
}

void DFRobot_BC20_SW_Serial::sendATCMDBychar(char str)
{
  SSerial->print(str);
}

void DFRobot_BC20_SW_Serial::sendATCMD(String str,uint8_t num)
{
  SSerial->print("AT+"+str+"=");
  SSerial->println(num);
  delay(500);
}

void DFRobot_BC20_SW_Serial::sendATCMD(String str,String cmd)
{
  SSerial->print("AT+"+str+"=");
  SSerial->println(cmd);
}

void DFRobot_BC20_SW_Serial::sendATCMD(uint8_t num)
{
  SSerial->println(num);
  delay(500);
}

bool DFRobot_BC20_SW_Serial::available(void)
{
  if(SSerial->available()> 0)
  {
    return true;
  }
  else
  {
    return false;
  }		
}

String DFRobot_BC20_SW_Serial::readData(void)
{
  String tempData="";
  uint32_t nowtime = millis();
  while(millis() - nowtime < 1000)
  {
    while(SSerial->available() > 0)
	{
	  tempData += (char)SSerial->read();		
    }
  	if((tempData.indexOf("OK") != -1))
	{
  	  break;
    }
  }
  return tempData;
}

void DFRobot_BC20_SW_Serial::receviceATCMD(uint32_t timeout)
{	
  String tempData="";
#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_LEONARDO) || defined(ARDUINO_AVR_MEGA2560)
  Flag=1;
  uint8_t counter=5;
#else
  uint8_t counter=100;
#endif
  int tempInt;
  uint8_t tempNum = 0;
  uint8_t num=0;
  uint8_t flag=0;
  uint32_t nowtime = millis();
  uint32_t len = 0;
  while(millis() - nowtime < timeout)
  {
    while(SSerial->available() > 0)
	{
	  if(num<counter)
	  {
	  	tempData +=(char)(SSerial->read());
	  	len++;
	  	nowtime = millis();
	  }
	  else
	  {
	  	SSerial->read();
	  	break;
	  }
	  if((tempData.indexOf("\r\n") != -1))
	  {
	  	flag=1;					
	  	num++;
	  	break;
	  }				
    }	
	if(num==counter)
	{
	  tempData="OK\r\n";
	}		
	if((tempData.length() > 0)&&(flag==1))
	{	
	  tempInt = tempData.indexOf("\r\n");
	  cuappEnqueue((uint8_t *)((tempData.substring(0,tempInt+2)).c_str()),tempInt+2,tempNum);
	  if((tempData.indexOf("OK\r\n") != -1))
	  {
	  	tempData="";
	  	flag=0;		
	  	break;
	  }
	  tempData="";
	  flag=0;		
	  tempNum ++;
	}		      
  }
  sRecData.dataNum = tempNum-1;
}
#endif

