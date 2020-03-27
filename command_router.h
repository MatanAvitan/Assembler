#ifndef FINAL_PROJECT_COMMAND_ROUTER_H
#define FINAL_PROJECT_COMMAND_ROUTER_H

#include "parsed_command.h"
#include "bits_command.h"
#include "validator.h"
#include "data_structures/reading_two_list.h"
#include "data_structures/symbols_list.h"

#define THE_REGISTER "ERROR! The register "
#define THE_COMMMAND "ERROR! The command "
#define INVALID_REGISTER_NAME " is invalid register name"
#define INVALID_COMMAND_INDIRECT " is invalid command for the following indirect registers"


int command_router(InstructionCount *ic,ParsedCommand *ppc, BitsCommand *pbc, int are, ReadingTwoList **rtl, SymbolsList **psl, int no_errors);

int to_decimal(char *number);

int compare_register(char *cmp);

int command_instant_address(char *command);

int command_direct_and_indirect_register_address(char* command);

int command_indirect_register_address_dst_arg_only(char* command);

int command_direct_register_address(char* command);

int command_direct_address_dst_arg_only(char* command);

int compare_register(char *cmp);

#endif /*FINAL_PROJECT_COMMAND_ROUTER_H*/
