//
//  FSC_SM_AI.c
//  FSC Safety Manager
//
//  Created by Jay on 25/4/2026.
//

#include "FSC_SM_AI.h"
#include <string.h>
#include <time.h>
#include <math.h>


#define NUM_FILES 8
#define NUM_CHANNELS 16
#define RAND_MAX 0x7fffffff
#define AI_THRESHOLD 20

uint16_t module_status;

// this code can be used to right to the analogue module, or the file that is written by the analogue input module


int FSC_SM_AI(int module_no){
    
    /* Register cleanup function to delete AI files on exit */

    
    FILE *fp_module1,*fp_module2;
    char filename[150];
    char filename2[150];
    char line[MAX_LINE];

    ChannelData channels[NUM_CHANNELS];
    int count = 0;

    // Seed random generator (only once at startup)
    srand(time(NULL));
    module_status = rand() % 256;

    for (int i = 0; i < NUM_FILES; i++) {
        snprintf(
            filename,
            sizeof(filename),
            "%s/AI_module_1%d.txt",
            OUTPUT_DIR,
            i + 1
        );
        fp_module1 = fopen(filename, "w");
        if (fp_module1 == NULL) {
            printf("Error creating file %s\n", filename);
            return 1;
        }

        // Write header
        fprintf(fp_module1, "module_no: %d\n",i+1);
        if (i<=2 )
        {fprintf(fp_module1, "Module Type: Analog Input Speed Sensor \n");}
        else
        {fprintf(fp_module1, "Module Type: Analog Input Position Report \n");}
        fprintf(fp_module1, "Module ID: 0xD28B\n");
        fprintf(fp_module1, "Status: %d\n",module_status);

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

            // Build filename for the corresponding file in POINT_PROCESSING_DIR2
            snprintf(
                filename2,
                sizeof(filename2),
                "%s/AI_module_%d%d.txt",
                POINT_PROCESSING_DIR2,
                module_no,
                i + 1
            );

            // Attempt to open the secondary file for reading
            fp_module2 = fopen(filename2, "r");
            float read_value = 0.0f;
            int found_value = 0;

            if (fp_module2 != NULL) {
                // Scan lines looking for the matching channel line
                while (fgets(line, sizeof(line), fp_module2) != NULL) {
                    if (sscanf(line, "channel[%d]: %f", &count, &read_value) == 2) {
                        if (count == ch) {
                            found_value = 1;
                            break;
                        }
                    }
                }
                fclose(fp_module2);
            }

            // Calculate average if value found, else use generated value
            float final_value = found_value ? ((value + read_value) / 2.0f) : value;
            if(abs(value-read_value) > AI_THRESHOLD)
            {final_value = 0.00;}

            // Write the final value and timestamp to the output file
            fprintf(fp_module1, "channel[%d]: %.6f  Timestamp: %s\n", ch, final_value, timestamp);
        }
        // Interrupt values (can also be randomized if needed)
        fprintf(fp_module1, "Interrupt Pin: %d\n", rand() % 10);
        fprintf(fp_module1, "Interrupt Line: %d\n", rand() % 10);
        fclose(fp_module1);
    }

    //printf("8 files with random data created successfully.\n");
    
    return module_status;
}

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
