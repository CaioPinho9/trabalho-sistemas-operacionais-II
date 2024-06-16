#include <stdio.h>
#include <stdlib.h>
#include "process_list.h"

void insert(processes *list, process *process)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->process = process;
    new_node->next = NULL;

    list->tail->next = new_node;
    list->tail = new_node;
}

process *get_process(processes *list, unsigned pid)
{
    struct Node *current = list->head->next;
    while (current != NULL)
    {
        if (current->process->pid == pid)
        {
            return current->process;
        }
        current = current->next;
    }
    return NULL;
}
