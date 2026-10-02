/*
 This file is part of the Fail-Safe Controller System (FSC) implementation.
 It manages multi-threaded processing for various FSC modules including
 analog/digital IO processing, balise reading, data table handling, and 
 monitoring of cpp1 status with fault detection and reporting.
 */

/* 
 Key Concepts:
 pthread_t: Data type to store the unique thread identifier.
 pthread_create(): Spawns new threads with specified start routines.
 pthread_join(): Waits for threads to complete to ensure ordered shutdown.
 pthread_exit(): Used to explicitly exit a thread.
*/

/*
 Fail-Safe Controller System Family Overview:
 This table summarizes different FSC system configurations, CPU architectures,
 and voting schemes used in the system's redundant architectures.
 

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
 This program implements software architecture DMR 1002D, compatible with CPU 10020/1/1  10020/1/2
*/
#define cpp_Path "/Users/jayziabari/Desktop/FSC Safety Manager 1/FSC Safety Manager/FSC-SMM Processor Resource Allocation/cpp1/cpp1_status.txt"
 
#include <stdio.h>      // Standard I/O functions
#include <stdlib.h>     // Standard library functions (malloc, free, exit)
#include <pthread.h>    // POSIX thread support
#include <unistd.h>     // Sleep, getpid(), and other POSIX functions
#include <stdbool.h>    // Boolean type support
#include <sys/types.h>  // Data types used in system calls
#include <sys/file.h>   // File locking primitives (flock)
#include <string.h>     // String manipulation functions
#include <time.h>       // Time and date functions

// Configuration header files: hardware and system configuration specifics
#include "config_load.h"
#include "FS88-501A.h"
#include "FS88-502.h"
#include "FS88-504.h"
#include "FS88-506.h"
#include "FSC_SM_AI.h"
#include "FSC_SM_DI.h"
#include "FSC_SM_DO.h"

// Main function headers: contain core functional modules
#include "file_1.h"
#include "file_2.h"
#include "compare.h"
#include "Redundnacy_Status.h"
#include "Balise_Reading.h"
#include "Data_Table.h"

 
// Tracks the timestamp when the process started for timing/fault simulation
static time_t program_start_time = 0;

// Global instance holding balise group data for balise reading operations
BaliseGroup group;

/*
 Data structure holding all status and fault flags for cpp1 processor,
 including alarms, failures, watchdog faults, and synchronization errors.
 Tracks internal state used for monitoring and reporting cpp1 health.
*/
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
    
    // Stores the current process ID of cpp1 for identification in logs
    pid_t pid ;

} cpp_Status_t;


// Thread function: Continuously reads and processes analog input points every 1 second
static void* ai_thread(void* arg) {
    while (1) {
        FSC_SM_AI(1);
        sleep(1);
    }
    return NULL;
}

// Thread function: Continuously reads and processes digital input points every 0.5 seconds
static void* di_thread(void* arg) {
    while (1) {
        FSC_SM_DI();
        usleep(500000); // sleep 0.5 seconds using microseconds
    }
    return NULL;
}

// Thread function: Performs balise reading every 10 seconds to update balise group data
static void* balise_thread(void* arg) {
    while (1) {
        Balise_Reader();
        sleep(5);
    }
    return NULL;
}

// Thread function: Processes digital output points every 0.5 seconds continuously
static void* do_thread(void* arg) {
    while (1) {
        FSC_SM_DO();
        usleep(500000); // sleep 0.5 seconds
    }
    return NULL;
}

// Thread function: Continuously updates analog input data table every 0.5 seconds
static void* data_table_thread(void* rag){
    while(1)
    {
        AI_Data_Table(0x81);
        usleep(500000); // sleep 0.5 seconds
    }
    return NULL;
}

// Thread function: Periodically compares two AI module files every 1 second for changes/differences
static void* data_table_compare_thread(void* arg) {
    while (1) {
        compareFiles("/Users/jayziabari/Desktop/FSC Safety Manager 1/FSC Safety Manager/FSC-SMM Processor Resource Allocation/Point_Processing/AI_module_11.txt" , "/Users/jayziabari/Desktop/FSC Safety Manager 1/FSC Safety Manager/FSC-SMM Processor Resource Allocation/Point_Processing/AI_module_11.txt" );
        sleep(1);
    }
    return NULL;
}

// Thread function: Displays module status every 2 seconds for diagnostics/monitoring purposes
static void* module_status_thread(void* arg) {
    while (1) {
        printf("\n%s", GetModuleStatus());
        sleep(2);
    }
    return NULL;
}

