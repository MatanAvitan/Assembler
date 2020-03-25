//
// Created by ma on 19/03/2020.
//

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

#endif //FINAL_PROJECT_FILE_HANDLER_H
