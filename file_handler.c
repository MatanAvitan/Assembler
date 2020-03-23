#include <stdio.h>
#include <stdlib.h>
#include "file_handler.h"


int ic = 100;

void write_command_to_file(BitsCommand *pbc) {
    char pcommand[17];
    FILE *pfile = NULL;
    convert_pbc_to_pchar(pcommand, pbc);

    pfile = fopen(BIN_FILENAME, "a");
    ic++;

    /* fopen() return NULL if last operation was unsuccessful */
    if (pfile == NULL) {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    /* Write data to file */
    fputs(pcommand, pfile);
    /* Close file to save file data */
    fclose(pfile);
}