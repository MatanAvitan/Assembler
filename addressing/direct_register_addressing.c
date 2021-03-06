#include "direct_register_addressing.h"


void run_direct_register_addressing(char *filename, InstructionCount *ic, ParsedCommand *ppc, BitsCommand *pbc, int are,
                                    ReadingTwoList **rtl) {
    /**The function translating the command to bits by direct register addressing method**/

    int is_src_arg = 0, i = 0;
    int num_of_command = 2; /**If there is no label the number of output command is 2**/

    /**First command**/
    assign_first_command(ppc, pbc, are);

    /**Second command**/
    if (ppc->args_num == 1) {
        is_src_arg = -1;
        assign_direct_and_indirect_register_number_command(ppc, pbc + 1, are, is_src_arg);
    }
    if (ppc->args_num == 2) {
        if ((ppc->src_addressing_method == INDIRECT_REGISTER_ADDRESSING_NO ||
             ppc->src_addressing_method == DIRECT_REGISTER_ADDRESSING_NO) &&
            (ppc->dst_addressing_method == INDIRECT_REGISTER_ADDRESSING_NO ||
             ppc->dst_addressing_method == DIRECT_REGISTER_ADDRESSING_NO)) {
            /**Both of the args are direct or indirect registers**/
            is_src_arg = 1;
            assign_direct_and_indirect_register_number_command(ppc, pbc + 1, are, is_src_arg);

            /**We already assigned the src arg to bits 6-8 in the second command,
             * so here we just adding the dst arg to bits 3-5**/
            is_src_arg = 0;
            assign_direct_and_indirect_register_number_command(ppc, pbc + 1, are, is_src_arg);
        } else if (ppc->src_addressing_method == DIRECT_REGISTER_ADDRESSING_NO &&
                   ppc->dst_addressing_method == DIRECT_ADDRESSING_NO) {
            /**The src arg is direct register and the dst arg is unknown**/
            is_src_arg = 1;
            assign_direct_and_indirect_register_number_command(ppc, pbc + 1, are, is_src_arg);

            if (is_label(ppc->dst) == TRUE) {
                ic->row = START_ROW_NUM + ic->ic + ic->dc;
                add_second_reading_line(rtl, ppc->dst, ppc + 2, NULL, pbc, ic->row + 2);
            }

            num_of_command += 1;
        } else if (ppc->src_addressing_method == DIRECT_ADDRESSING_NO &&
                   ppc->dst_addressing_method == DIRECT_REGISTER_ADDRESSING_NO) {
            /**The src arg is unknown and the dst arg is direct register**/
            if (is_label(ppc->src) == TRUE) {
                ic->row = START_ROW_NUM + ic->ic + ic->dc;
                add_second_reading_line(rtl, ppc->src, ppc + 1, NULL, pbc, ic->row + 1);
            }
            num_of_command += 1;

            is_src_arg = 0;

            assign_direct_and_indirect_register_number_command(ppc, pbc + 2, are, is_src_arg);
        }
    }
    for (; i < num_of_command; i++) {
        /**Write the command to the bin file**/
        ic->row = START_ROW_NUM + ic->ic + ic->dc;
        write_command_to_file(ic, pbc + i, filename);
        ic->ic++;
        ic->row = START_ROW_NUM + ic->dc + ic->ic;

    }
}
