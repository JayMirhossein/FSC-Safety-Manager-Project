//
//  FSC_SM_AI.c
//  FSC Safety Manager
//
//  Created by Jay on 25/4/2026.
//

#include "FSC_SM_AI.h"

// this code can be used to right to he output module, or the file that is written by the analogue input module

int FSC_SM_AI(void){

#define NUM_FILES 8
#define NUM_CHANNELS 16
#define RAND_MAX 0x7fffffff


    FILE *fp;
    char filename[50];

    // Seed random generator (only once at startup)
    srand(time(NULL));

    for (int i = 0; i < NUM_FILES; i++) {
        sprintf(filename, "module_%d.txt", i + 1);

        fp = fopen(filename, "w");
        if (fp == NULL) {
            printf("Error creating file %s\n", filename);
            return 1;
        }

        // Write header
        fprintf(fp, "Module Type: Analog Input\n");
        fprintf(fp, "Module ID: 0xD28B\n");
        fprintf(fp, "Status: 0xB5D\n");

        // Generate random channel values (0–100)
        for (int ch = 0; ch < NUM_CHANNELS; ch++) {
            float value = ((float)rand() / (float)RAND_MAX) * 100.0;
            fprintf(fp, "channel[%d]: %.6f\n", ch, value);
        }

        // Interrupt values (can also be randomized if needed)
        fprintf(fp, "Interrupt Pin: %d\n", rand() % 10);
        fprintf(fp, "Interrupt Line: %d\n", rand() % 10);

        fclose(fp);
    }

    printf("8 files with random data created successfully.\n");
    return 0;
}
