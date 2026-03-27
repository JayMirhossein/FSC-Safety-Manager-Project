/*
 
 Key Concepts
 pthread_t: Data type to store the unique thread identifier.
 pthread_create(): The function used to spawn a new thread. It takes arguments for the thread ID, attributes (NULL for default), the function the thread will execute, and arguments to pass to that function.
 pthread_join(): The function the main thread calls to wait for a specific created thread to terminate. This ensures the main program doesn't exit before the tasks are completed.
 pthread_exit(): Used to explicitly exit a thread. */
 
 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // For sleep function
#include "channel_1.h"
#include "channel_2.h"
#include "compare.h"
#include "config_load.h"
#include "FS88-501A.h"
#include "FS88-502.h"
#include "FS88-504.h"
#include "FS88-506.h"

/// <#Description#>
int main() {
    
    const char* word_to_find ; // Replace with the word to search
    const char* filename = "/Users/jayziabari/Desktop/1oo2/1oo2/outfile1.txt";
    
    pthread_t thread1, thread2; // Declare thread ID variables
    int ret1, ret2,ret3;
    printf("Main thread started\n");
    
    
        // Create the first thread
        ret1 = pthread_create(&thread1, NULL, channel_one, NULL); //
        if (ret1) {
            fprintf(stderr, "Error - pthread_create() return code: %d\n", ret1);
            exit(EXIT_FAILURE);
        }
        
        // Create the second thread
        ret2 = pthread_create(&thread2, NULL, channel_two, NULL); //
        if (ret2) {
            fprintf(stderr, "Error - pthread_create() return code: %d\n", ret2);
            exit(EXIT_FAILURE);
        }
       
        // Wait for both threads to finish
        pthread_join(thread1, NULL); //
        pthread_join(thread2, NULL); //

       // compareFiles("/Users/jayziabari/Desktop/1oo2/1oo2/outfile1.txt",
        //             "/Users/jayziabari/Desktop/1oo2/1oo2/outfile2.txt");
    
     FS88_501A(filename,"FS88-501A"); // NIM's UCN that SM is connected to (Process Network Number)
     FS88_501A(filename,"FS88-501B"); // NIM's UCN that SM is connected to (Process Network Number)
     FS88_502(filename,"FS88-502"); // FSC-SM Analog Input Data Point
     FS88_504(filename,"FS88-504"); // FSC-SM Digital Composite Data Point
    //FS88_504(filename,"FS88-506"); // FSC-SM Digital Output Data Point
    


    return 0;
}
