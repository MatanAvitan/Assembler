#include "parsed_command.h"
#include "bits_command.h"


void routing(ParsedCommand *ppc, BitsCommand *pbc, int are);

int to_decimal(char *number);

int compare_register(char *cmp);

int command_instant_address(char *command);

int command_direct_and_indirect_register_address(char* command);

int command_indirect_register_address_dst_arg_only(char* command);

int command_direct_register_address(char* command);

int command_direct_address_dst_arg_only(char* command);