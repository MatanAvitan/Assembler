#include "reading_two_list.h"


void add_second_reading_line(ReadingTwoList **rtl,char* label_name, ParsedCommand *ppc, BitsCommand *pbc, int row_num)
{
	ReadingTwoList *sl, *node, *runner;
    if (!*rtl) {
        /**First allocation**/
       	sl = (ReadingTwoList *) malloc(sizeof(ReadingTwoList));
        sl->row_num = row_num;
        sl->ppc = ppc;
        sl->pbc = pbc;
        sl->label_name = label_name;
        sl->next = NULL;
        *rtl = sl;
    } else 
    {
        runner = *rtl;
        while (runner->next)
        	runner = runner->next;
        node = (ReadingTwoList *) malloc(sizeof(ReadingTwoList));
        node->row_num = row_num;
        sl->ppc = ppc;
        sl->pbc = pbc;
        sl->label_name = label_name;
        node->next = NULL;
        runner->next = node;
	}

}

/*void print_second_line(ReadingTwoList **rtl)
{
	ReadingTwoList* head_temp;
	head_temp = *rtl;
	while(head_temp!=NULL)
	{
		printf("%s\n",head_temp->label_name);
		printf("%d\n",head_temp->row_num);
		printf("...\n");

		head_temp=head_temp->next;
	}
}*/