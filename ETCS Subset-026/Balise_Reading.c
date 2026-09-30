//
//  Balise_Reading.c
//  FSC Safety Manager
//
//  Created by Jay on 3/8/2026.
//

#include "Balise_Reading.h"

struct balise_group_message {
    // balise group number;
    int8_t NI_DBG;
    /* The next expected number of the balise position in Group, The internal number of the balise describes the relative position of the balise in the group */
    int8_t N_PIG;
    // The next balise unqiue identifier number,
    int8_t NI_DC;
    // The next balise location identification
    int8_t NI_D;
}; // Balise basic data - Subset-026


int balise_reading(const char *baslie_group)
{
    return 0;
    
    struct balise_group_message b_group1,
                                b_group2,
                                b_group3,
                                b_group4,
                                b_group5,
                                b_group6,
                                b_group7,
                                b_group8,
                                b_group9,
                                b_group10;
    
}
