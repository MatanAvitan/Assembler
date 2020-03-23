#ifndef FINAL_PROJECT_ADDRESSING_UTILS_H
#define FINAL_PROJECT_ADDRESSING_UTILS_H


#include <string.h>

#include "../consts.h"
#include "../bits_command.h"
#include "../parsed_command.h"
#include "../utils.h"
#include "../file_handler.h"
#include <stdlib.h>



int to_opcode(char *command);

void binary_to_bits(BitsCommand *pbc, int opcode_binary);

void assign_command_bits(ParsedCommand *ppc, BitsCommand *pbc);

void assign_src_arg_bits(ParsedCommand *ppc, BitsCommand *pbc);

void assign_dst_arg_bits(ParsedCommand *ppc, BitsCommand *pbc);

void assign_are_bits(BitsCommand *pbc, int are);

void convert_pbc_to_pchar(char *pcommand, BitsCommand *pbc);

void assign_first_command(ParsedCommand *ppc, BitsCommand *pbc, int are);

void assign_instant_command(ParsedCommand *ppc, BitsCommand *pbc, int are, int is_src_arg_instant_addr);

void assign_direct_register_value_command(ParsedCommand *ppc, BitsCommand *pbc, int are,
                                          int is_src_arg_direct_register_addr);


void assign_direct_register_number_command(ParsedCommand *ppc, BitsCommand *pbc, int are,
                                           int is_src_arg_direct_register_addr);




#endif //FINAL_PROJECT_ADDRESSING_UTILS_H
