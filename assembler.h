#ifndef FINAL_PROJECT_ASSEMBLER_H
#define FINAL_PROJECT_ASSEMBLER_H

#include <stdlib.h>
#include "consts.h"
#include "input.h"
#include "command_router.h"
#include "parsed_instruction.h"
#include "instruction_router.h"
#include "data_structures/symbols_list.h"
#include "data_structures/reading_two_list.h"
#include "utils.h"
#include "file_handler.h"
#include "data_structures/instruction_counter.h"
#include "validator.h"


void run_flow(FILE *pfile, char *filename);

#endif //FINAL_PROJECT_ASSEMBLER_H
