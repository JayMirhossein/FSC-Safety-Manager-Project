//
//  Redundnacy_Status.c
//  FSC Safety Manager
//
//  Created by Jay on 18/7/2026.
//

#include "Redundnacy_Status.h"
#include <stdio.h>
#include <string.h>

#define STATUS_FILE "/Users/jayziabari/Desktop/cpp_Watchdog/cpp_Watchdog/cpp_status.txt"
#define MAX_LINE 512

/*
 * Reads the latest status of cpp1 or cpp2 from the status file.
 *
 * process : "cpp1" or "cpp2"
 * status  : Output string ("RUNNING", "TERMINATED", or "UNKNOWN")
 *
 * Returns:
 *   0  = Success
 *  -1  = Could not open file
 */
int Getredundancystatus(const char *process, char *status)
{
    FILE *fp;
    char line[MAX_LINE];

    fp = fopen(STATUS_FILE, "r");
    if (fp == NULL)
    {
        perror("Unable to open status file");
        strcpy(status, "UNKNOWN");
        return -1;
    }

    strcpy(status, "UNKNOWN");

    /* Read the entire file so the last occurrence is kept */
    while (fgets(line, sizeof(line), fp))
    {
        if (strstr(line, process) != NULL)
        {
            if (strstr(line, "RUNNING") != NULL)
            {
                strcpy(status, "RUNNING");
            }
            else if (strstr(line, "TERMINATED") != NULL)
            {
                strcpy(status, "TERMINATED");
            }
        }
    }

    fclose(fp);
    return 0;
}

int main(void)
{
    char cpp1Status[20];
    char cpp2Status[20];

    Getredundancystatus("cpp1", cpp1Status);
    Getredundancystatus("cpp2", cpp2Status);

    printf("cpp1 Status: %s\n", cpp1Status);
    printf("cpp2 Status: %s\n", cpp2Status);

    return 0;
}
