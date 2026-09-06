//
//  FSC_SM_AI.c
//  FSC Safety Manager
//
//  Created by Jay on 25/4/2026.
//

#include "FSC_SM_AI_1.h"
#include <string.h>
#include <time.h>
#define POINT_PROCESSING_DIR1 "/Users/jayziabari/Desktop/FSC Safety Manager 2/FSC Safety Manager/FSC-SMM Processor Resource Allocation/Point_Processing"


uint16_t module_status;

// this code can be used to right to the analogue module, or the file that is written by the analogue input module

int FSC_SM_AI(int module_no){

#define NUM_FILES 8
#define NUM_CHANNELS 16
#define RAND_MAX 0x7fffffff
    
    FILE *fp;
    char filename[150];

    // Seed random generator (only once at startup)
    srand(time(NULL));
    module_status = rand() % 256;

    for (int i = 0; i < NUM_FILES; i++) {
        snprintf(
            filename,
            sizeof(filename),
            "%s/AI_module_%d%d.txt",
            POINT_PROCESSING_DIR1,
            module_no,
            i + 1
        );
        fp = fopen(filename, "w");
        if (fp == NULL) {
            printf("Error creating file %s\n", filename);
            return 1;
        }
        // Write header
        fprintf(fp, "module_no: %d\n",i+1);
        fprintf(fp, "Module Type: Analog Input\n");
        fprintf(fp, "Module ID: 0xD28B\n");
        fprintf(fp, "Status: %d\n",module_status);

        // Generate random channel values (0–100) with timestamp
        for (int ch = 0; ch < NUM_CHANNELS; ch++)
        {
            float value = ((float)rand() / (float)RAND_MAX) * 100.0;
            time_t now;
            struct tm *tm_info;
            char timestamp[32];

            now = time(NULL);
            tm_info = localtime(&now);
            strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

            fprintf(fp, "channel[%d]: %.6f  Timestamp: %s\n", ch, value, timestamp);
        }
        // Interrupt values (can also be randomized if needed)
        fprintf(fp, "Interrupt Pin: %d\n", rand() % 10);
        fprintf(fp, "Interrupt Line: %d\n", rand() % 10);
        fclose(fp);
    }

    //printf("8 files with random data created successfully.\n");

    return module_status;
}
//
//  FSC_SM_AI_fault.c
//  FSC Safety Manager
//
//  Created by Jay on 31/5/2026.
//


const char* GetModuleStatus() {
    {
        AlarmState state;
        switch(module_status)
        {
            case (1): {
                state = STATE_BELOW_LOW_TX_ALARM_LEVEL;
                return "Below Low Transmitter Alarm Level";}
                
            case (2):
            {state = STATE_PER_RANGE_ALARM_LEVEL;
                return "Upper Range Alarm Level";
                
            case (4):
                {state = STATE_ABOVE_HIGH_TX_ALARM_LEVEL;
                    return "Above High Transmitter Alarm Level";
                }
                
            case (8):
                { state = STATE_CHANNEL_X_MODULE_FAULTY;
                    return "Channel X Module Faulty";}
                
            case (16):
                { state = STATE_EXTERNAL_VOLTAGE_MONITORING_FAULT;
                    return "External Voltage Monitoring Fault";}
                
            case (32):
                {state = STATE_MODULE_FAULTY;
                    return "Module Faulty";}
                
            case (64):
                {state = STATE_INTERNAL_POWER_DOWN;
                    return "Internal Power Down";}
                
            case (128):
                {state = STATE_INPUT_COMPARE_ERROR;
                    return "Input Compare Error";}
                
            case (256):
                { state = STATE_INTERNAL_COMPARE_ERROR;
                    return "Internal Compare Error";}
                
            default:
                return "Analog Module state NORMAL\n";
            }
        }
    }}
