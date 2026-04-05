//
//  FS88-502.h
//  FSC Safety Manager
//
//  Created by Jay on 23/1/2026.
//

#ifndef FS88_502_h
#define FS88_502_h

#include <stdio.h>
#include "config_load.h"

// global variable
extern int minV, maxV;
extern uint16_t parameter_range;
extern int found;
//extern struct FS88_502_FSC_SM_AI_Ranges FSC_AI_Data_Point;
int FS88_502(const char* filename, const char* search_word);

#endif /* FS88_502_h */
