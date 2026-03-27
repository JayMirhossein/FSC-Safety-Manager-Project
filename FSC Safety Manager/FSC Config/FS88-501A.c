//
//  FS88-501A.c
//  FSC Safety Manager
//
//  Created by Jay on 8/1/2026.
//
/* This form is intended primarily for use in configuring each FSC-SM on your system by selecting SM for
 NODETYP below. This same form can be used to configure each NIM on your system by selecting
 NIM for NODETYP (some different targets will appear as shown). If your system has other UCN
 devices (PM, APM, HPM, LM), the NIMs can also be configured using the forms contained in the
 documentation for those devices.*/

#include "FS88-501A.h"
#include "config_load.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Structure representing FS88-501A/B configuration parameters
struct FSC_SM_UCN_Node_Config_Range{
    int NTWKNUM_min,NTWKNUM_max;
    int NODENUM_min,NODENUM_max;
    char NODETYP[5];
    int NMSGTXT_min,NMSGTXT_max;
    int NAISLOT_min,NAISLOT_max;
    int NDISLOT_min,NDISLOT_max;
    int NDOSLOT_min,NDOSLOT_max;
    int NLOGSLO_min,NLOGSLO_max;
    int NDITIMER_min,NDITIMER_max;
};

void print_FSC_SM_UCN_Node_Config_Range(const struct FSC_SM_UCN_Node_Config_Range* s) {
    printf("NTWKNUM_min: %d\n", s->NTWKNUM_min);
    printf("NTWKNUM_max: %d\n", s->NTWKNUM_max);
    printf("NODENUM_min: %d\n", s->NODENUM_min);
    printf("NODENUM_max: %d\n", s->NODENUM_max);
    printf("NODETYP: %s\n", s->NODETYP);
    printf("NMSGTXT_min: %d\n", s->NMSGTXT_min);
    printf("NMSGTXT_max: %d\n", s->NMSGTXT_max);
    printf("NAISLOT_min: %d\n", s->NAISLOT_min);
    printf("NAISLOT_max: %d\n", s->NAISLOT_max);
    printf("NDISLOT_min: %d\n", s->NDISLOT_min);
    printf("NDISLOT_max: %d\n", s->NDISLOT_max);
    printf("NDOSLOT_min: %d\n", s->NDOSLOT_min);
    printf("NDOSLOT_max: %d\n", s->NDOSLOT_max);
    printf("NLOGSLO_min: %d\n", s->NLOGSLO_min);
    printf("NLOGSLO_max: %d\n", s->NLOGSLO_max);
    printf("NDITIMER_min: %d\n", s->NDITIMER_min);
    printf("NDITIMER_max: %d\n", s->NDITIMER_max);
}

//  FSC-SM UCN Node Configuration ranges (parsed values)
int minV = 0, maxV = 0;
uint16_t parameter_range;
int found;

/*
 NotConfg This NIM or SM not configured on UCN
 Nim --> Network Interface Module
 PM  --> Process Manager Module
 APM --> Advanced Process Manager Module
 HPM --> High Performance Process Manager Module
 LM  --> Logic Manager Module
 SM  --> Safety Manager Module
 */
static const char* ALLOWED_NODETYP[] = {"Nim", "PM", "APM", "HPM", "LM", "SM"};

//struct to read FSC-SM UCN Node Configuration from page FS88-501A
struct FSC_SM_UCN_Node_Config_Range FSC_SM_UCN;

