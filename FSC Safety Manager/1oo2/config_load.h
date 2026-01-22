//
//  config_load.h
//  1oo2
//
//  Created by Jay on 6/1/2026.
//

#ifndef config_load_h
#define config_load_h

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 1024

int search_word_in_file(const char* filename, const char* search_word);
int extract_range_for_keyword_in_line(const char *keyword, const char *line, int *outMin, int *outMax);

#endif /* config_load_h */

