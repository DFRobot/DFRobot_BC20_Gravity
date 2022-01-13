/*!
 * @file DFRobot_BC20AT.h
 * @brief This file offers the necessary command char strings for a NB module.
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      [PengKaixing](kaixing.peng@dfrobot.com)
 * @version  V1.0.0
 * @date  2019-07-16
 * @url https://github.com/DFRobot/DFRobot_BC20_Gravity
 */

#ifndef __DFROBOT_BC20AT__
#define __DFROBOT_BC20AT__

#define     CIMI_INFO                 0
#define     AT_OK                     (char*)"OK\r\n"

/*Get product information */
#define     GET_PII                   (char*)"ATI"

#define     SET_ECHO_0                (char*)"ATE0"
#define     SET_ECHO_1                (char*)"ATE1"

#define     READ_BAUD                 (char*)"IPR?"
#define     CHECK_BAUD                (char*)"IPR=?"
#define     SET_BAUD                  (char*)"IPR="


#define     CHECK_BC20                (char*)""
#define     CHECK_NB_CARD             (char*)"CIMI"
#define     CHECK_IMEI_NUM            (char*)"CGSN=1"

/*Get manufacturer information*/
#define     TEST_MI                   (char*)"CGMI=?"
#define     GET_MI                    (char*)"CGMI"

/*Get module information*/
#define     TEST_MM                   (char*)"CGMM=?"
#define     GET_MM                    (char*)"CGMM"

/*Get manufacturer version*/
#define     TEST_MR                   (char*)"CGMR=?"
#define     GET_MR                    (char*)"CGMR"

/*Get signal strength and CBER(Channel bit error rate)*/
#define     TEST_SQ                   (char*)"CSQ=?"
#define     GET_SQ                    (char*)"CSQ"

/*Get extended signal quality*/
#define     TEST_ESQ                  (char*)"CESQ=?"
#define     GET_ESQ                   (char*)"CESQ"

/*Product Serial Number*/
#define     TEST_GSN                  (char*)"CGSN=?"
#define     GET_GSN                   (char*)"CGSN"

/*EPS Network Registration Status*/
#define     TEST_EREG                 (char*)"CEREG=?"
#define     GET_EREG                  (char*)"CEREG?"
#define     SET_EREG                  (char*)"CEREG"

/*Signalling Connection Status*/
#define     TEST_SCON                 (char*)"CSCON=?"
#define     GET_SCON                  (char*)"CSCON?"
#define     SET_SCON                  (char*)"CSCON"

/*Operator Selection*/
#define     TEST_OPS                  (char*)"COPS=?"
#define     GET_OPS                   (char*)"COPS?"
#define     SET_OPS                   (char*)"COPS"

/*PS Attach or Detach*/
#define     TEST_GATT                 (char*)"CGATT=?"
#define     GET_GATT                  (char*)"CGATT?"
#define     SET_GATT                  (char*)"CGATT"

/*Define a PDP Context*/
#define     TEST_GDCONT               (char*)"CGDCONT=?"
#define     GET_GDCONT                (char*)"CGDCONT?"
#define     SET_GDCONT                (char*)"CGDCONT"

/*PDP Context Activation/Deactivation*/
#define     TEST_GACT                 (char*)"CGACT=?"
#define     GET_GACT                  (char*)"CGACT?"
#define     SET_GACT                  (char*)"CGACT"

/*Show PDP Addresses*/
#define     TEST_GPADDR               (char*)"CGPADDR=?"
#define     GET_GPADDR                (char*)"CGPADDR?"
#define     SET_GPADDR                (char*)"CGPADDR"

/*Request International Mobile Subscriber Identity*/
#define     TEST_IMI                  (char*)"CIMI=?"
#define     GET_IMI                   (char*)"CIMI"

/*Set UE Functionality*/
#define     TEST_FUN                  (char*)"CFUN=?"
#define     GET_FUN                   (char*)"CFUN?"
#define     SET_FUN                   (char*)"CFUN"

