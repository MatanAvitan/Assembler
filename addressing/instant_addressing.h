#include <stdio.h>

#include "../consts.h"
#include "../parsed_command.h"
#include "../bits_command.h"
#include "addressing_utils.h"
#include "../file_handler.h"
#include "../command_router.h"
#include "../data_structures/reading_two_list.h"

void run_instant_addressing(ParsedCommand *, BitsCommand *, int, ReadingTwoList **);