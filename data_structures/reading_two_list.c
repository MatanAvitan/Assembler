#include "reading_two_list.h"

void add_second_line_reading(ReadingTwoList **ptl, ParsedCommand *ppc, BitsCommand *pbc, int row_num) 
{
	ReadingTwoList *pl, *node, *runner;
    if (!*ptl)
    {
        /**First allocation**/
        pl = (ReadingTwoList *) malloc(sizeof(ReadingTwoList));
        pl->row_num = row_num;
        pl->ppc = ppc;
        pl->pbc = pbc;
        pl->next = NULL;
        *ptl = pl;
    } 
    else
    {
        runner = *ptl;
        while (runner->next)runner = runner->next;
        node = (ReadingTwoList *) malloc(sizeof(ReadingTwoList));
        node->row_num = row_num;
        pl->ppc = ppc;
        pl->pbc = pbc;
        node->next = NULL;
        runner->next = node;
    }

    printf("hey\n");
}