/*Report Mobile Termination Error*/
#define     TEST_MEE                  (char*)"CMEE=?"
#define     GET_MEE                   (char*)"CMEE?"
#define     SET_MEE                   (char*)"CMEE"

/*Return Current Date and Time*/
#define     TEST_CLK                  (char*)"CCLK=?"
#define     GET_CLK                   (char*)"CCLK?"

/*Query Power Supply Voltage*/
#define     TEST_BC                   (char*)"CBC=?"
#define     GET_BC                    (char*)"CBC"

/*Power Saving Mode Setting*/
#define     TEST_PSMS                 (char*)"CPSMS=?"
#define     GET_PSMS                  (char*)"CPSMS?"
#define     SET_PSMS                  (char*)"CPSMS"

/*eDRX Setting*/
#define     TEST_EDRXS                (char*)"CEDRXS=?"
#define     GET_EDRXS                 (char*)"CEDRXS?"
#define     SET_EDRXS                 (char*)"CEDRXS"

/*eDRX Read Dynamic Parameters*/
#define     TEST_EDRXRDP              (char*)"CEDRXRDP=?"
#define     GET_EDRXRDP               (char*)"CEDRXRDP"

/*Time Zone Reporting*/
#define     TEST_TZR                  (char*)"CTZR=?"
#define     GET_TZR                   (char*)"CTZR?"
#define     SET_TZR                   (char*)"CTZR"

/*Initial PDP Context Activation*/
#define     TEST_IPCA                  (char*)"CIPCA=?"
#define     GET_IPCA                   (char*)"CIPCA?"
#define     SET_IPCA                   (char*)"CIPCA"

/*CloT Optimization Configuration*/
#define     TEST_CIOTOPT               (char*)"CCIOTOPT=?"
#define     GET_CIOTOPT                (char*)"CCIOTOPT?"
#define     SET_CIOTOPT                (char*)"CCIOTOPT"

/*APN Rate Control*/
#define     TEST_GAPNRC                (char*)"CGAPNRC=?"
#define     SET_GAPNRC                 (char*)"CGAPNRC"

/*Extended Error Report*/
#define     TEST_EER                   (char*)"CEER=?"
#define     GET_EER                    (char*)"CEER"

/*Activate/Deactivate a PDN Context*/
#define     SET_QGACT                  (char*)"QGACT"

/*Get and Set Mobile Operation Band*/
#define     TEST_QBAND                 (char*)"QBAND=?"
#define     GET_QBAND                  (char*)"QBAND?"
#define     SET_QBAND                  (char*)"QBAND"

/*Automatically Reset*/
#define     TEST_QRST                  (char*)"QRST=?"
#define     SET_QRST                   (char*)"QRST"

/*Set Scrambling Algorithm*/
#define     TEST_QSPCHSC               (char*)"QSPCHSC=?"
#define     GET_QSPCHSC                (char*)"QSPCHSC?"
#define     SET_QSPCHSC                (char*)"QSPCHSC"

/*Lock NB-IoT Frequency*/
#define     TEST_QLOCKF                (char*)"QLOCKF=?"
#define     GET_QLOCKF                 (char*)"QLOCKF?"
#define     SET_QLOCKF                 (char*)"QLOCKF"

/*Clear NB-IoT Stored EARFCN List*/
#define     GET_QCSEARFCN              (char*)"QCSEARFCN"
#define     GET_QCSEARFCN              (char*)"QCSEARFCN"

/*Set Default PSD Connection Settings*/
#define     TEST_QCGDEFCONT            (char*)"QCGDEFCONT=?"
#define     GET_QCGDEFCONT             (char*)"QCGDEFCONT?"
#define     SET_QCGDEFCONT             (char*)"QCGDEFCONT"

/*NB-IoT Release Assistance Indication*/
#define     TEST_QNBIOTRAI            (char*)"QNBIOTRAI=?"
#define     GET_QNBIOTRAI             (char*)"QNBIOTRAI?"
#define     SET_QNBIOTRAI             (char*)"QNBIOTRAI"

