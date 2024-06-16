#ifndef process_list_h
#define process_list_h

typedef unsigned char byte;

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
    byte *content;
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