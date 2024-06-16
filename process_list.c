#include <stdio.h>
#include <stdlib.h>

typedef unsigned logical_memory;
typedef struct Process process;

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

struct Node *head;
struct Node *tail;

void insert(process *process)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->process = process;
    new_node->next = NULL;

    if (head == NULL)
    {
        head = new_node;
        tail = new_node;
    }
    else
    {
        tail->next = new_node;
        tail = new_node;
    }
}

process *get_process(int pid)
{
    struct Node *current = head;
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
