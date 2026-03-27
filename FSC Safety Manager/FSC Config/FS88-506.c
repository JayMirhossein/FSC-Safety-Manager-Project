//
//  FS88-506.c
//  FSC Safety Manager
//
//  Created by Jay on 26/2/2026.
//

#include "FS88-506.h"

//  FSC-SM Digital Output Data Point

int FS88_506(const char* filename, const char* search_word) {
    const char* config_sheet;// Replace with the word to search
    filename = "/Users/jayziabari/Desktop/1oo2/1oo2/outfile1.txt";
    config_sheet = "FS88-506";
    printf("configuration form '%s' in file '%s'...\n", config_sheet, filename);
    int result = search_word_in_file(filename, config_sheet);
    if (result == -1) {
        printf("An error occurred while trying to open the file.\n");
    } else if (result == 0) {
        printf("The word '%s' was not found in the file.\n", config_sheet);
    } else {
        printf("Search completed.\n");}
    search_word_in_file(filename, "NTWKNUM"); // NIM's UCN that Contains This Point
    search_word_in_file(filename, "NODENUM "); // SMM's Address on the UCN
    search_word_in_file(filename, "SLOTNUM "); // Point Number Slot
    search_word_in_file(filename, "STATETXT (0)"); // Number of Digital States
    search_word_in_file(filename, "STATETXT (1)"); // Number of Digital Input Connections
    search_word_in_file(filename, "STATETXT (2)"); // Number of Digital Output Connections

    return 0;
}

