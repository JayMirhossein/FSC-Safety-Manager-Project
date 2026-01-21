//
//  channel_1.c
//  1oo2
//
//  Created by Jay on 27/12/2025.
//
#include "channel_1.h"

void *channel_one(void *arg){
    
    /* declare a file pointer */
    FILE    *infile, *outfile1;
    char    *buffer;
    long    numbytes;
    
    printf("Task 1 is running on thread %ld\n", pthread_self()); //
    /* open an existing file for reading */
    infile = fopen("/Users/jayziabari/Desktop/1oo2/cat1.txt", "r");
    
    /* quit if the file does not exist */
    if(infile == NULL)
        return 1;
        
    /* Get the number of bytes */
    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);
     
    /* reset the file position indicator to
    the beginning of the file */
    fseek(infile, 0L, SEEK_SET);
     
    /* grab sufficient memory for the
    buffer to hold the text */
    buffer = (char*)calloc(numbytes, sizeof(char));
     
    /* memory error */
    if(buffer == NULL)
        return 1;
     
    /* copy all the text into the buffer */
    fread(buffer, sizeof(char), numbytes, infile);
    fclose(infile);

    // Open a file in writing mode
    outfile1 = fopen("/Users/jayziabari/Desktop/1oo2/1oo2/outfile1.txt", "w");
    // Write buffer text to the file
    fprintf(outfile1,buffer);
    fclose(outfile1);
    
    /* confirm we have read the file by
    outputing it to the console */
   // printf("The file called test.dat contains this text\n\n%s", buffer);

    /* free the memory we used for the buffer */
    free(buffer);
    
    printf("Task 1 finished\n");
    pthread_exit(NULL); //
}


