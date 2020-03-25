#ifndef FINAL_PROJECT_DIRECT_ADDRESSING_H
#define FINAL_PROJECT_DIRECT_ADDRESSING_H

#include <stdio.h>

#include "../consts.h"
#include "../utils.h"
#include "../parsed_command.h"
#include "../bits_command.h"
#include "addressing_utils.h"
#include "../file_handler.h"
#include "../data_structures/reading_two_list.h"

void run_direct_addressing(ParsedCommand *ppc, BitsCommand *pbc, int are, ReadingTwoList **rtl);

#endif /*FINAL_PROJECT_DIRECT_ADDRESSING_H*/
