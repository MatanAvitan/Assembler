
#ifndef FINAL_PROJECT_FILE_HANDLER_H
#define FINAL_PROJECT_FILE_HANDLER_H

#include <stdio.h>
#include "consts.h"
#include "bits_command.h"
#include "addressing/addressing_utils.h"
#include "parsed_instruction.h"


void write_command_to_file(BitsCommand *pbc, char *filename);

void write_entry_or_extern_to_file(ParsedInstruction *ppi, char *filename);

void edit_existing_row_are(int row, int are);

void edit_existing_row_label_adress(int row_num, int adress_of_label);

void change_bits_second_reading(int row_num, char binary_label_address[]);

void create_hex_file(int row, char *filename);

#endif /*FINAL_PROJECT_FILE_HANDLER_H*/
