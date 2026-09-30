/*
 Key Concepts
 pthread_t: Data type to store the unique thread identifier.
 pthread_create(): The function used to spawn a new thread. It takes arguments for the thread ID, attributes (NULL for default), the function the thread will execute, and arguments to pass to that function.
 pthread_join(): The function the main thread calls to wait for a specific created thread to terminate. This ensures the main program doesn't exit before the tasks are completed.
 pthread_exit(): Used to explicitly exit a thread. */

/*
 Fail-Safe Controller System Family
 ===================================
 +------------+------------------------------+--------------------------+--------+-------+
 | Central    | I/O                          | CPU                      | Arch   | Vote  |
 +------------+------------------------------+--------------------------+--------+-------+
 | Single     | Single                       | 10020/1/1 or 10020/1/2   | DMR    | 1oo2  |
 |            |                              | 10002/1/2 or 10012/1/2   | 1oo1D  | 1oo1D |
 +------------+------------------------------+--------------------------+--------+-------+
 | Redundant  | Single / Redundant / Both    | 10020/1/1 or 10020/1/2   | QMR    | 2oo4D |
 |            |                              | 10002/1/2 or 10012/1/2   | 1oo2D  | 1oo2D |
 +------------+------------------------------+--------------------------+--------+-------+
 (QPM – Quad Processor Module, QMR – Quadruple Modular Redundant, DMR – Dual Modular Redundant)
 This program implements software architecture DMR 1002, compatible with CPU 10020/1/1  10020/1/2
 */

#define cpp_Path "/Users/jayziabari/Desktop/FSC Safety Manager 1/FSC Safety Manager/FSC-SMM Processor Resource Allocation/cpp1/cpp1_status.txt"
 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // For sleep function
#include <stdbool.h>
#include <unistd.h> // Required for getpid()
#include <sys/types.h>
#include <sys/file.h>
#include <string.h>
#include <time.h>

// configuation header file
#include "config_load.h"
#include "FS88-501A.h"
#include "FS88-502.h"
#include "FS88-504.h"
#include "FS88-506.h"
#include "FSC_SM_AI.h"
#include "FSC_SM_AI.h"
#include "FSC_SM_DI.h"
#include "FSC_SM_DO.h"

//main functions header files
#include "file_1.h"
#include "file_2.h"
#include "compare.h"
#include "Redundnacy_Status.h"
#include "Balise_Reading.h"
#include "Data_Table.h"

static time_t program_start_time = 0;

typedef struct
{
    bool temperatureHighAlarm;
    bool temperatureLowAlarm;

    bool qppMemoryFailure;

    bool executionTimeOutOfRange;
    bool executionTimeOutFailure;

    bool logicalSheetError;

    bool watchdogOutputShorted;
    bool watchdogDeEnergized;

    bool redundantOutputsLineFault;
    bool nonRedundantOutputsLineFault;

    bool watchdogFaulty;
    bool busDriverFaulty;
    bool internalLinkFaulty;
    bool qppModeFaulty;

    bool secondarySwitchOffFaulty;
    bool softwareCorrupted;

   // intervention QPP key switch to IDLE
    bool cpp1_key_switch_IDLE;
    bool cpp1_spurious_watchdog_interrupt;
    bool cpp1_safe_state_initiated;
    bool cpp1_SD_input_de_energized;
    
    bool cpp1_synchronization_err;
    bool cpp1_base_timer_IO_err;
    bool cpp1_IO_compare_err;
    
    // Get the current process ID for cpp1
    pid_t pid ;

} cpp_Status_t;

// Thread functions now run continuously in an infinite loop,
// with a 1-second pause per iteration for CPU relief.
static void* ai_thread(void* arg) {
    while (1) {
        FSC_SM_AI(1);
    }
    return NULL;
}


static void* di_thread(void* arg) {
    while (0.5) {
        FSC_SM_DI();
        sleep(0.5);
    }
    return NULL;
}
static void* do_thread(void* arg) {
    while (1) {
        FSC_SM_DO();
        sleep(0.5);
    }
    return NULL;
}

static void* data_table_thread(void* rag){
    while(1)
    {
        //0x81; // 100000001
        AI_Data_Table(0x81);
        sleep(0.5);}
    return NULL;
}

