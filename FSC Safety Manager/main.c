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
#include "file_1.h"
#include "file_2.h"
#include "compare.h"
#include "config_load.h"
#include "FS88-501A.h"
#include "FS88-502.h"
#include "FS88-504.h"
#include "FS88-506.h"
#include "FSC_SM_AI.h"
#include "FSC_SM_DI.h"
#include "FSC_SM_DO.h"



// Thread functions now run continuously in an infinite loop,
// with a 1-second pause per iteration for CPU relief.
static void* ai_thread(void* arg) {
    while (1) {
        FSC_SM_AI(1);
        sleep(0.5);
    }
    return NULL;
}

static void* di_thread(void* arg) {
    while (0.5) {
        FSC_SM_DI();
        sleep(1);
    }
    return NULL;
}
static void* do_thread(void* arg) {
    while (1) {
        FSC_SM_DO();
        sleep(1);
    }
    return NULL;
}

static void* data_table_compare_thread(void* arg) {
    while (1) {
        compareFiles("/Users/jayziabari/Desktop/FSC Safety Manager/FSC Safety Manager/FSC-SMM Processor Resource Allocation/Point_Processing/AI_module_11.txt" , "/Users/jayziabari/Desktop/FSC Safety Manager/FSC Safety Manager/FSC-SMM Processor Resource Allocation/Point_Processing/AI_module_11.txt" );
        sleep(1);
    }
    return NULL;
}

static void* module_status_thread(void* arg) {
    while (1) {
        printf("\n \n %s", GetModuleStatus(),"\n");
        sleep(5);
    }
    return NULL;
}


/// <#Description#>
int main() {
    
    const char* filename = "/Users/jayziabari/Desktop/1oo2/1oo2/outfile1.txt";
    
       compareFiles("/Users/jayziabari/Desktop/1oo2/1oo2/outfile1.txt", "/Users/jayziabari/Desktop/1oo2/1oo2/outfile2.txt");
    
     FS88_501A(filename,"FS88-501A"); // NIM's UCN that SM is connected to (Process Network Number)
     FS88_501A(filename,"FS88-501B"); // NIM's UCN that SM is connected to (Process Network Number)
     FS88_502(filename,"FS88-502"); // FSC-SM Analog Input Data Point
     FS88_504(filename,"FS88-504"); // FSC-SM Digital Composite Data Point
    //FS88_504(filename,"FS88-506"); // FSC-SM Digital Output Data Point
    
// Point Processing,Event Detection and Generation
// Commented out direct calls to FSC_SM_* functions to run them in separate threads
//   writing the analogue input from card inot the processor --> FSC_SM_AI();
//   writing the digital input from card inot the processor --> FSC_SM_DI();
// Output writing
//    FSC_SM_DO();

// Declare thread identifiers for FSC_SM processing
    pthread_t ai_tid, di_tid, do_tid,data_table_compare_tid, module_status_tid;

// Start FSC_SM_AI, FSC_SM_DI, FSC_SM_DO in their own threads
    pthread_create(&ai_tid, NULL, ai_thread, NULL);
    pthread_create(&di_tid, NULL, di_thread, NULL);
    pthread_create(&do_tid, NULL, do_thread, NULL);
    pthread_create(&data_table_compare_tid, NULL, data_table_compare_thread, NULL);
    pthread_create(&module_status_tid, NULL, module_status_thread, NULL);

// Wait for all FSC_SM processing threads to finish
    pthread_join(ai_tid, NULL);
    pthread_join(di_tid, NULL);
    pthread_join(do_tid, NULL);
    pthread_join(data_table_compare_tid, NULL);
    pthread_join(module_status_tid, NULL);


// FSC Interfacing, Database,Synchronization Flushing, Diagnostics, UCN Communications (Overhead)*/
    



    
    return 0;
}