/*Enable/Disable NB-IoT Related Event Report*/
#define     TEST_QNBIOTEVENT          (char*)"QNBIOTEVENT=?"
#define     GET_QNBIOTEVENT           (char*)"QNBIOTEVENT?"
#define     SET_QNBIOTEVENT           (char*)"QNBIOTEVENT"

/*Enable/Disable Deep Sleep Wakeup Indication*/
#define     TEST_QATWAKEUP            (char*)"QATWAKEUP=?"
#define     GET_QATWAKEUP             (char*)"QATWAKEUP?"
#define     SET_QATWAKEUP             (char*)"QATWAKEUP"

/*Engineering Mode*/
#define     TEST_QENG                 (char*)"QENG=?"
#define     GET_QENG                  (char*)"QENG"

/*USIM Card Identification*/
#define     GET_QCCID                 (char*)"QCCID"

/*Power off the Module*/
#define     GET_QPOWD                 (char*)"QPOWD=?"
#define     SET_QPOWD                 (char*)"QPOWD"

/*Configure Sleep Mode*/
#define     TEST_QSCLK                (char*)"QSCLK=?"
#define     GET_QSCLK                 (char*)"QSCLK?"
#define     SET_QSCLK                 (char*)"QSCLK"

/*Upgrade Firmware When the Delta Firmware Package is Stored on HTTP(S) Server*/
#define     TEST_QFOTADL              (char*)"QFOTADL=?"
#define     SET_QFOTADL               (char*)"QFOTADL"

/*GNSS module power control*/
#define     TEST_QGNSSC               (char*)"QGNSSC=?"
#define     GET_QGNSSC                (char*)"QGNSSC?"
#define     SET_QGNSSC                (char*)"QGNSSC"

/*Get GNSS information*/
#define     TEST_QGNSSRD              (char*)"QGNSSRD=?"
#define     GET_QGNSSRD               (char*)"QGNSSRD?"
#define     SET_QGNSSRD               (char*)"QGNSSRD"
#define     NMEA_RMC                  (char*)"\"NMEA/RMC\""
#define     NMEA_VTG                  (char*)"\"NMEA/VTG\""
#define     NMEA_GGA                  (char*)"\"NMEA/GGA\""
#define     NMEA_GSA                  (char*)"\"NMEA/GSA\""
#define     NMEA_GSV                  (char*)"\"NMEA/GSV\""
#define     NMEA_GLL                  (char*)"\"NMEA/GLL\""

/*Configure Optional Parameters of MQTT*/
#define     TEST_QMTCFG               (char*)"QMTCFG=?"
#define     GET_QMTCFG                (char*)"QMTCFG"

/*Open a Network for MQTT Client*/
#define     TEST_QMTOPEN              (char*)"QMTOPEN=?"
#define     GET_QMTOPEN               (char*)"QMTOPEN?"
#define     SET_QMTOPEN               (char*)"QMTOPEN"

/*Close a Network for MQTT Client*/
#define     TEST_QMTCLOSE             (char*)"QMTCLOSE=?"
#define     SET_QMTCLOSE              (char*)"QMTCLOSE"

/*Connect a Client to MQTT Server*/
#define     TEST_QMTCONN              (char*)"QMTCONN=?"
#define     GET_QMTCONN               (char*)"QMTCONN?"
#define     SET_QMTCONN               (char*)"QMTCONN"

/*Disconnect a Client from MQTT Server*/
#define     TEST_QMTDISC              (char*)"QMTDISC=?"
#define     SET_QMTDISC               (char*)"QMTDISC"

/*Subscribe to Topics*/
#define     TEST_QMTSUB               (char*)"QMTSUB=?"
#define     SET_QMTSUB                (char*)"QMTSUB"

/*Unsubscribe from Topics*/
#define     TEST_QMTUNS               (char*)"QMTUNS=?"
#define     SET_QMTUNS                (char*)"QMTUNS"

/*Publish Messages*/
#define     TEST_QMTPUB               (char*)"QMTPUB=?"
#define     SET_QMTPUB                (char*)"QMTPUB"
#endif
