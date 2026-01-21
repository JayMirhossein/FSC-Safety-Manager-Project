//
//  channel_1.h
//  1oo2
//
//  Created by Jay on 27/12/2025.
//

#ifndef channel_1_h
#define channel_1_h

#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // For sleep function
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Task function for the first thread
void *channel_one(void *arg); 

#endif /* channel_1_h */
