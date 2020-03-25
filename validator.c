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


/*The function gets a command and number of arguments and returs true if the command have the right operand's number*/
/*we assume the command is right and alreday checked*/
int right_count_operands(char* command, int args_num)
{
    if((strcmp(command, MOV) == 0) || strcmp(command, CMP) == 0 || strcmp(command, ADD) == 0 
        || strcmp(command, SUB) == 0 || strcmp(command, LEA) == 0)
    {
        /*command need 2 operand*/
        if(args_num != 2)
            return FALSE;
    }
    else if(strcmp(command, CLR) == 0 || strcmp(command, NOT) == 0 ||
            strcmp(command, INC) == 0 || strcmp(command, DEC) == 0 ||
            strcmp(command, JMP) == 0 || strcmp(command, BNE) == 0 ||
            strcmp(command, RED) == 0 || strcmp(command, PRN) == 0 || 
            strcmp(command, JSR) == 0)
    {
        /*command need 1 operand*/
        if(args_num != 1)
        {
            return FALSE;
        }
    }
    else
    {
        /*command need 1 operand*/
        if(args_num != 0)
        {
            return FALSE;
        }
    }
    return TRUE;

}


/*The function gets a command and returns true if the command is valid and else returns false*/
int valid_command_name(char* command)
{
    if(strcmp(command, MOV) == 0 || strcmp(command, CMP) == 0 || strcmp(command, ADD) == 0 
        || strcmp(command, SUB) == 0 || strcmp(command, LEA) == 0 || strcmp(command, CLR) == 0 
        || strcmp(command, NOT) == 0 || strcmp(command, INC) == 0 || strcmp(command, DEC) == 0 
        || strcmp(command, JMP) == 0 || strcmp(command, BNE) == 0 || strcmp(command, RED) == 0
        || strcmp(command, PRN) == 0 || strcmp(command, JSR) == 0 || strcmp(command, RTS) == 0 
        || strcmp(command, STOP) == 0)
        return TRUE;
    return FALSE;
}

/*The function gets instruction_type and members_num of parsed instruction and returns true if the count operand is valid and else returns false*/
int right_instruction_count_operand(int instruction_type, int members_num)
{
   /*TODO: string - we need to check that there is only one string, one "".*/

   if(instruction_type == ENTRY_NO || instruction_type  == EXTERN_NO) 
   {
        /*need 1 parameter*/
        if(members_num == 1)
            return TRUE; 
        return FALSE;
   }
   else if(instruction_type == DATA_NO || instruction_type == STRING_NO)
    {
        if(members_num >= 1)
            return TRUE;
        return FALSE;
    }
}


/*The function gets the label and checks if it is valid and returs true if the label is valid and else false*/
int valid_label(char label[])
{
    int length = 0, i = 0;
    /*TODO: check if the label donsent exsist - NULL?*/
    if(label != NULL)
    {
        /*65 to 72 ot 97 to 122*/
        if((label[0] >= CAPITAL_LETTER_START && label[0] <= CAPITAL_LETTER_END) || (label[0] >= LOWER_CASE_LETTER_START || label[0] <= LOWER_CASE_LETTER_END))
        {
            length = count_length(label);
           
            /*if the label is too long*/
            if(length > 31)
            {
                printf(ERROR_LABEL_LENGTH);
                return FALSE;
            }
            /*if the last char isnt ':', like a label should end*/
            else if(strcmp(label[length-1], ":") != 0)
            {
                printf(ERROR_LABEL_LAST_CHAR);
                return FALSE;
            }
            else
            {
                /*if the label is with letters or digits*/
                while (i != length)
                {
                    if((label[i] < CAPITAL_LETTER_START || label[i] > CAPITAL_LETTER_END) && 
                        (label[i] < LOWER_CASE_LETTER_START || label[i] > LOWER_CASE_LETTER_END) &&
                        (label[i] < DIGITS_START || label[i] > DIGITS_END))
                    {
                        printf(ERROR_LABEL_ILLEGAL_CHAR);
                       return FALSE; 
                    }
                        
                    i++;
                }
            }
            return TRUE;
        }
        else
        {
            /*The label dosent start with letter*/
            printf(ERROR_LABEL_FIRST_CHAR);
            return FALSE;
        }
    }
    /*the label is null - there is not label*/
    else
    {
        return TRUE;
    }
}


/*The function gets a char array and count the length*/
int count_length (char array[])
{
    int count = 0, i = 0;
    int size = 0;
    size = sizeof(array)/sizeof(char);

    while(i != size)
    {
        /*check if there is NULL*/
        if(array[i] != NULL)
            count++;
        else
            break;
        i++;
    }

    return count;
}

