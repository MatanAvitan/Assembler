#ifndef FINAL_PROJECT_DIRECT_REGISTER_ADDRESSING
#define FINAL_PROJECT_DIRECT_REGISTER_ADDRESSING

#include <stdio.h>

#include "../consts.h"
#include "../utils.h"
#include "../parsed_command.h"
#include "../bits_command.h"
#include "../file_handler.h"
#include "addressing_utils.h"
#include "../data_structures/reading_two_list.h"
#include "../data_structures/instruction_counter.h"


void run_direct_register_addressing(InstructionCount *ic, ParsedCommand *ppc, BitsCommand *pbc, int, ReadingTwoList **);

#endif /*FINAL_PROJECT_DIRECT_REGISTER_ADDRESSING*/