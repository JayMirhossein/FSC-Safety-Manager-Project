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
    int range_min=0, range_max=0;

    
    // Open the file in read mode
    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return -1; // Return -1 to indicate an error
    }
    
    // Read the file line by line
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        line_num++;
        if (strstr(buffer, search_word) != NULL) {
           printf("Found '%s' on line %d: %s", search_word, line_num, buffer);
            int success = extract_range_for_keyword_in_line(search_word, buffer, &range_min, &range_max);

            if (success) {
                printf("Parsed range: min = %d, max = %d\n", range_min, range_max);
            } else {
                printf("Failed to parse range in line.\n");
            }
  
        }
    }
    fclose(fp);
    
    if (found) {
        return 1; // Return 1 if found at least once
    } else {
        return 0; // Return 0 if not found
    }
}

    
// Parse a range from a line if it contains the given keyword.
// Returns 1 on success and fills outMin/outMax; returns 0 if keyword or range not found.
int extract_range_for_keyword_in_line(const char *keyword, const char *line, int *outMin, int *outMax)
{
    if (!keyword || !line || !outMin || !outMax) return 0;
    // Ensure the line contains the keyword (e.g., "NTWKNUM")
    if (strstr(line, keyword) == NULL) {
        return 0;
    }

    // Find the substring "range" and parse two integers following it
    const char *p = strstr(line, "range");
    if (!p) return 0;

    int minVal = 0, maxVal = 0;
    // Tolerant parse: allow arbitrary non-digits between numbers
    if (sscanf(p, "range%*[^0-9]%d%*[^0-9]%d", &minVal, &maxVal) == 2) {
        *outMin = minVal;
        *outMax = maxVal;
        Optional: printf("%s range parsed: min=%d, max=%d\n", keyword, minVal, maxVal);
        return 1;
    }
    // Fallback strict form
    if (sscanf(p, "range = %d to %d", &minVal, &maxVal) == 2) {
        *outMin = minVal;
        *outMax = maxVal;
        return 1;
    }

    // Parsing failed
    printf("Failed to parse range for %s in line.\n", keyword);
    return 0;
}
