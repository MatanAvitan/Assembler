#include "assembler.h"

void run_flow(FILE *pfile, char *filename) {
    char zeroed_command[MAX_LINE] = {0};
    char command_input[MAX_LINE] = {0};
    InstructionCount *ic;
    ParsedCommand *ppc;
    ParsedInstruction *ppi;
    BitsCommand *pbc;
    SymbolsList *sl = {0};
    ReadingTwoList *rtl = {0};
    int first_round = TRUE, second_round = TRUE;
    int are, is_entry_or_extern = 0, is_labeled_command = 0, backup_row;

    ic = (InstructionCount *) malloc(sizeof(InstructionCount));
    ic->row = START_ROW_NUM;

    do {
        strcpy(command_input, zeroed_command);
        read_command(pfile, command_input);
        /**Allow ; and \n as a comment**/
        while (command_input[0] == COMMENT_MARK_CHAT || command_input[0] == NEW_LINE_AS_CHAR) {
            strcpy(command_input, zeroed_command);
            read_command(pfile, command_input);
        }
        if (command_input[0] == 0) {
            /**We achieved EOF after looping the the above while,
             * So we need to break out**/
            break;
        }
        ppc = (ParsedCommand *) malloc(sizeof(ParsedCommand));
        parse(command_input, ppc);
        if (strcmp(ppc->command, TERMINATE) == 0) {
            /**If the command parser failed to parse the command maybe it's an instruction sentence**/
            ppi = (ParsedInstruction *) malloc(sizeof(ParsedInstruction));
            /**The command parser already caught the label**/
            strcpy(ppi->label, ppc->prefix);
            first_round = parse_instruction(ic, command_input, ppi);
            if (ppi->members_num == 0) {
                /**Parsing error**/
                /**Fetch command**/
                read_command(pfile, command_input);
                /**Allow ; and \n as a comment**/
                while (command_input[0] == COMMENT_MARK_CHAT || command_input[0] == NEW_LINE_AS_CHAR) {
                    read_command(pfile, command_input);
                    /**Achieved end of file**/
                    if (feof(pfile))break;
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
                strcpy(ppc->prefix, zeroed_command);
            }
            pbc = (BitsCommand *) malloc(sizeof(BitsCommand) * ppi->members_num);
            first_round = instruction_router(filename, ic, ppi, pbc, first_round);


            free(ppi);  /**Free the previous instruction command**/
        } else {
            /**Regular command**/
            pbc = (BitsCommand *) malloc(sizeof(BitsCommand) * MAX_NUM_OF_TRANSLATION_COMMANDS);
            /**Run first time and assign all the declaration variables to three lists A, R, E.
             *Then call to the get_are(command) and pass the output to the command_router function.**/
            backup_row = START_ROW_NUM + ic->ic + ic->dc;
            are = 2;
            first_round = command_router(filename, ic, ppc, pbc, are, &rtl, &sl, first_round);
            if (strlen(ppc->prefix)) {
                is_entry_or_extern = 0;
                is_labeled_command = 1;
                ic->row = backup_row;
                first_round = valid_label(ppc->prefix, sizeof(ppc->prefix) / sizeof(char));
                add_symbol(&sl, ppc->prefix, ic, 0, 0, 0,
                           is_entry_or_extern, is_labeled_command);
            }
        }
        free(ppc);
        free(pbc);  /**Free the previous command bytes representation**/
    } while (!feof(pfile));

    /**If there are error in the first round - the program* will not continue**/
    if (first_round == TRUE) {
        second_round = validate_labels_at_second_running(filename, ic, &sl, &rtl, second_round);
        if (first_round == TRUE && second_round == TRUE) {
            convert_bin_file_to_oct_file(filename, ic);
        } else {
            printf(SECOND_ROUND_FAILED);
        }
    } else {
        printf(FIRST_ROUND_FAILED);
    }
    /**If there are errors - the program will not continue**/
    if (ic) {
        free(ic);
    }
}

int main(int argc, char **argv) {
    FILE *pfile;
    char reading_file[MAX_LINE];
    int i = 1;
    for (; i < argc; i++) {
        strcpy(reading_file, argv[i]);
        strcat(reading_file, INPUT_FILE_EXTENSION);
        pfile = fopen(reading_file, "r+");
        run_flow(pfile, argv[i]);
        fclose(pfile);
    }
    return 1;
}

