#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include "file_handler.h"


int ic = 100;

void write_command_to_file(BitsCommand *pbc, char *filename) {
    char pcommand[17];
    FILE *pfile = NULL;
    convert_pbc_to_pchar(pcommand, pbc);

    pfile = fopen(filename, "a");

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
    ic++;

}

void write_entry_or_extern_to_file(ParsedInstruction *ppi, char *filename) {
    FILE *pfile = NULL;
    char ic_as_string[IC_CHARS];

    pfile = fopen(filename, "a");

    /* fopen() return NULL if last operation was unsuccessful */
    if (pfile == NULL) {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    /* Write data to file */
    int_to_string(ic, ic_as_string);
    fputs(ic_as_string, pfile);
    fputs(ppi->list.val_for_labels, pfile);
    fputs(NEW_LINE, pfile);
    /* Close file to save file data */
    fclose(pfile);

    ic++;
}

void edit_existing_row_are(int row, int are) {
    FILE *pfile;
    char buffer[MAX_LINE];

    pfile = fopen(BIN_FILENAME, "r+");

    while (row) {
        fgets(buffer, MAX_LINE, pfile);
        row--;
    }
    lseek(pfile, 12 + (3 - are), 1);
}


