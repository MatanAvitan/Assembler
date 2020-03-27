#include "parsed_command.h"
#include "parsed_instruction.h"


#define FAILED_TO_FETCH_COMMAND "Failed to fetch a command\n"

ParsedCommand *get_error_parser(ParsedCommand *ppc) {
    /*If the command is not valid i want to return an appropriate ParsedCommand pointer to the main*/
    const char termination_command[20] = {'t', 'e', 'r', 'm', 'i', 'n', 'a', 't', 'e'};
    strcpy(ppc->command, termination_command);
    return ppc;
}

ParsedCommand *parse(char *command, ParsedCommand *ppc) {
    char seps[] = ":";
    char coma_and_space_seps[] = ", ";
    char space_sep = ' ';
    char *token, prefix[MAX_LINE], command_without_prefix[MAX_LINE];
    char *src_token, *dst_token;
    int n;
    ppc->args_num = 0;
    ppc->src_addressing_method = -1;
    ppc->dst_addressing_method = -1;

    /*The prefix for command is actually optional field,
    *only for new labels this filed will store the label's name*/
    token = strtok(command, seps);
    strcpy(prefix, token);
    token = strtok(NULL, seps);

    /*If the second token is not null then the : separator separates between the label and the rest of the command
     *else the second argument just be null*/
    if (token) {
        strcpy(command_without_prefix, token);
        strcpy(ppc->prefix, prefix);
        /*Remove unneeded spaces */
        strcpy(command, command_without_prefix);
        /**This is an instruction sentence because there is a label**/
        token = strtok(command_without_prefix, &space_sep);
        if (starts_with_valid_instruction(token))
            return get_error_parser(ppc);
    }

    if (sscanf(command, " %[a-zA-Z] %n", ppc->command, &n) != 1) {
        return get_error_parser(ppc);
    }
    command += n;
    /*if (!validate_commas(command)) {
        return get_error_parser(ppc);
    }*/
    src_token = strtok(command, coma_and_space_seps);
    if (src_token) /**If there is no first arg than src_token is null**/
    {
        if (strstr(src_token, "#")) {
            ppc->src_addressing_method = INSTANT_ADDRESSING_NO;
            if (*src_token == '#') {
                src_token++;
            }
        }
        else if (strstr(src_token, "*r")) {
            ppc->src_addressing_method = INDIRECT_REGISTER_ADDRESSING_NO;
            if (*src_token == '*') {
                src_token++;
            }
        } else if (strstr(src_token, "r")) {
            ppc->src_addressing_method = DIRECT_REGISTER_ADDRESSING_NO;
        } else {
            /**It's none of the mentioned methods above, so if it's a valid command it has to be Direct addressing**/
            ppc->src_addressing_method = DIRECT_ADDRESSING_NO;
        }
    }
    dst_token = strtok(NULL, coma_and_space_seps);
    if (dst_token) /**If there is no second arg than dst_token is null**/
    {
        if (strstr(dst_token, "#")) {
            ppc->dst_addressing_method = INSTANT_ADDRESSING_NO;
            if (*dst_token == '#') {
                dst_token++;
            }
        }
        else if (strstr(dst_token, "*r")) {
            ppc->dst_addressing_method = INDIRECT_REGISTER_ADDRESSING_NO;
            if (*dst_token == '*') {
                dst_token++;
            }
        } else if (strstr(dst_token, "r")) {
            ppc->dst_addressing_method = DIRECT_REGISTER_ADDRESSING_NO;
        } else {
            /**It's none of the mentioned methods above, so if it's a valid command it has to be Direct addressing**/
            ppc->dst_addressing_method = DIRECT_ADDRESSING_NO;
        }

    }


    if (src_token && (sscanf(src_token, "%[-0-9a-zA-Z] , %n", ppc->src, &n) == 1)) {
        ppc->args_num += 1;
    }

    if (dst_token && (sscanf(dst_token, "%[-0-9a-zA-Z] , %n", ppc->dst, &n) == 1)) {
        ppc->args_num += 1;
    }

    /*If there is only one args than we assigned the dst to the src so we need to swap between them*/
    if (ppc->args_num == 1) {
        strcpy(ppc->dst, ppc->src);
        ppc->dst_addressing_method = ppc->src_addressing_method;
        ppc->src_addressing_method = -1;
        for (n = 0; n < MAX_ARG_SIZE; n++) {
            ppc->src[n] = 0;
        }
    }

    return ppc;
}
