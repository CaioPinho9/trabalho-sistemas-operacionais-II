#include <stdio.h>
#include <stdlib.h>

typedef unsigned logical_memory;
typedef struct Process process;
typedef struct List processes;

struct Process
{
    int pid;
    int size;
    int *page_table;
    logical_memory *content;
};

struct Node
{
    struct Process *process;
    struct Node *next;
};

void insert(processes *list, process *process)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->process = process;
    new_node->next = NULL;

    if (list->head == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

process *get_process(processes *list, int pid)
{
    struct Node *current = list->head;
    while (current != NULL)
    {
        if (current->process->pid == pid)
        {
            return current->process;
        }
        current = current->next;
    }
    printf("Process %d not found\n", pid);
}

struct List
{
    struct Node *head;
    struct Node *tail;
};
