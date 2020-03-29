#include "instant_addressing.h"

/*The function translating the command to bits by instant addressing method*/
void run_instant_addressing(char *filename, InstructionCount *ic,
                            ParsedCommand *ppc, BitsCommand *pbc, int are, ReadingTwoList **rtl) {

    /**In both addressing methods the are is 1**/
    int is_src_arg = 0, i = 0;

    /**First command**/
    assign_first_command(ppc, pbc, are);
    if (ppc->args_num == 1) {
        if (ppc->dst_addressing_method == INSTANT_ADDRESSING_NO) {
            /**Second command**/
            is_src_arg = -1;
            assign_instant_command(ppc, pbc + 1, are, is_src_arg);
        }
    }
    if (ppc->args_num == 2) {
        if (ppc->src_addressing_method == INSTANT_ADDRESSING_NO) {
            /**Second command**/
            is_src_arg = 1;
            assign_instant_command(ppc, pbc + 1, are, is_src_arg);

            /**Third command**/

            /*is_src_arg = 0;*/
            is_src_arg = -1;
            assign_direct_register_value_command(ppc, pbc + 2, are, is_src_arg);

            if (is_label(ppc->dst) == TRUE) {
                /*address of the label - second reading*/
                add_second_reading_line(rtl, ppc->dst, ppc + 2, NULL, pbc, ic->row + 2);
            }

        } else {
            /**Second command**/
            is_src_arg = 1;
            assign_direct_register_value_command(ppc, pbc + 1, are, is_src_arg);

            /**Third command**/
            /*is_src_arg = 0;*/
            is_src_arg = -1;
            assign_instant_command(ppc, pbc + 2, are, is_src_arg);

            if (is_label(ppc->src) == TRUE) {
                /**address of the label - second reading**/
                add_second_reading_line(rtl, ppc->src, ppc + 1, NULL, pbc, ic->row + 1);
            }

        }
    }
    for (; i < ppc->args_num + 1; i++) {
        /**Write the command to the bin file**/
        ic->row = START_ROW_NUM + ic->ic + ic->dc;
        write_command_to_file(ic, pbc + i, filename);
        ic->ic++;
        ic->row = START_ROW_NUM + ic->dc + ic->ic;
    }

}
