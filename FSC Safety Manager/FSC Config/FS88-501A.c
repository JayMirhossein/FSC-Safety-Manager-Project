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

// Structure representing FS88-501A configuration parameters
struct FSC_SM_UCN_Node_Config_Range{
    int NTWKNUM_min,NTWKNUM_max;
    int NODENUM_min,NODENUM_max;
    char NODETYP[5];
    int NMSGTXT_min,NMSGTXT_max;
    int NAISLOT_min,NAISLOT_max;
    int NDISLOT_min,NDISLOT_max;
    int NDOSLOT_min,NDOSLOT_max;
};

//  FSC-SM UCN Node Configuration ranges (parsed values)
int g_NTWKNUM_min = 0;
int g_NTWKNUM_max = 0;
int minV = 0, maxV = 0;
uint16_t parameter_range;
int found;

/*
 NotConfg This NIM or SM not configured on UCN
 Nim Network Interface Module
 PM Process Manager Module
 APM Advanced Process Manager Module
 HPM High Performance Process Manager Module
 LM Logic Manager Module
 SM Safety Manager Module
 */
static const char* ALLOWED_NODETYP[] = { "Nim", "PM", "APM", "HPM", "LM", "SM" };

struct FSC_SM_UCN_Node_Config_Range FSC_SM;


// Removed invalid line: FSC_SM.NODETYP[] = ALLOWED_NODETYP[5];


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
    maxV = parameter_range >> 16;
    minV = parameter_range & 0xFFFF;
    FSC_SM.NTWKNUM_min = minV;
    FSC_SM.NTWKNUM_max = maxV;
        
    parameter_range = search_word_in_file(filename, "NODENUM"); // NIM's UCN that SM is connected to (Process Network Number)
    maxV = parameter_range >> 16;
    minV = parameter_range & 0xFFFF;
    FSC_SM.NODENUM_min = minV;
    FSC_SM.NODENUM_max = maxV;
    strcpy(FSC_SM.NODETYP, ALLOWED_NODETYP[5]); // Set NODETYP to "SM"
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
    
    parameter_range = search_word_in_file(filename, "NAISLOT"); // NIM's UCN that SM is connected to (Process Network Number)
    maxV = parameter_range >> 16;
    minV = parameter_range & 0xFFFF;
    //NDOSLOT
    parameter_range = search_word_in_file(filename, "NDOSLOT"); // NIM's UCN that SM is connected to (Process Network Number)
    maxV = parameter_range >> 16;
    minV = parameter_range & 0xFFFF;
    //NDISLOT
    parameter_range = search_word_in_file(filename, "NDISLOT"); // NIM's UCN that SM is connected to (Process Network Number)
    maxV = parameter_range >> 16;
    minV = parameter_range & 0xFFFF;
    
    //  NLOGSLO
    parameter_range = search_word_in_file(filename, " NLOGSLO"); // NIM's UCN that SM is connected to (Process Network Number)
    maxV = parameter_range >> 16;
    minV = parameter_range & 0xFFFF;
    
    parameter_range = search_word_in_file(filename, "NDITIMER"); // NIM's UCN that SM is connected to (Process Network Number)
    maxV = parameter_range >> 16;
    minV = parameter_range & 0xFFFF;

    return 0;
}

