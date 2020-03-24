#include "instant_addressing.h"


void run_instant_addressing(ParsedCommand *ppc, BitsCommand *pbc, int are) {

    /**In both addressing methods the are is 1**/
    int is_src_arg = 0, i = 0;

    /**First command**/
    assign_first_command(ppc, pbc, are);

    if (ppc->src_addressing_method == INSTANT_ADDRESSING_NO) {
        /**Second command**/
        is_src_arg = 1;
        assign_instant_command(ppc, pbc + 1, are, is_src_arg);

        /**Third command**/
        is_src_arg = 0;
        assign_direct_register_value_command(ppc, pbc + 2, are, is_src_arg);
    } else {
        /**Second command**/
        is_src_arg = 1;
        assign_direct_register_value_command(ppc, pbc + 1, are, is_src_arg);

        /**Third command**/
        is_src_arg = 0;
        assign_instant_command(ppc, pbc + 2, are, is_src_arg);

    }
    for (; i < ppc->args_num + 1; i++) {
        /**Write the command to the bin file**/
        write_command_to_file(pbc + i, BIN_FILENAME);
    }

}