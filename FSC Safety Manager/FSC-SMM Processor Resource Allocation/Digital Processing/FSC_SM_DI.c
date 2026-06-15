//
//  FSC_SM_DI.c
//  FSC Safety Manager
//
//  Created by Jay on 5/5/2026.
//

#include "FSC_SM_DI.h"

int FSC_SM_DI(void){

#define NUM_FILES 8
#define NUM_CHANNELS 16

    FILE *fp;
    char filename[150];

    // Seed random generator (only once at startup)
    srand(time(NULL));

    for (int i = 0; i < NUM_FILES; i++) {
        sprintf(filename, "/Users/jayziabari/Desktop/FSC Safety Manager 1/FSC Safety Manager/FSC-SMM Processor Resource Allocation/Digital Processing/DI_module_%d.txt", i + 1);

        fp = fopen(filename, "w");
        if (fp == NULL) {
            printf("Error creating file %s\n", filename);
            return 1;
        }

        // Write header
        fprintf(fp, "Module Type: Ditial Input\n");
        fprintf(fp, "Module ID: 0xD28B\n");
        fprintf(fp, "Status: 0xB5D\n");

        // Generate random channel values (0–65535)
        for (int ch = 0; ch < NUM_CHANNELS; ch++) {
            unsigned int value = rand() % 65536;
            fprintf(fp, "channel[%d]: %u\n", ch, value);
        }

        // Interrupt values (can also be randomized if needed)
        fprintf(fp, "Interrupt Pin: %d\n", rand() % 10);
        fprintf(fp, "Interrupt Line: %d\n", rand() % 10);

        fclose(fp);
    }

    //printf("8 files with random data created successfully.\n");
    return 0;
}

