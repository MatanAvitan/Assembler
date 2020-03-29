#ifndef FINAL_PROJECT_INSTANT_ADDRESSING_H
#define FINAL_PROJECT_INSTANT_ADDRESSING_H

#include <stdio.h>

#include "../consts.h"
#include "../parsed_command.h"
#include "../bits_command.h"
#include "addressing_utils.h"
#include "../file_handler.h"
#include "../command_router.h"
#include "../data_structures/reading_two_list.h"

void run_instant_addressing(char *filename, InstructionCount *ic, ParsedCommand *, BitsCommand *,
                            int, ReadingTwoList **);

#endif /*FINAL_PROJECT_INSTANT_ADDRESSING_H*/
