
#include <stdio.h>

#include "direct_addressing.h"

/*The function translating the command to bits by direct addressing method*/
void run_direct_addressing(char *filename,InstructionCount *ic, ParsedCommand *ppc, BitsCommand *pbc, int are, ReadingTwoList **rtl) {

    /**FIRST*/

    int i = 0;

    /**First command**/
    assign_first_command(ppc, pbc, are);


    /**SECOND**/
    /**address of the label - second reading**/
    if (ppc->args_num == 1) {
        ic->row = START_ROW_NUM + ic->ic + ic->dc;
        add_second_reading_line(rtl, ppc->dst, ppc,NULL, pbc + 1, ic->row + 1);

    } else if (ppc->args_num == 2) {
        /*two labels - add to the second reading list*/
        ic->row = START_ROW_NUM + ic->ic + ic->dc;
        add_second_reading_line(rtl, ppc->src, ppc, NULL,pbc + 1, ic->row + 1);
        add_second_reading_line(rtl, ppc->dst, ppc, NULL,pbc + 2, ic->row + 2);
    }

    for (; i < ppc->args_num + 1; i++) {
        /**Write the command to the bin file**/
        ic->row = START_ROW_NUM + ic->ic + ic->dc;
        write_command_to_file(ic, pbc + i, filename);
        ic->ic++;
        ic->row = START_ROW_NUM + ic->dc + ic->ic;
    }
}
