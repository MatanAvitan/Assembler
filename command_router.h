#include "parsed_command.h"
#include "bits_command.h"
#include "data_structures/reading_two_list.h"


void command_router(ParsedCommand *ppc, BitsCommand *pbc, int are, ReadingTwoList **rtl);

int to_decimal(char *number);

int compare_register(char *cmp);

int command_instant_address(char *command);

int command_direct_and_indirect_register_address(char* command);

int command_indirect_register_address_dst_arg_only(char* command);

int command_direct_register_address(char* command);

int command_direct_address_dst_arg_only(char* command);

int compare_register(char *cmp);