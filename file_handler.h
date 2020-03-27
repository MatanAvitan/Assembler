
#ifndef FINAL_PROJECT_FILE_HANDLER_H
#define FINAL_PROJECT_FILE_HANDLER_H

#include <stdio.h>
#include "consts.h"
#include "bits_command.h"
#include "addressing/addressing_utils.h"
#include "parsed_instruction.h"
#include "data_structures/instruction_counter.h"


void write_command_to_file(InstructionCount *ic, BitsCommand *pbc, char *filename);

void write_entry_or_extern_to_file(InstructionCount *ic, char *symbol, char *filename) ;

void edit_existing_row_are(int row, int are);

void edit_existing_row_label_address(int row_num, int adress_of_label);

void change_bits_second_reading(int row_num, char *binary_label_address);

void convert_bin_file_to_oct_file(InstructionCount *ic);

#endif /*FINAL_PROJECT_FILE_HANDLER_H*/
