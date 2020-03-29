#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "file_handler.h"


#define LSEEK_START_POS_AT_ROW 12+4+1 /**bits without are + IC size + \t**/
#define START_POS_AT_ROW 4+1


void write_command_to_file(InstructionCount *ic, BitsCommand *pbc, char *filename) {
    char pcommand[PBC_COMMAND_LEN];
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
    int_to_string(ic->row, ic_as_string);
    fputs(ic_as_string, pfile);
    fputs(pcommand, pfile);
    /* Close file to save file data */
    fclose(pfile);

}

void write_entry_or_extern_to_file(int row_num, char *symbol, char *filename) {
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
    int_to_string(row_num, ic_as_string);
    fputs(ic_as_string, pfile);
    fputs(symbol, pfile);
    fputs(NEW_LINE, pfile);
    /* Close file to save file data */
    fclose(pfile);

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
        fwrite(one_bit, 1, sizeof(one_bit), pfile);
        fwrite(zero_bit, 1, sizeof(zero_bit), pfile);
        fwrite(zero_bit, 1, sizeof(zero_bit), pfile);
    } else if (are == 0) {
        fseek(pfile, LSEEK_START_POS_AT_ROW, SEEK_CUR);
        fwrite(zero_bit, 1, sizeof(zero_bit), pfile);
        fwrite(zero_bit, 1, sizeof(zero_bit), pfile);
        fwrite(one_bit, 1, sizeof(one_bit), pfile);
    }
    fclose(pfile);
}

void edit_existing_row_label_address(int row_num, int adress_of_label) {
    char binary_label_address[MAX_BITS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    if (dec_to_binary(adress_of_label, MAX_BITS, binary_label_address)) {
        change_bits_second_reading(row_num, binary_label_address);
    } else {
        printf("ERROR!\n");
    }
}

void change_bits_second_reading(int row, char *binary_label_address) {
    FILE *pfile;
    int i = 0;
    char buffer[MAX_LINE];
    char zero_bit[1] = {0}, one_bit[1] = {0};
    zero_bit[0] = '0';
    one_bit[0] = '1';
    row = row - START_ROW_NUM;
    pfile = fopen(BIN_FILENAME, "r+");

    while (row) {
        fgets(buffer, MAX_LINE, pfile);
        row--;
    }
    fseek(pfile, START_POS_AT_ROW, SEEK_CUR);
    for (i = 0; i < MAX_BITS - 3; ++i) {
        if (binary_label_address[i + 3] == 1)
            fwrite(one_bit, 1, sizeof(one_bit), pfile);
        else
            fwrite(zero_bit, 1, sizeof(zero_bit), pfile);
    }
    fclose(pfile);
}


/**The function reads the binary base file and converts it to oct base file**/
void convert_bin_file_to_oct_file(char *filename, InstructionCount *ic) {
    FILE *pbfile = NULL;
    FILE *pofile = NULL;
    char buffer[MAX_LINE];
    char oct_output[OCT_OUTPUT_LINE_SIZE];
    char oct_command[OCT_COMMAND_LEN];
    char first_line[OCT_OUTPUT_LINE_SIZE];
    char binary_to_convert[PBC_COMMAND_LEN];
    char *token;
    char sep;
    sep = '\t';
    pbfile = fopen(BIN_FILENAME, "r");
    strcat(filename, OCT_FILENAME_EXT);
    pofile = fopen(filename, "a");

    if (pbfile == NULL) {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    if (pofile == NULL) {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    first_line[0] = sep;
    sprintf(first_line + 1, "%d\t", ic->ic);
    fputs(first_line, pofile);
    first_line[1] = NULL;/**Let's copy from bit 1*/
    sprintf(first_line + 1, "%d\n", ic->dc);
    fputs(first_line, pofile);
    while (!feof(pbfile)) {
        fgets(buffer, MAX_LINE, pbfile);
        token = strtok(buffer, &sep);
        if (token == NULL) break;/**We achieved non parseable string**/
        strcpy(oct_output, token);
        oct_output[4] = sep;
        token = strtok(NULL, &sep);
        if (token == NULL)break; /**End of file**/
        strcpy(binary_to_convert, token);

        strcpy(oct_output + 5, convert_bin_to_oct(binary_to_convert, oct_command));
        oct_output[10] = NEW_LINE_AS_CHAR;
        oct_output[11] = NULL;
        fputs(oct_output, pofile);
    }

    /* Close file to save file data */
    fclose(pbfile);
    fclose(pofile);
}


