struct Node;

typedef struct Process process;
typedef struct List processes;

void insert(processes *list, process *process);
process *get_process(processes *list, int pid);