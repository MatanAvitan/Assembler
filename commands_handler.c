#include "commands_handler.h"
#include <string.h>




command_t commands[] = {
	{COMMAND_ID_READ_SET, "read_set", 1},
	{COMMAND_ID_PRINT_SET, "print_set", 1},
	{COMMAND_ID_UNION_SET, "union_set", 3},
	{COMMAD_ID_INTERSECT_SET, "intersect_set", 3},
	{COMMAD_ID_SUB_SET, "sub_set", 3},
	{COMMAD_ID_SYMDIFF_SET, "symdiff_set", 3}
};

set_gruop_t sets[] = {
	{SET_GRUOP_ID_SETA, "SETA"},
	{SET_GRUOP_ID_SETB, "SETB"},
	{SET_GRUOP_ID_SETC, "SETC"},
	{SET_GRUOP_ID_SETD, "SETD"},
	{SET_GRUOP_ID_SETE, "SETE"},
	{SET_GRUOP_ID_SETF, "SETF"}
};


void read_command(char * input, set* all_sets)
{
	parse_command readParse = {0};

	char trash1[MAX_LINE];
	char trash2[MAX_LINE];
	char ** arr;
	int arr_len = 0;
	int i = 0;

	int command_id = NO_COMMAND;
	int args = 0;

	sscanf(input,"%[A-Za-z_] %[a-zA-Z]%[, ]%[a-zA-Z]%[, ]%[a-zA-Z]",readParse.name,readParse.arg1,trash1,readParse.arg2,trash2,readParse.arg3);

	/*Checking if the command name is read_set*/
	if(strcmp("read_set",readParse.name) == 0) /*TODO - Change the read_set value to generic variable*/
	{
		initString(readParse.arg1,5);
		initString(readParse.arg2,5);
		initString(readParse.arg3,5);

		sscanf(input,"%[A-Za-z_] %[a-zA-Z]%[, ]%[0-9, -]",readParse.name,readParse.arg1,trash1,trash2);

		arr = str_split(trash2,',');
		arr_len = mymatrixlen(arr);

		/*TODO: put in numbers array*/

		insert_to_array(arr,&readParse);

		if(strcmp(arr[arr_len-1],zakif))
		{
			printf(ERROR_NO_ZAKIF);
			return;
		}
	}

	/**command validation**/

	for (i = 0; i <= sizeof(commands)/sizeof(commands[0]); ++i)
	{
		if(strcmp(readParse.name, commands[i].command_name) == 0)
		{
			command_id = commands[i].command_id;
		}
	}

	if(command_id == NO_COMMAND)
	{
		printf(ERROR_NO_RIGHT_COMMAND);
		return;
	}

	args = args_num(readParse);

	if(args != commands[command_id].arguments_count)
	{
		if(args > commands[command_id].arguments_count)
			printf(ERROR_MORE_COUNT_SET); 
		else
			printf(ERROR_LESS_COUNT_SET);
		return;
	}
	else
	{
		if(cmp_set(readParse.arg1) == -1)
		{
			printf(ERROR_SET_NAME);
			return;
		}
		if(args == MAX_ARGS)
		{
			if((cmp_set(readParse.arg2) == -1) || (cmp_set(readParse.arg3) == -1))
			{
				printf(ERROR_SET_NAME);
				return;
			}
		}

	}

	/*send to right function*/
	if(command_id == 0)
	{
		read_set(cmp_set(readParse.arg1),readParse.numbers,all_sets);
	}
	if(command_id == 1)
		print_set(cmp_set(readParse.arg1), all_sets);



	/*TODO: init all*/

}

int cmp_set(char arg[])
{
	/*1 for true, -1 for false*/
	int i = 0;
	for (i = 0; i < sizeof(sets)/sizeof(sets[0]); i++)
	{
		printf("arg: %s\n",arg);
		if(strcmp(arg, sets[i].set_name) == 0)
		{
			return i;
		}
	}
	return -1;
}


int args_num(parse_command pc)
{
	int count = 0;
	if(pc.arg1[0] != '\0')
		count++;
	if(pc.arg2[0] != '\0')
		count++;
	if(pc.arg3[0] != '\0')
		count++;
	return count;
}


char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = (char*)strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}


int mystrlen(char * str)
{
	int retval = 0;

	while(str[retval++]);

	return retval-1;
}

int mymatrixlen(char ** str)
{
	int retval = 0;

	while(str[retval++]);

	return retval-1;
}

void initString(char * str,int len)
{
	int i = 0;

	for (i = 0; i < len;i++)
	{
		str[i] = 0;
	}
}

void insert_to_array(char ** arr,parse_command *pc)
{
	int i = 0;

	for(i = 0;i < mymatrixlen(arr);i++)
	{
		pc->numbers[i] = atoi(arr[i]);
	}

}
