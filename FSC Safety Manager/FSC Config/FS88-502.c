//
//  FS88-502.c
//  FSC Safety Manager
//
//  Created by Jay on 23/1/2026.
// FSC-SM Analog Input Data Point

#include "FS88-502.h"
//  FSC-SM Analog Input Data Point
/*int g_NTWKNUM_min = 0;
int g_NTWKNUM_max = 0;
int minV = 0, maxV = 0; */
//const char *sampleLine = "NTWKNUM NIM's UCN that SMM is connected to |__.__| range = 1 to 20";

int FS88_502(const char* filename, const char* search_word) {
    const char* config_sheet;// Replace with the word to search
    filename = "/Users/jayziabari/Desktop/1oo2/1oo2/outfile1.txt";
    config_sheet = "FS88-502";
    printf("configuration form '%s' in file '%s'...\n", config_sheet, filename);
    int result = search_word_in_file(filename, config_sheet);
    if (result == -1) {
        printf("An error occurred while trying to open the file.\n");
    } else if (result == 0) {
        printf("The word '%s' was not found in the file.\n", config_sheet);
    } else {
        printf("Search completed.\n");}
    
    // Demo: extract range for NTWKNUM from a given line of text
    
    search_word_in_file(filename, "PTDESC"); // Point Descriptor
    search_word_in_file(filename, "EUDESC "); //Engineering Unit Descriptor
    search_word_in_file(filename, "KEYWORD"); // Point Keyword Descriptor
    search_word_in_file(filename, "ASSOCDSP"); // Point Descriptor
    search_word_in_file(filename, "UNIT"); //Engineering Unit Descriptor
    search_word_in_file(filename, "NTWKNUM"); // Point Keyword Descriptor
    search_word_in_file(filename, "NODENUM"); // Point Keyword Descriptor
    search_word_in_file(filename, "SLOTNUM"); // Point Keyword Descriptor
    search_word_in_file(filename, "PLCADDR"); // Point Keyword Descriptor 
    
    
    return 0;
}
