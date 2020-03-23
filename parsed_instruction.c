#include "parsed_instruction.h"

int get_instruction_type(char *instruction) {
    if (strcmp(instruction, DATA) == 0)
        return DATA_NO;
    if (strcmp(instruction, STRING) == 0)
        return STRING_NO;
    if (strcmp(instruction, ENTRY) == 0)
        return ENTRY_NO;
    if (strcmp(instruction, EXTERN) == 0)
        return EXTERN_NO;

}

void parse_instruction(char *command, ParsedInstruction *ppi) {
    char seps[] = " ,\t\n";
    char label[MAX_INSTRUCTION_LEN];
    char *token;
    char instruction[MAX_INSTRUCTION_LEN];
    LinkedList *node, *runner;

    ppi->members_num = 0;
    token = strtok(command, seps);
    if (token[0] == '.') {
        strcpy(instruction, token + 1);
        ppi->instruction_type = get_instruction_type(instruction);
    }
    token = strtok(NULL, seps);
    if (token) {
        node = (LinkedList *) malloc(sizeof(LinkedList));
        node->val = atoi(token);
        node->next = NULL;
        ppi->list = *node;
        ppi->members_num += 1;
    }
    token = strtok(NULL, seps);
    while (token) {
        node = (LinkedList *) malloc(sizeof(LinkedList));
        node->val = atoi(token);
        node->next = NULL;
        runner = &ppi->list;
        while (runner->next) runner = runner->next;
        runner->next = node;
        ppi->members_num += 1;
        token = strtok(NULL, seps);
    }
}

