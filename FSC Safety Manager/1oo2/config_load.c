//
//  config_load.c
//  1oo2
//
//  Created by Jay on 6/1/2026.
//

#include "config_load.h"

int search_word_in_file(const char* filename, const char* search_word) {
    FILE* fp;
    char buffer[BUFFER_SIZE];
    int line_num = 0;
    int found = 0;
    
    // Open the file in read mode
    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return -1; // Return -1 to indicate an error
    }
    
    // Read the file line by line
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        line_num++;
        // Use strstr to find the search_word within the current line (buffer)
        if (strstr(buffer, search_word) != NULL) {
            printf("Found '%s' on line %d: %s", search_word, line_num, buffer);
            found = 1; // Mark as found
        }
    }
    // Close the file
    fclose(fp);

    if (found) {
        return 1; // Return 1 if found at least once
    } else {
        return 0; // Return 0 if not found
    }
}
