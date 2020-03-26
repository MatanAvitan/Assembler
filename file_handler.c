#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "file_handler.h"

#define LSEEK_START_POS_AT_ROW 12+4+1 /**bits without are + IC size + \t**/

int ic = START_ROW_NUM;

void write_command_to_file(BitsCommand *pbc, char *filename) {
    char pcommand[17];
    char ic_as_string[IC_CHARS];
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
    int_to_string(ic, ic_as_string);
    fputs(ic_as_string, pfile);
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
    char zero_bit[1], one_bit[1];
    zero_bit[0] = '0';
    one_bit[0] = '1';
    row = row - START_ROW_NUM;
    pfile = fopen(BIN_FILENAME, "r+");

    while (row) {
        fgets(buffer, MAX_LINE, pfile);
        row--;
    }
    if (are == 1) {
        fseek(pfile, LSEEK_START_POS_AT_ROW, SEEK_CUR);
        fwrite(zero_bit, 1, sizeof(zero_bit), pfile);
        fwrite(one_bit, 1, sizeof(one_bit), pfile);
        fwrite(zero_bit, 1, sizeof(zero_bit), pfile);
    } else if (are == 2) {
        fseek(pfile, LSEEK_START_POS_AT_ROW, SEEK_CUR);
        fwrite(zero_bit, 1, sizeof(zero_bit), pfile);
        fwrite(zero_bit, 1, sizeof(zero_bit), pfile);
        fwrite(one_bit, 1, sizeof(one_bit), pfile);
    }
    fclose(pfile);
}


