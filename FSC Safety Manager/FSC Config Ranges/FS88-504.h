//
//  FS88-504.h
//  FSC Safety Manager
//
//  Created by Jay on 31/1/2026.
//

#ifndef FS88_504_h
#define FS88_504_h

#include <stdio.h>
#include "config_load.h"
extern int minV, maxV;
extern uint16_t parameter_range;
extern int found;
int FS88_504(const char* filename, const char* search_word);

#endif /* FS88_504_h */