static void* data_table_compare_thread(void* arg) {
    while (1) {
        compareFiles("/Users/jayziabari/Desktop/FSC Safety Manager 1/FSC Safety Manager/FSC-SMM Processor Resource Allocation/Point_Processing/AI_module_11.txt" , "/Users/jayziabari/Desktop/FSC Safety Manager 1/FSC Safety Manager/FSC-SMM Processor Resource Allocation/Point_Processing/AI_module_11.txt" );
        sleep(1);
    }
    return NULL;
}
static void* module_status_thread(void* arg) {
    while (1) {
        printf("\n%s", GetModuleStatus());
        sleep(2);
    }
    return NULL;
}
// monitoring CPP1 state , if any failure the
static void* cpp1_status_thread(void* arg) {
    while (1) {
        //  QPP1 fault
        //  faults that the Controller detects related to the QPP and the response to these faults.
        cpp_Status_t cpp1_status;
        cpp1_status.executionTimeOutFailure = 0;
        cpp1_status.executionTimeOutOfRange =0;
        // test timer , CPU send fault signal to watchdog after this time
        if (time(NULL) - program_start_time >= 150000000)
            cpp1_status.qppMemoryFailure = 1;
        else
        cpp1_status.qppMemoryFailure = 0;
        cpp1_status.watchdogFaulty =0;
        cpp1_status.busDriverFaulty =0;
        cpp1_status.internalLinkFaulty =0;
        cpp1_status.nonRedundantOutputsLineFault =0;
        cpp1_status.qppModeFaulty =0;
        cpp1_status.cpp1_IO_compare_err =0;
        cpp1_status.cpp1_base_timer_IO_err =0;
        cpp1_status.cpp1_spurious_watchdog_interrupt =0;
        cpp1_status.cpp1_synchronization_err =0;
        cpp1_status.pid = getpid();
        
        FILE *file = fopen(cpp_Path, "w");
        if (file != NULL) {
            int fd = fileno(file);
            flock(fd, LOCK_EX);
            fprintf(file, "FSC cpp1 status \n");
            fprintf(file, "executionTimeOutFailure: %d\n", cpp1_status.executionTimeOutFailure);
            fprintf(file, "qppMemoryFailure: %d\n", cpp1_status.qppMemoryFailure);
            fprintf(file, "watchdogFaulty: %d\n", cpp1_status.watchdogFaulty);
            fprintf(file, "busDriverFaulty: %d\n", cpp1_status.busDriverFaulty);
            fprintf(file, "internalLinkFaulty: %d\n", cpp1_status.internalLinkFaulty);
            fprintf(file, "nonRedundantOutputsLineFault: %d\n", cpp1_status.nonRedundantOutputsLineFault);
            fprintf(file, "qppModeFaulty: %d\n", cpp1_status.qppModeFaulty);
            fprintf(file, "IO Compare err: %d\n", cpp1_status.cpp1_IO_compare_err);
            fprintf(file, "base timer IO err: %d\n", cpp1_status.cpp1_base_timer_IO_err );
            fprintf(file, "spurious watchdog: %d\n", cpp1_status.cpp1_spurious_watchdog_interrupt);
            fprintf(file, "synch_err: %d\n", cpp1_status.cpp1_synchronization_err );
            fprintf(file, "cpp1processorpid: %d\n", cpp1_status.pid);
            flock(fd, LOCK_UN);
            fclose(file);

        } else {
            // Handle file open error if needed
        }}
    sleep(2);
}

/// <#Description#>
int main(void) {
    program_start_time = time(NULL);

    const char* filename = "/Users/jayziabari/Desktop/1oo2/1oo2/outfile1.txt";
       compareFiles("/Users/jayziabari/Desktop/1oo2/1oo2/outfile1.txt", "/Users/jayziabari/Desktop/1oo2/1oo2/outfile2.txt");
     FS88_501A(filename,"FS88-501A"); // NIM's UCN that SM is connected to (Process Network Number)
     FS88_501A(filename,"FS88-501B"); // NIM's UCN that SM is connected to (Process Network Number)
     FS88_502(filename,"FS88-502"); // FSC-SM Analog Input Data Point
     FS88_504(filename,"FS88-504"); // FSC-SM Digital Composite Data Point
     FS88_504(filename,"FS88-506"); // FSC-SM Digital Output Data Point
    
// Point Processing,Event Detection and Generation
// Commented out direct calls to FSC_SM_* functions to run them in separate threads
//   writing the analogue input from card inot the processor --> FSC_SM_AI();
//   writing the digital input from card inot the processor --> FSC_SM_DI();
// Output writing

// Declare thread identifiers for FSC_SM processing
    pthread_t ai_tid,
    di_tid, do_tid,
    data_table_compare_tid,
    data_table_tid,
    module_status_tid,cpp1_status_tid;

// Start FSC_SM_AI, FSC_SM_DI, FSC_SM_DO in their own threads
    pthread_create(&ai_tid, NULL, ai_thread, NULL);
    pthread_create(&di_tid, NULL, di_thread, NULL);
    pthread_create(&do_tid, NULL, do_thread, NULL);
// pthread_create(&data_table_compare_tid, NULL, data_table_compare_thread, NULL);
    pthread_create(&module_status_tid, NULL, module_status_thread, NULL);
    pthread_create(&data_table_tid, NULL, data_table_thread, NULL);
    pthread_create(&cpp1_status_tid, NULL, cpp1_status_thread, NULL);


// Wait for all FSC_SM processing threads to finish
    pthread_join(ai_tid, NULL);
    pthread_join(di_tid, NULL);
    pthread_join(do_tid, NULL);
    pthread_join(data_table_tid, NULL);

// FSC Interfacing, Database,Synchronization Flushing, Diagnostics, UCN Communications (Overhead)*/
    
//  pthread_join(data_table_compare_tid, NULL);
    pthread_join(module_status_tid, NULL);
    pthread_join(cpp1_status_tid, NULL);


    return 0;
}

