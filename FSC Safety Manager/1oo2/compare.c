//
//  compare.c
//  1oo2
//
//  Created by Jay on 30/12/2025.
//

#include "compare.h"
/**
 * Compares two files character by character.
 * Returns 0 if files are identical, 1 otherwise.
 */
int compareFiles(char *path1, char *path2) {
    int ch1, ch2;
    FILE *fp1,*fp2;
    unsigned long position = 0;
    
    // Open both files in read mode
   // char path1[100], path2[100];
    fp1 = fopen(path1, "r");
    fp2 = fopen(path2, "r");
    
    if (fp1 == NULL || fp2 == NULL) {
        perror("Error opening files");
        return EXIT_FAILURE;
    }

    do {
        ch1 = getc(fp1);
        ch2 = getc(fp2);
        position++;

        if (ch1 != ch2) {
            // Check if one file ended prematurely
            if (ch1 == EOF) {
                printf("Files differ: file 1 ended before file 2 at position %lu.\n", position);
            } else if (ch2 == EOF) {
                printf("Files differ: file 2 ended before file 1 at position %lu.\n", position);
            } else {
                printf("Files differ at position %lu: character 1 (0x%02X) != character 2 (0x%02X).\n", position, ch1, ch2);
            }
            return 1; // Files are different
        }
    } while (ch1 != EOF && ch2 != EOF);

    if (ch1 == EOF && ch2 == EOF) {
        printf("\n Files are identical.\n");
        return 0; // Files are identical
    } else {
        // This case handles a mismatch in length detected after the loop
        return 1;
    }
    
    // Close the files
    fclose(fp1);
    fclose(fp2);
    return EXIT_SUCCESS;
}

