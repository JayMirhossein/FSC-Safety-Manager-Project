//
//  FSC_SM_DO.c
//  FSC Safety Manager
//
//  Created by Jay on 5/5/2026.
//

#include "FSC_SM_DO.h"
#include <time.h>

int FSC_SM_DO(void)
{
#define NUM_FILES 8
#define NUM_CHANNELS 16

    FILE *fp;
    char filename[150];

    // Seed random generator (only once at startup)
    srand((unsigned int)time(NULL));

    for (int i = 0; i < NUM_FILES; i++)
    {
        sprintf(filename,
                "/Users/jayziabari/Desktop/FSC Safety Manager 1/FSC Safety Manager/FSC-SMM Processor Resource Allocation/Output Writing/DO_module_%d.txt",
                i + 1);

        fp = fopen(filename, "w");
        if (fp == NULL)
        {
            printf("Error creating file %s\n", filename);
            return 1;
        }

        // Write header
        fprintf(fp, "Module Type: Digital Output\n");
        fprintf(fp, "Module ID: 0xD28B\n");
        fprintf(fp, "Status: 0xB5D\n");

        // Generate random channel values with timestamp
        for (int ch = 0; ch < NUM_CHANNELS; ch++)
        {
            unsigned int value = rand() % 2;

            time_t now = time(NULL);
            struct tm *tm_info = localtime(&now);

            char timestamp[32];
            strftime(timestamp, sizeof(timestamp),
                     "%Y-%m-%d %H:%M:%S", tm_info);

            fprintf(fp,
                    "channel[%d]: %u    Timestamp: %s\n",
                    ch, value, timestamp);
        }

        // Interrupt values
        fprintf(fp, "Interrupt Pin: %d\n", rand() % 10);
        fprintf(fp, "Interrupt Line: %d\n", rand() % 10);

        fclose(fp);
    }

    return 0;
}
