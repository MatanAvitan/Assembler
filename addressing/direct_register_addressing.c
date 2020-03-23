#include "direct_register_addressing.h"

#define NUM_OF_COMMAND 2

void run_direct_register_addressing(ParsedCommand *ppc, BitsCommand *pbc, int are) {
    int is_src_arg = 0, i = 0;

    /**First command**/
    assign_first_command(ppc, pbc, are);

    /**Second command**/
    if (ppc->args_num == 1) {
        is_src_arg = 0;
        assign_direct_and_indirect_register_number_command(ppc, pbc + 1, are, is_src_arg);
    }
    if (ppc->args_num == 2) {
        /**Both of the args are direct registers**/
        is_src_arg = 1;
        assign_direct_and_indirect_register_number_command(ppc, pbc + 1, are, is_src_arg);

        /**We already assigned the src arg to bits 6-8 in the second command,
         * so here we just adding the dst arg to bits 3-5**/
        is_src_arg = 0;
        assign_direct_and_indirect_register_number_command(ppc, pbc + 1, are, is_src_arg);
    }
    for (; i < NUM_OF_COMMAND; i++) {
        /**Write the command to the bin file**/
        write_command_to_file(pbc + i);
    }
}