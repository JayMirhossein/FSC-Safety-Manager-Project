//
//  FS88-506.h
//  FSC Safety Manager
//
//  Created by Jay on 26/2/2026.
//

#ifndef FS88_506_h
#define FS88_506_h

#include <stdio.h>
#include "config_load.h"
int FS88_506(const char* filename, const char* search_word);

extern int minV, maxV;
extern uint16_t parameter_range;
extern int found;
#endif /* FS88_506_h */
