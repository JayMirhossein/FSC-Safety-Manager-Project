//
//  FS88-501A.h
//  FSC Safety Manager
//
//  Created by Jay on 8/1/2026.
//

#ifndef FS88_501A_h
#define FS88_501A_h

#include <stdio.h>
#include <_types/_uint16_t.h>
#include <stdint.h>

// In FS88-501A.h (or your relevant header)
// global variable
extern int minV, maxV;
extern uint16_t parameter_range;
extern int found;
extern struct FSC_SM_UCN_Node_Config_Range FSC_SM_UCN;

int FS88_501A(const char* filename, const char* search_word);

#endif /* FS88_501A_h */
