#ifndef FINAL_PROJECT_INSTRUCTION_SENTENCES
#define FINAL_PROJECT_INSTRUCTION_SENTENCES

#include <stdio.h>

#include "consts.h"
#include "file_handler.h"
#include "bits_command.h"
#include "utils.h"
#include "parsed_instruction.h"


void run_instruction_sentences(ParsedInstruction *ppi, BitsCommand *pbc);
void assign_arg_to_all_bits(BitsCommand *pbc, int binary_arg);


#endif /*FINAL_PROJECT_INSTRUCTION_SENTENCES*/