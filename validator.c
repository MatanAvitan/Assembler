#include "consts.h"
#include "validator.h"

int validate_commas(char *command) {
    int counter = 0;
    char *token;
    char *p;
    char backup_command[120];
    int trail_comma = 0;
    int trail_digit = 0;
    int trail_alpha = 0;
    int trail_space = 0;
    strcpy(backup_command, command);
    for (p = backup_command; counter < MAX_LINE && *p != '\n'; p++) {
        if (trail_comma == 0 && *p == ',') {
            trail_comma = 1;
            continue;
        }
        if (isdigit(*p) || isalpha(*p))trail_comma = 0;
        if (trail_comma == 1 && *p == ',') {
            printf(MULTI_COMMAS);
            return 0;
        }
        counter++;
    }
    token = strtok(backup_command, " ");
    if(!token) return 1;
    /*if the illegal comma is right after the command*/
    if (strstr(token, ",")) {
        printf(ILLEGAL_COMMA);
        return 0;
    } else{
        /*if the illegal comma is after a space*/
        token = strtok(NULL, " ");
        if(!token) return 1;
        if(*token == ','){
            printf(ILLEGAL_COMMA);
            return 0;
        }
    }


    trail_alpha = 0;
    trail_space = 0;
    counter = 0;
    for (p = backup_command; counter < MAX_LINE && *p != '\n'; p++) {
        if(*p == '\n') break;
        if (trail_alpha) {
            if (trail_space) {
                if (isalpha(*p)) {
                    printf(MISSING_COMMA);
                    return 0;
                } else {
                    if (*p == ',') {
                        trail_alpha = 0;
                        trail_space = 0;
                    }
                }
            } else {
                if (*p == ' ') {
                    trail_space = 1;
                } else{
                    if (isalpha(*p)) {
                        trail_alpha = 1;
                        trail_space=0;
                    } else if (*p == ','){
                        trail_alpha = 0;
                        trail_space=0;
                    }
                }
            }
        } else {
            if (isalpha(*p)) {
                trail_alpha = 1;
                trail_space=0;
            }else{
                trail_alpha = 0;
                trail_space=0;
            }
        }


    }
    trail_digit = 0;
    trail_space = 0;
    counter = 0;
    for (p = backup_command; counter < MAX_LINE; p++) {
        if(*p == '\n') break;
        if (trail_digit) {
            if (trail_space) {
                if (isdigit(*p)) {
                    printf(MISSING_COMMA);
                    return 0;
                } else {
                    if (*p == ',') {
                        trail_digit = 0;
                        trail_space = 0;
                    }
                }
            } else {
                if (*p == ' ') {
                    trail_space = 1;
                } else{
                    if (isdigit(*p)) {
                        trail_digit = 1;
                        trail_space=0;
                    } else if (*p == ','){
                        trail_digit = 0;
                        trail_space=0;
                    }
                }
            }
        } else {
            if (isdigit(*p)) {
                trail_digit = 1;
                trail_space=0;
            }
        }


    }

    return 1;
}
