#include "parsed_instruction.h"
#include "utils.h"

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

int parse_instruction(char *command, ParsedInstruction *ppi) {
    char seps[] = " ,\t\n", quota_sep = '"';
    char label[MAX_INSTRUCTION_LEN];
    char *token;
    char instruction[MAX_INSTRUCTION_LEN];
    LinkedList *node, *runner;
    ppi->members_num = 0;
    token = strtok(command, seps);
    int quota_started = 0;
    if (token[0] == '.') {
        strcpy(instruction, token + 1);
        ppi->instruction_type = get_instruction_type(instruction);
    }
    token = strtok(NULL, seps);


    if (strcmp(instruction, DATA) == 0) {
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
    } else if (strcmp(instruction, STRING) == 0) {
        if (token[0] == quota_sep) {
            token++; /**Step over the quota**/
            quota_started = 1;
        }
        if (quota_started == 0) {
            printf("There is no starting quota");
            return FALSE;
        }
        if (token) {
            node = (LinkedList *) malloc(sizeof(LinkedList));
            node->val = *token; /**Assign each char as int(ascii representation)**/
            node->next = NULL;
            ppi->list = *node;
            ppi->members_num += 1;
        }
        token++;
        while (*token) {
            if (*token == quota_sep && quota_started) {
                quota_started = 0;
                break;
            }
            node = (LinkedList *) malloc(sizeof(LinkedList));
            node->val = *token;/**Assign each char as int(ascii representation)**/
            node->next = NULL;
            runner = &ppi->list;
            while (runner->next) runner = runner->next;
            runner->next = node;
            ppi->members_num += 1;
            token++;
        }
        if (quota_started == 1) {
            printf("There is starting quota and no ending quota");
            return FALSE;
        } else {
            /**We go a valid string**/
            /**Let's add a NULL termination char**/
            node = (LinkedList *) malloc(sizeof(LinkedList));
            node->val = NULL;/**Assign each char as int(ascii representation)**/
            node->next = NULL;
            runner = &ppi->list;
            while (runner->next) runner = runner->next;
            runner->next = node;
            ppi->members_num += 1;
        }
    } else if ((strcmp(instruction, ENTRY) == 0) || (strcmp(instruction, EXTERN) == 0)) {
        if (*token) {
            node = (LinkedList *) malloc(sizeof(LinkedList));

            strcpy(ppi->label, token);

            strcpy(node->val_for_labels, token); /**Assign each char as int(ascii representation)**/
            node->next = NULL;
            ppi->list = *node;
            ppi->members_num += 1;


        } else {
            /*todo: there is no label after entry*/
            return FALSE;
        }
    }
    return TRUE;
}


int starts_with_valid_instruction(char *str) {
    return (starts_with(DOT_DATA, str) ||
            starts_with(DOT_STRING, str) ||
            starts_with(DOT_ENTRY, str) ||
            starts_with(DOT_EXTERN, str));
}

