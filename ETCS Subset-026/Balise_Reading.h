//
//  Balise_Reading.h
//  FSC Safety Manager
//
//  Created by Jay on 3/8/2026.
//  balise_reader.c
//  FSC Safety Manager
//
//  Reads balise group information from:
//  /Users/jayziabari/Desktop/FSC Safety Manager 1/ETCS Subset-026/Balise files/balise_groups_1.txt
//
//  Reads one balise entry every 5 seconds
//  and writes Group Number, NI_DBG, N_PIG and NI_D

#ifndef Balise_Reading_h
#define Balise_Reading_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BALISE_FILE \
"/Users/jayziabari/Desktop/FSC Safety Manager 1/ETCS Subset-026/Balise files/balise_groups_1.txt"

#define OUTPUT_FILE "balise_output.txt"

typedef struct
{
    int groupNumber;
    int NI_DBG;
    int N_PIG;
    int NI_DC;
    int NI_D;
} BaliseGroup;

int Balise_Reader(void);


#endif /* Balise_Reading_h */