// Thread function: Monitors cpp1 processor status continuously every 2 seconds,
// updates fault flags based on runtime conditions,
// and writes status atomically to cpp1 status file with file locking to prevent race conditions.
static void* cpp1_status_thread(void* arg) {
    while (1) {
        // Initialize a local cpp1 status structure and reset fault flags
        cpp_Status_t cpp1_status = {0};
        cpp1_status.executionTimeOutFailure = false;
        cpp1_status.executionTimeOutOfRange = false;

        // Simulate a test fault: set memory failure flag after extended run time
        if (time(NULL) - program_start_time >= 150000000)
            cpp1_status.qppMemoryFailure = true;
        else
            cpp1_status.qppMemoryFailure = false;

        // Clear other fault flags by default
        cpp1_status.watchdogFaulty = false;
        cpp1_status.busDriverFaulty = false;
        cpp1_status.internalLinkFaulty = false;
        cpp1_status.nonRedundantOutputsLineFault = false;
        cpp1_status.qppModeFaulty = false;
        cpp1_status.cpp1_IO_compare_err = false;
        cpp1_status.cpp1_base_timer_IO_err = false;
        cpp1_status.cpp1_spurious_watchdog_interrupt = false;
        cpp1_status.cpp1_synchronization_err = false;

        // Retrieve current process id for this cpp1 instance
        cpp1_status.pid = getpid();
        
        // Open the cpp1 status file for writing
        FILE *file = fopen(cpp_Path, "w");
        if (file != NULL) {
            // Obtain exclusive lock on the file to prevent concurrent writes from other processes
            int fd = fileno(file);
            flock(fd, LOCK_EX);

            // Write all status flags to the file in a human-readable format
            fprintf(file, "FSC cpp1 status \n");
            fprintf(file, "executionTimeOutFailure: %d\n", cpp1_status.executionTimeOutFailure);
            fprintf(file, "qppMemoryFailure: %d\n", cpp1_status.qppMemoryFailure);
            fprintf(file, "watchdogFaulty: %d\n", cpp1_status.watchdogFaulty);
            fprintf(file, "busDriverFaulty: %d\n", cpp1_status.busDriverFaulty);
            fprintf(file, "internalLinkFaulty: %d\n", cpp1_status.internalLinkFaulty);
            fprintf(file, "nonRedundantOutputsLineFault: %d\n", cpp1_status.nonRedundantOutputsLineFault);
            fprintf(file, "qppModeFaulty: %d\n", cpp1_status.qppModeFaulty);
            fprintf(file, "IO Compare err: %d\n", cpp1_status.cpp1_IO_compare_err);
            fprintf(file, "base timer IO err: %d\n", cpp1_status.cpp1_base_timer_IO_err);
            fprintf(file, "spurious watchdog: %d\n", cpp1_status.cpp1_spurious_watchdog_interrupt);
            fprintf(file, "synch_err: %d\n", cpp1_status.cpp1_synchronization_err);
            fprintf(file, "cpp1processorpid: %d\n", cpp1_status.pid);

            // Release the file lock and close the status file
            flock(fd, LOCK_UN);
            fclose(file);
        } else {
            // File open error could be logged or handled here as needed
        }
        // Sleep for 2 seconds before next status update cycle
        sleep(2);
    }
    return NULL;
}

/// Main entry point of the program
int main(void) {
    // --- Initialization and file setup ---
    program_start_time = time(NULL);

    const char* filename = "/Users/jayziabari/Desktop/1oo2/1oo2/outfile1.txt";
    // Initial file comparison and setup of FSC modules pointing to various UCNs
    compareFiles("/Users/jayziabari/Desktop/1oo2/1oo2/outfile1.txt", "/Users/jayziabari/Desktop/1oo2/1oo2/outfile2.txt");
    FS88_501A(filename,"FS88-501A"); // NIM's UCN that SM is connected to (Process Network Number)
    FS88_501A(filename,"FS88-501B"); // NIM's UCN that SM is connected to (Process Network Number)
    FS88_502(filename,"FS88-502");   // FSC-SM Analog Input Data Point
    FS88_504(filename,"FS88-504");   // FSC-SM Digital Composite Data Point
    FS88_504(filename,"FS88-506");   // FSC-SM Digital Output Data Point
    
    // --- Thread declaration ---
    pthread_t ai_tid,
              di_tid,
              do_tid,
              balise_thread_tid,
              data_table_compare_tid,
              data_table_tid,
              module_status_tid,
              cpp1_status_tid;

    // --- Thread launching ---
    // Launch FSC_SM_AI processing thread (runs every 1 second)
    pthread_create(&ai_tid, NULL, ai_thread, NULL);
    // Launch FSC_SM_DI processing thread (runs every 0.5 seconds)
    pthread_create(&di_tid, NULL, di_thread, NULL);
    // Launch balise reading thread (runs every 10 seconds)
    pthread_create(&balise_thread_tid, NULL, balise_thread, NULL);
    // Launch FSC_SM_DO processing thread (runs every 0.5 seconds)
    pthread_create(&do_tid, NULL, do_thread, NULL);
    // Data table compare and data table threads are commented out, can be enabled if needed
    // pthread_create(&data_table_compare_tid, NULL, data_table_compare_thread, NULL);
    pthread_create(&module_status_tid, NULL, module_status_thread, NULL);
    // pthread_create(&data_table_tid, NULL, data_table_thread, NULL);
    // Launch cpp1 status monitoring thread (runs every 2 seconds)
    pthread_create(&cpp1_status_tid, NULL, cpp1_status_thread, NULL);

    // --- Thread joins and shutdown ---
    // Wait for balise_thread to finish (blocks main, others run detached)
    pthread_join(balise_thread_tid, NULL);

    // The following joins are commented out: main will block on balise_thread and cpp1_status_thread only.
    pthread_join(ai_tid, NULL);
    pthread_join(di_tid, NULL);
    pthread_join(do_tid, NULL);
    // pthread_join(data_table_tid, NULL);
    // pthread_join(data_table_compare_tid, NULL);
    pthread_join(module_status_tid, NULL);
    pthread_join(cpp1_status_tid, NULL);

    return 0;
}