int FS88_501A(const char* filename, const char* search_word) {
    const char* config_sheet;// Replace with the word to search
    filename = "/Users/jayziabari/Desktop/FSC Safety Manager/FSC Safety Manager/cat1.txt";
    config_sheet = "FS88-501A";
    printf("configuration form '%s' in file '%s'...\n", config_sheet, filename);
    int result = search_word_in_file(filename, config_sheet);
    if (result == -1) {
        printf("An error occurred while trying to open the file.\n");
    } else if (result == 0) {
        printf("The word '%s' was not found in the file.\n", config_sheet);
    } else {
        printf("Search completed.\n");}
    printf("items found = %d times \n \n ",result);
    
    // Demo: extract range for FS88-501A from a given line of text
    
    parameter_range = search_word_in_file(filename, "NTWKNUM"); // NIM's UCN that SM is connected to (Process Network Number)
    minV = parameter_range >> 16;
    maxV = parameter_range & 0xFFFF;
    FSC_SM_UCN.NTWKNUM_min = minV;
    FSC_SM_UCN.NTWKNUM_max = maxV;
        
    parameter_range = search_word_in_file(filename, "NODENUM"); // NIM's UCN that SM is connected to (Process Network Number)
    minV = parameter_range >> 16;
    maxV = parameter_range & 0xFFFF;
    FSC_SM_UCN.NODENUM_min = minV;
    FSC_SM_UCN.NODENUM_max = maxV;
    
    strcpy(FSC_SM_UCN.NODETYP, ALLOWED_NODETYP[5]); // Set NODETYP to "SM"
    
    search_word_in_file(filename, "NMSGTXT"); // Number of Message Text Items
    
    config_sheet = "FS88-501B";
    printf("configuration form '%s' in file '%s'...\n", config_sheet, filename);
    result = search_word_in_file(filename, config_sheet);
    if (result == -1) {
        printf("An error occurred while trying to open the file.\n");
    } else if (result == 0) {
        printf("The word '%s' was not found in the file.\n", config_sheet);
    } else {
        printf("Search completed.\n");}
    printf("items found = %d times \n \n ",result);
    
    // Demo: extract range for FS88-501A from a given line of text
    //NAISLOT - # of Analog Input Slots
    parameter_range = search_word_in_file(filename, "NAISLOT"); // NIM's UCN that SM is connected to (Process Network Number)
    minV = parameter_range >> 16;
    maxV = parameter_range & 0xFFFF;
    
    FSC_SM_UCN.NAISLOT_max =maxV;
    FSC_SM_UCN.NAISLOT_min = minV;
    
    //NDOSLOT - # of Digital Output Slots
    parameter_range = search_word_in_file(filename, "NDOSLOT"); // NIM's UCN that SM is connected to (Process Network Number)
    minV = parameter_range >> 16;
    maxV = parameter_range & 0xFFFF;
    
    FSC_SM_UCN.NDOSLOT_max =maxV;
    FSC_SM_UCN.NDOSLOT_min = minV;
    
    //NDISLOT # of Digital Input Slots
    parameter_range = search_word_in_file(filename, "NDISLOT"); // NIM's UCN that SM is connected to (Process Network Number)
    minV = parameter_range >> 16;
    maxV = parameter_range & 0xFFFF;
    
    FSC_SM_UCN.NDISLOT_max =maxV;
    FSC_SM_UCN.NDISLOT_min = minV;
    
    //  NLOGSLO # of Logic Slots
    parameter_range = search_word_in_file(filename,"NLOGSLO"); // NIM's UCN that SM is connected to (Process Network Number)
    minV = parameter_range >> 16;
    maxV = parameter_range & 0xFFFF;
    
    FSC_SM_UCN.NLOGSLO_max =maxV;
    FSC_SM_UCN.NLOGSLO_min = minV;
    
    // NDITIMER # of Timer Slot
    
    parameter_range = search_word_in_file(filename, "NDITIMER"); // NIM's UCN that SM is connected to (Process Network Number)
    minV = parameter_range >> 16;
    maxV = parameter_range & 0xFFFF;
    
    FSC_SM_UCN.NDITIMER_max =maxV;
    FSC_SM_UCN.NDITIMER_min = minV;
    
    /* * The actual Range check will be calculated on the PU count for each Point type and the mix of configured
     Points desired. The FSC-SMM will perform Range checking. The 0.5 second scan rates will tend to lower these maximum range values.
     The actual Range check for this Parameter will depend on the NNLSBA. The FSC-SMM will perform Range
     checking.*/
    
    print_FSC_SM_UCN_Node_Config_Range(&FSC_SM_UCN);
    


    return 0;
}

