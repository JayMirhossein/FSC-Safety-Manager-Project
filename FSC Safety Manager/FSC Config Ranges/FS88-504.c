//
//  FS88-504.c
//  FSC Safety Manager
//
//  Created by Jay on 31/1/2026.


#include "FS88-504.h"
//  FSC-SM Digital Composite Data Point

struct FS88_504_FSC_SM_DI_Ranges {
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
};

void print_FS88_504_FSC_SM_DI_Ranges(const struct FS88_504_FSC_SM_DI_Ranges* s) {
    printf("FS88_504_FSC_SM_DI_Composite\n \n");
    printf("NTWKNUM_min: %d\n", s->NTWKNUM_min);
    printf("NTWKNUM_max: %d\n", s->NTWKNUM_max);
    printf("NODENUM_min: %d\n", s->NODENUM_min);
    printf("NODENUM_max: %d\n", s->NODENUM_max);
    printf("SLOTNUM_min: %d\n", s->SLOTNUM_min);
    printf("SLOTNUM_max: %d\n", s->SLOTNUM_max);
}

int FS88_504(const char* filename, const char* search_word) {
    const char* config_sheet;// Replace with the word to search
    filename = "/Users/jayziabari/Desktop/FSC Safety Manager/FSC Safety Manager/cat1.txt";
    config_sheet = "FS88-504";
    printf("configuration form '%s' in file '%s'...\n", config_sheet, filename);
    int result = search_word_in_file(filename, config_sheet);
    if (result == -1) {
        printf("An error occurred while trying to open the file.\n");
    } else if (result == 0) {
        printf("The word '%s' was not found in the file.\n", config_sheet);
    } else {
        printf("Search completed.\n");}
    
    
    struct FS88_504_FSC_SM_DI_Ranges FSC_DI_Composite_Data_Point;

    
    parameter_range = search_word_in_file(filename, "NTWKNUM"); // NIM's UCN that SM is connected to (Process Network Number)
    minV = parameter_range >> 16;
    maxV = parameter_range & 0xFFFF;
    FSC_DI_Composite_Data_Point.NTWKNUM_min = minV;
    FSC_DI_Composite_Data_Point.NTWKNUM_max = maxV;
        
    parameter_range = search_word_in_file(filename, "NODENUM"); // NIM's UCN that SM is connected to (Process Network Number)
    minV = parameter_range >> 16;
    maxV = parameter_range & 0xFFFF;
    FSC_DI_Composite_Data_Point.NODENUM_min = minV;
    FSC_DI_Composite_Data_Point.NODENUM_max = maxV;

    search_word_in_file(filename, "SLOTNUM"); // Point Slot Number
    minV = parameter_range >> 16;
    maxV = parameter_range & 0xFFFF;
    FSC_DI_Composite_Data_Point.SLOTNUM_max = maxV;
    FSC_DI_Composite_Data_Point.SLOTNUM_min = minV;
    
    print_FS88_504_FSC_SM_DI_Ranges(&FSC_DI_Composite_Data_Point);

    return 0;
}
