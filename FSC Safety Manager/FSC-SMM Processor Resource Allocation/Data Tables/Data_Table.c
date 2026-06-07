//
//  Data_Table.c
//  FSC Safety Manager
//
//  Created by Jay on 5/6/2026.
//
#include "Data_Table.h"
#define NUM_FILES 8
#define MAX_LINE 256
#define Point_Path "/Users/jayziabari/Desktop/FSC Safety Manager/FSC Safety Manager/FSC-SMM Processor Resource Allocation/Point_Processing/"
#define AI_module1_Path Point_Path "AI_module_11.txt"
#define AI_module2_Path Point_Path "AI_module_12.txt"
#define AI_module3_Path Point_Path "AI_module_13.txt"
#define AI_module4_Path Point_Path "AI_module_14.txt"
#define AI_module5_Path Point_Path "AI_module_15.txt"
#define AI_module6_Path Point_Path "AI_module_16.txt"
#define AI_module7_Path Point_Path "AI_module_17.txt"
#define AI_module8_Path Point_Path "AI_module_18.txt"

int AI_Data_Table(uint8_t module_mask) {
    // 1. Declare the file pointer for in and outfile
    FILE *outFile,*inFile;
    char line[MAX_LINE];
    char active_module_bit[NUM_FILES];

    
    for (int bit = 0; bit < NUM_FILES; bit++)
    {
        uint8_t bitValue = (module_mask >> bit) & 0x01;
        active_module_bit[bit] = bitValue;
        printf("Bit %d = %u\n", bit, bitValue);
    }
    
    outFile = fopen("/Users/jayziabari/Desktop/FSC Safety Manager/FSC Safety Manager/FSC-SMM Processor Resource Allocation/Data Tables/Point_Data_Table.txt", "w");
    if (outFile == NULL)
    {
        printf("Cannot create output file.\n");
        fclose(outFile);
        return 1;
    }
    

    // module 1 active
        if(active_module_bit[0]) {
            inFile = fopen(AI_module1_Path , "r");
            if (inFile == NULL)
            {
                printf("Cannot open input file.\n");
                return 1;
            }
            
            while (fgets(line, sizeof(line), inFile))
            {
                if (strncmp(line, "module_no:", 10) == 0 ||
                    strncmp(line, "channel[", 8) == 0)
                {
                    fputs(line, outFile);
                }
            }
            fclose(inFile);
        }
    
   // module 2 active
            if (active_module_bit[1]) {
                inFile = fopen(AI_module2_Path , "r");
                if (inFile == NULL)
                {
                    printf("Cannot open input file.\n");
                    return 1;
                }
                
                while (fgets(line, sizeof(line), inFile))
                {
                    if (strncmp(line, "module_no:", 10) == 0 ||
                        strncmp(line, "channel[", 8) == 0)
                    {
                        fputs(line, outFile);
                    }
                }
                fclose(inFile);
            }
            
    // module 3 active
             if (active_module_bit[2]) {
                 inFile = fopen(AI_module3_Path , "r");
                 if (inFile == NULL)
                 {
                     printf("Cannot open input file.\n");
                     return 1;
                 }
                 
                 while (fgets(line, sizeof(line), inFile))
                 {
                     if (strncmp(line, "module_no:", 10) == 0 ||
                         strncmp(line, "channel[", 8) == 0)
                     {
                         fputs(line, outFile);
                     }
                 }
                 fclose(inFile);
             }
    // module 4 active
             if (active_module_bit[3]) {
                 inFile = fopen(AI_module4_Path , "r");
                 if (inFile == NULL)
                 {
                     printf("Cannot open input file.\n");
                     return 1;
                 }
                 
                 while (fgets(line, sizeof(line), inFile))
                 {
                     if (strncmp(line, "module_no:", 10) == 0 ||
                         strncmp(line, "channel[", 8) == 0)
                     {
                         fputs(line, outFile);
                     }
                 }
                 fclose(inFile);
             }
    
    // module 5 active
             if (active_module_bit[4]) {
                 inFile = fopen(AI_module5_Path , "r");
                 if (inFile == NULL)
                 {
                     printf("Cannot open input file.\n");
                     return 1;
                 }
                 
                 while (fgets(line, sizeof(line), inFile))
                 {
                     if (strncmp(line, "module_no:", 10) == 0 ||
                         strncmp(line, "channel[", 8) == 0)
                     {
                         fputs(line, outFile);
                     }
                 }
                 fclose(inFile);
             }
    // module 6 active
             if (active_module_bit[5]) {
                 inFile = fopen(AI_module6_Path , "r");
                 if (inFile == NULL)
                 {
                     printf("Cannot open input file.\n");
                     return 1;
                 }
                 
                 while (fgets(line, sizeof(line), inFile))
                 {
                     if (strncmp(line, "module_no:", 10) == 0 ||
                         strncmp(line, "channel[", 8) == 0)
                     {
                         fputs(line, outFile);
                     }
                 }
                 fclose(inFile);
             }
   
    // module 7 active
             if (active_module_bit[6]) {
                 inFile = fopen(AI_module7_Path , "r");
                 if (inFile == NULL)
                 {
                     printf("Cannot open input file.\n");
                     return 1;
                 }
                 
                 while (fgets(line, sizeof(line), inFile))
                 {
                     if (strncmp(line, "module_no:", 10) == 0 ||
                         strncmp(line, "channel[", 8) == 0)
                     {
                         fputs(line, outFile);
                     }
                 }
                 fclose(inFile);
             }
  
    // module 8 active
             if (active_module_bit[7]) {
                 inFile = fopen(AI_module8_Path , "r");
                 if (inFile == NULL)
                 {
                     printf("Cannot open input file.\n");
                     return 1;
                 }
                 
                 while (fgets(line, sizeof(line), inFile))
                 {
                     if (strncmp(line, "module_no:", 10) == 0 ||
                         strncmp(line, "channel[", 8) == 0)
                     {
                         fputs(line, outFile);
                     }
                 }
                 fclose(inFile);
             }
    
    fclose(outFile);

    printf("Filtered data written to Filtered_Data.txt\n");
    return 0;
}
    

