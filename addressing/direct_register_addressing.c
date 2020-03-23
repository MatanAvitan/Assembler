#include "direct_register_addressing.h"

void run_direct_register_addressing(ParsedCommand *ppc, BitsCommand *pbc, int are) {
    int is_src_arg = 0, i = 0;

    /**First command**/
    assign_first_command(ppc, pbc, are);

    if (ppc->src_addressing_method == DIRECT_REGISTER_ADDRESSING_NO) {
        /**Second command**/
        is_src_arg = 1;
        assign_direct_register_value_command(ppc, pbc + 1, are, is_src_arg);

    }
    if (ppc->args_num == 2) {
        is_src_arg = 0;
        /**We already assigned the src arg to bits 6-8 in the second command,
         * so here we just adding the dst arg to bits 3-5**/
        assign_direct_register_number_command(ppc, pbc + 1, are, is_src_arg);
    }
    for (; i < ppc->args_num + 1; i++) {
        /**Write the command to the bin file**/
        write_command_to_file(pbc + i);
    }
}