//
//  FSC_SM_AI.h
//  FSC Safety Manager
//
//  Created by Jay on 25/4/2026.
//
// FSC_SM_AI.h
#ifndef FSC_SM_AI_H
#define FSC_SM_AI_H
#define POINT_PROCESSING_DIR "/Users/jayziabari/Desktop/FSC Safety Manager 1/FSC Safety Manager/FSC-SMM Processor Resource Allocation/Point_Processing"

// FSC_SM_AI.h
extern const char *kPointProcessingDir;
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

int FSC_SM_AI(int module_no);

/* Alarm/Error States */

typedef enum
{
    STATE_BELOW_LOW_TX_ALARM_LEVEL,
    STATE_PER_RANGE_ALARM_LEVEL,
    STATE_ABOVE_HIGH_TX_ALARM_LEVEL,
    STATE_CHANNEL_X_MODULE_FAULTY,
    STATE_EXTERNAL_VOLTAGE_MONITORING_FAULT,
    STATE_MODULE_FAULTY,
    STATE_INTERNAL_POWER_DOWN,
    STATE_INPUT_COMPARE_ERROR,
    STATE_INTERNAL_COMPARE_ERROR
} AlarmState;

/* Return alarm/error message */
const char* GetModuleStatus();

#endif // !FSC_SM_AI_H
