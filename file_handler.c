#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "file_handler.h"

#define LSEEK_START_POS_AT_ROW 12+4+1 /**bits without are + IC size + \t**/
#define START_POS_AT_ROW 4+1

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

void edit_existing_row_label_adress(int row_num, int adress_of_label)
{
    char binary_label_address[MAX_BITS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    if (dec_to_binary(adress_of_label, MAX_BITS, binary_label_address))
    {
        change_bits_second_reading(row_num,binary_label_address);
    }
    else
    {
        printf("ERROR!\n");
    }
}

void change_bits_second_reading(int row, char binary_label_address[])
{
    FILE *pfile;
    int i = 0;
    char buffer[MAX_LINE];
    char zero_bit[1] = {0}, one_bit[1] = {0};
    strcpy(zero_bit, "0");
    strcpy(one_bit, "1");
    row = row - START_ROW_NUM;
    pfile = fopen(BIN_FILENAME, "r+");

    while (row) {
        fgets(buffer, MAX_LINE, pfile);
        row--;
    }
    fseek(pfile, START_POS_AT_ROW, SEEK_CUR);
    for (i = 0; i < MAX_BITS-3; ++i)
    {
        if(binary_label_address[i+3] == 1)
            fwrite(one_bit, 1, sizeof(one_bit), pfile);
        else
            fwrite(zero_bit, 1, sizeof(zero_bit), pfile);
    }
    fclose(pfile);
}
