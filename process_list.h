#ifndef process_list_h
#define PROCESS_LIST_H

typedef unsigned logical_memory;

struct Node
{
    struct Process *process;
    struct Node *next;
};
struct Process
{
    unsigned pid;
    unsigned size;
    unsigned *page_table;
    logical_memory *content;
};

struct List
{
    struct Node *head;
    struct Node *tail;
};
typedef struct Node node;
typedef struct Process process;
typedef struct List processes;

void insert(processes *list, process *process);
process *get_process(processes *list, unsigned pid);

#endif