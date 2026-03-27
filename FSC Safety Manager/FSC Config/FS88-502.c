//
//  FS88-502.c
//  FSC Safety Manager
//
//  Created by Jay on 23/1/2026.
// FSC-SM Analog Input Data Point

#include "FS88-502.h"
//  FSC-SM Analog Input Data Point
struct FS88_502_FSC_SM_AI_Ranges {
    int NTWKNUM_min,NTWKNUM_max;     // NIM's UCN that Contains This Point range
    int NODENUM_min,NODENUM_max;     // SMM's Address on the UCN range */
    int SLOTNUM_min,SLOTNUM_max;          // Point Slot Number
    int PLCADDR_min,PLCADDR_max;     // FSC Source Address range
    char PRIMMOD[64];     // Primary Module Point ID
    char NAME[16];        // Point name
    char PTDESC[16];      // Point Descriptor
    char EUDESC[16];      // Engineering Unit Descriptor
    char KEYWORD[16];     // Point Keyword Descriptor
    char UNIT[8];         // Engineering Unit Descriptor
    int PVRAWHI;          // PV Raw High Value
    int PVRAWLO;          // PV Raw Low Value
    int PVEUHI;           // PV High Range in EUs
    int PVEULI;           // PV Low Range in EUs
};

void print_FS88_502_FSC_SM_AI_Ranges(const struct FS88_502_FSC_SM_AI_Ranges* s) {
    printf("NTWKNUM_min: %d\n", s->NTWKNUM_min);
    printf("NTWKNUM_max: %d\n", s->NTWKNUM_max);
    printf("NODENUM_min: %d\n", s->NODENUM_min);
    printf("NODENUM_max: %d\n", s->NODENUM_max);
    printf("SLOTNUM_min: %d\n", s->SLOTNUM_min);
    printf("SLOTNUM_max: %d\n", s->SLOTNUM_max);
    printf("PLCADDR_min: %d\n", s->PLCADDR_min);
    printf("PLCADDR_max: %d\n", s->PLCADDR_max);
    printf("PRIMMOD: %s\n", s->PRIMMOD);
    printf("NAME: %s\n", s->NAME);
    printf("PTDESC: %s\n", s->PTDESC);
    printf("EUDESC: %s\n", s->EUDESC);
    printf("KEYWORD: %s\n", s->KEYWORD);
    printf("UNIT: %s\n", s->UNIT);
    printf("PVRAWHI: %d\n", s->PVRAWHI);
    printf("PVRAWLO: %d\n", s->PVRAWLO);
    printf("PVEUHI: %d\n", s->PVEUHI);
    printf("PVEULI: %d\n", s->PVEULI);
}

int FS88_502(const char* filename, const char* search_word) {
    const char* config_sheet;// Replace with the word to search
    filename = "/Users/jayziabari/Desktop/FSC Safety Manager/FSC Safety Manager/cat1.txt";
    config_sheet = "FS88-502";
    printf("configuration form '%s' in file '%s'...\n", config_sheet, filename);
    int result = search_word_in_file(filename, config_sheet);
    if (result == -1) {
        printf("An error occurred while trying to open the file.\n");
    } else if (result == 0) {
        printf("The word '%s' was not found in the file.\n", config_sheet);
    } else {
        printf("Search completed.\n \n \n ");}
    
    // extract range for NTWKNUM from a given line of text
    
    struct FS88_502_FSC_SM_AI_Ranges FSC_AI_Data_Point;
  
    
    parameter_range = search_word_in_file(filename, "NTWKNUM"); // NIM's UCN that SM is connected to (Process Network Number)
    minV = parameter_range >> 16;
    maxV = parameter_range & 0xFFFF;
    FSC_AI_Data_Point.NTWKNUM_min = minV;
    FSC_AI_Data_Point.NTWKNUM_max = maxV;
        
    parameter_range = search_word_in_file(filename, "NODENUM"); // NIM's UCN that SM is connected to (Process Network Number)
    minV = parameter_range >> 16;
    maxV = parameter_range & 0xFFFF;
    FSC_AI_Data_Point.NODENUM_min = minV;
    FSC_AI_Data_Point.NODENUM_max = maxV;

    search_word_in_file(filename, "SLOTNUM"); // Point Slot Number
    minV = parameter_range >> 16;
    maxV = parameter_range & 0xFFFF;
    FSC_AI_Data_Point.SLOTNUM_max = maxV;
    FSC_AI_Data_Point.SLOTNUM_min = minV;
    
    search_word_in_file(filename,"PLCADDR"); // PLC Adrress
    minV = parameter_range >> 16;
    maxV = parameter_range & 0xFFFF;
    FSC_AI_Data_Point.PLCADDR_max = maxV;
    FSC_AI_Data_Point.PLCADDR_min = minV;
    
    search_word_in_file(filename, "PRIMMOD"); // Primary Module Point ID
    search_word_in_file(filename, "NAME"); // Name
    search_word_in_file(filename, "PTDESC"); // Point Descriptor
    search_word_in_file(filename, "EUDESC "); //Engineering Unit Descriptor
    search_word_in_file(filename, "KEYWORD"); // Point Keyword Descriptor
    search_word_in_file(filename, "UNIT"); //Engineering Unit Descriptor
    search_word_in_file(filename, "PVRAWHI"); // PV Raw High Value
    search_word_in_file(filename, "PVRAWLO"); // PV Raw Low Value
    search_word_in_file(filename, "PVEUHI");// PV High Range in EUs
    search_word_in_file(filename, "PVEULI");// PV Low Range in EUs
    
    print_FS88_502_FSC_SM_AI_Ranges(&FSC_AI_Data_Point);

    
    return 0;
}

