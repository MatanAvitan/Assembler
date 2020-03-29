#include <stdlib.h>
#include "consts.h"
#include "input.h"
#include "command_router.h"
#include "parsed_instruction.h"
#include "instruction_router.h"
#include "data_structures/symbols_list.h"
#include "data_structures/reading_two_list.h"
#include "utils.h"
#include "file_handler.h"
#include "data_structures/instruction_counter.h"
#include "validator.h"


int main() {
    char command_input[MAX_LINE] = {0};
    char copy_input[MAX_LINE] = {0};
    InstructionCount *ic;
    ParsedCommand *ppc;
    ParsedInstruction *ppi;
    BitsCommand *pbc;
    SymbolsList *sl = {0};
    ReadingTwoList *rtl = {0};
    int first_round = TRUE, second_round = TRUE;
    int first_input = 1; /*1 is command, 0 is instruction*/
    int are, is_entry_or_extern = 0, is_labeled_command = 0, backup_row;

    read_command(command_input);
    /**Allow ; and \n as a comment**/
    while (command_input[0] == COMMENT_MARK_CHAT || command_input[0] == NEW_LINE_AS_CHAR) {
        read_command(command_input);
    }
    strcpy(copy_input, command_input);

    ppc = (ParsedCommand *) malloc(sizeof(ParsedCommand));
    ppc = parse(copy_input, ppc);

    ppi = (ParsedInstruction *) malloc(sizeof(ParsedInstruction));
    strcpy(ppi->label, ppc->prefix);
    first_round = parse_instruction(copy_input, ppi);

    if (strcmp(ppc->command, TERMINATE) == 0) {
        first_input = 0;
    }

    ic = (InstructionCount *) malloc(sizeof(InstructionCount));
    ic->row = START_ROW_NUM;
    while (strcmp(command_input, COMMAND_END_FILE) != 0) {
        if (strcmp(ppc->command, TERMINATE) == 0) {
            /**If the command parser failed to parse the command maybe it's an instruction sentence**/
            if (first_input != 0) {
                ppi = (ParsedInstruction *) malloc(sizeof(ParsedInstruction));
                /**The command parser already caught the label**/
                strcpy(ppi->label, ppc->prefix);
                first_round = parse_instruction(command_input, ppi);
            } else {
                first_input = -1;
            }
            if (ppi->members_num == 0) {
                /**Parsing error**/
                /**Fetch command**/
                read_command(command_input);
                /**Allow ; and \n as a comment**/
                while (command_input[0] == COMMENT_MARK_CHAT || command_input[0] == NEW_LINE_AS_CHAR) {
                    read_command(command_input);
                }
                continue;
            } else {
                /**We have a valid instruction sentence command**/
                if (strlen(ppi->label) != 0) {
                    if (strlen(ppi->list.val_for_labels) != 0) {
                        is_entry_or_extern = 1;
                    }
                    is_labeled_command = 0;
                    if (strlen(ppi->label) &&
                        (ppi->instruction_type == ENTRY_NO || ppi->instruction_type == EXTERN_NO)) {
                        if (ppi->instruction_type == EXTERN_NO) {
                            ic->row = START_ROW_NUM + ic->ic + ic->dc;
                            add_symbol(&sl, ppi->label, ic, ppi->instruction_type, ppi->list.val,
                                       ppi->list.val_for_labels,
                                       is_entry_or_extern, is_labeled_command);
                        } else {
                            /**If it's an entry or extern label than just override the given label by the first given value**/
                            ic->row = START_ROW_NUM + ic->ic + ic->dc;
                            strcpy(ppi->label, ppi->list.val_for_labels);
                            add_second_reading_line(&rtl, ppi->label, ppc, ppi, pbc, ic->row);
                        }
                    }
                    if (strlen(ppi->label) &&
                        (ppi->instruction_type != ENTRY_NO && ppi->instruction_type != EXTERN_NO)) {
                        ic->row = START_ROW_NUM + ic->ic + ic->dc;
                        add_symbol(&sl, ppi->label, ic, ppi->instruction_type, ppi->list.val,
                                   ppi->list.val_for_labels,
                                   is_entry_or_extern, is_labeled_command);

                    }
                }
                /**Let's zero the label for this command in case that the next command will have not have label,
                 * it cause a bug that the next command will be considered as command with this label.**/
                strcpy(ppc->prefix, "");
            }
            pbc = (BitsCommand *) malloc(sizeof(BitsCommand) * ppi->members_num);
            first_round = instruction_router(ic, ppi, pbc, first_round);

            /**Fetch command**/
            read_command(command_input);
            /**Allow ; and \n as a comment**/
            while (command_input[0] == COMMENT_MARK_CHAT || command_input[0] == NEW_LINE_AS_CHAR) {
                read_command(command_input);
            }
            ppc = parse(command_input, ppc);
            free(ppi);  /**Free the previous instruction command**/
            free(pbc);  /**Free the previous command bytes representation**/
            continue;
            /*} else {
                /**We got stop command**/
            /* break;
         }*/

        } else {
            /**Regular command**/
            pbc = (BitsCommand *) malloc(sizeof(BitsCommand) * MAX_NUM_OF_TRANSLATION_COMMANDS);
            /**Run first time and assign all the declaration variables to three lists A, R, E.
             *Then call to the get_are(command) and pass the output to the command_router function.**/
            backup_row = START_ROW_NUM + ic->ic + ic->dc;
            are = 2;
            first_round = command_router(ic, ppc, pbc, are, &rtl, &sl, first_round);
            if (strlen(ppc->prefix)) {
                is_entry_or_extern = 0;
                is_labeled_command = 1;
                ic->row = backup_row;
                first_round = valid_label(ppc->prefix);
                add_symbol(&sl, ppc->prefix, ic, NULL, NULL, NULL,
                           is_entry_or_extern, is_labeled_command);
            }
            /**Fetch command**/
            read_command(command_input);
            /**Allow ; and \n as a comment**/
            while (command_input[0] == COMMENT_MARK_CHAT || command_input[0] == NEW_LINE_AS_CHAR) {
                read_command(command_input);
            }
            ppc = parse(command_input, ppc);
        }

    }

    /*if there are error in the first round - the program* will not continue*/
    if (first_round == TRUE) {
        second_round = validate_labels_at_second_running(ic, &sl, &rtl, second_round);
        if (first_round == TRUE && second_round == TRUE) {
            convert_bin_file_to_oct_file(ic);
        } else {
            printf(SECOND_ROUND_FAILD);
        }
    } else {
        printf(FIRST_ROUND_FAILD);
    }
    /**If there are errors - the program will not continue**/
    if (ppc) {
        free(ppc);
    }
    if (ic) {
        free(ic);
    }
}
