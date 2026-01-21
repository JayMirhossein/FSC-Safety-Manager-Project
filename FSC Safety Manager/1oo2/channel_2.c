//
//  channel_2.c
//  1oo2
//
//  Created by Jay on 27/12/2025.
//

#include "channel_2.h"

void *channel_two(void *arg) {
    
            const char* filename = "/Users/jayziabari/Desktop/1oo2/cat1.txt";
            FILE *outfile2;
            printf("Task 2 is running on thread %ld\n", pthread_self()); //
    int i=1;
            printf("Task 2: %d\n", i);
            FILE* file = fopen(filename, "rb"); // Open in binary read mode
            if (file == NULL) {
                perror("Error opening file");
              //  return NULL;
            }
            
            // Seek to the end of the file to determine the size
            fseek(file, 0, SEEK_END);
            long length = ftell(file);
            fseek(file, 0, SEEK_SET); // Rewind to the beginning
            
            // Check for potential errors in fseek/ftell
            if (length == -1L) {
                perror("Error getting file size");
                fclose(file);
              //  return NULL;
            }
            
            // Allocate memory for the entire file content + null terminator
            char* buffer = (char*)malloc(length + 1);
            if (buffer == NULL) {
                perror("Error allocating memory");
                fclose(file);
               // return NULL;
            }
            
            // Read the file content into the buffer
            size_t bytesRead = fread(buffer, 1, length, file);
            
            // Close the file
            fclose(file);
            
            if (bytesRead != length) {
                fprintf(stderr, "Error reading file: read %zu bytes, expected %ld\n", bytesRead, length);
                free(buffer);
               // return NULL;
            }
            
            // Null-terminate the string (important for text processing)
            buffer[length] = '\\0';
            // Open a file in writing mode
            outfile2 = fopen("/Users/jayziabari/Desktop/1oo2/1oo2/outfile2.txt", "w");
            // Write buffer text to the file
            fprintf(outfile2,buffer);
            fclose(outfile2);
          //  printf(buffer,"\n");
            
           // return buffer; // Caller is responsible for freeing this memory
            printf("Task 2 finished\n");
            pthread_exit(NULL); //
    
        }
