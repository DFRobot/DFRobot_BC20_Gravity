/*!
 * @file DFRobot_queue.h
 * @brief This is a header for handling linked list data.
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      [PengKaixing](kaixing.peng@dfrobot.com)
 * @version  V1.0.0
 * @date  2019-07-16
 * @url https://github.com/DFRobot/DFRobot_BC20_Gravity
 */

#ifndef DFROBOT_QUEUE_H_
#define DFROBOT_QUEUE_H_

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <Arduino.h>
struct sQueueData{
    struct sQueueData *next;
    uint16_t handle;
    uint16_t len;
    uint8_t data[0];
};

extern void cuappEnqueue(uint8_t *pbuf, uint16_t len, uint16_t conn_id);
extern struct sQueueData *cuappDequeue( void );
extern struct sQueueData *getQueueTail(void);
extern struct sQueueData *getQueueHead(void);
#endif
