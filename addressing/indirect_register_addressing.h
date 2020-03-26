//
// Created by ma on 16/03/2020.
//

#ifndef FINAL_PROJECT_INDIRECT_REGISTER_ADDRESSING_H
#define FINAL_PROJECT_INDIRECT_REGISTER_ADDRESSING_H

#include "../parsed_command.h"
#include "../bits_command.h"
#include "../consts.h"
#include "addressing_utils.h"
#include "../data_structures/reading_two_list.h"

void run_indirect_register_addressing(InstructionCount *ic, ParsedCommand *, BitsCommand *, int, ReadingTwoList **);

#endif /*FINAL_PROJECT_INDIRECT_REGISTER_ADDRESSING_H*/
