//
//  Balise_Reading.c
//  FSC Safety Manager
//
//  Created by Jay on 3/8/2026.
//

#include "Balise_Reading.h"

int Balise_Reader(void)
{
    FILE *inputFile;
    BaliseGroup balise_ref;
    BaliseGroup balise_next;

    int firstBalise = 1;

    /*
     * Open balise input file
     */
    inputFile = fopen(BALISE_FILE, "r");

    if (inputFile == NULL)
    {
        perror("ERROR: Could not open balise group file");
        return EXIT_FAILURE;
    }

    printf("========================================\n");
    printf("       BALISE GROUP READER\n");
    printf("========================================\n");
    printf("Input file:\n%s\n\n", BALISE_FILE);
    printf("Reading one balise every 5 seconds...\n\n");

    /*
     * Read balise groups from file
     */
    while (fscanf(inputFile,
                  " Group %d: NI_DBG=%d, N_PIG=%d, NI_DC=%d, NI_D=%d",
                  &balise_next.groupNumber,
                  &balise_next.NI_DBG,
                  &balise_next.N_PIG,
                  &balise_next.NI_DC,
                  &balise_next.NI_D) == 5)
    {
        /*
         * First balise (Reference Balise)
         * There is no previous balise to compare with henve this balise is the reference
         */
        if (firstBalise)
        {
            printf("REFERENCE BALISE GROUP\n");

            printf("Group Number : %d\n", balise_next.groupNumber);
            printf("NI_DBG       : %d\n", balise_next.NI_DBG);
            printf("N_PIG        : %d\n", balise_next.N_PIG);
            printf("NI_DC        : %d\n", balise_next.NI_DC);
            printf("NI_D         : %d\n", balise_next.NI_D);

            printf("----------------------------------------\n");

            /*
             * Store this balise as the reference
             * for the next comparison.
             */
            balise_ref = balise_next;

            firstBalise = 0;
        }
        else
        {
            /*
             * Compare the new balise with
             * the previous balise.
             */

            printf("NEW BALISE GROUP\n");

            printf("Group Number : %s (%d -> %d)\n",
                   (balise_next.groupNumber == balise_ref.groupNumber)
                   ? "SAME" : "DIFFERENT",
                   balise_ref.groupNumber,
                   balise_next.groupNumber);

            printf("NI_DBG       : %s (%d -> %d)\n",
                   (balise_next.NI_DBG > balise_ref.NI_DBG)
                   ? "FWD" : "REV",
                   balise_ref.NI_DBG,
                   balise_next.NI_DBG);

            printf("N_PIG        : %s (%d -> %d)\n",
                   (balise_next.N_PIG > balise_ref.N_PIG)
                   ? "FWD" : "REV",
                   balise_ref.N_PIG,
                   balise_next.N_PIG);

            printf("NI_DC        : %s (%d -> %d)\n",
                   (balise_next.NI_DC > balise_ref.NI_DC)
                   ? "FWD" : "REV",
                   balise_ref.NI_DC,
                   balise_next.NI_DC);

            printf("NI_D         : %s (%d -> %d)\n",
                   (balise_next.NI_D > balise_ref.NI_D)
                   ? "FWD" : "REV",
                   balise_ref.NI_D,
                   balise_next.NI_D);

            printf("----------------------------------------\n");

            /*
             * The current balise becomes the previous
             * balise for the next iteration.
             */
            balise_ref = balise_next;
        }

        /*
         * Wait 5 seconds before reading
         * the next balise.
         */
        sleep(5);
    }

    /*
     * Close file
     */
    fclose(inputFile);

    printf("\n========================================\n");
    printf("All balise entries have been processed.\n");
    printf("========================================\n");

    return EXIT_SUCCESS;
}
