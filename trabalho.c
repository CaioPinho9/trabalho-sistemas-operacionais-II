#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "process_list.h"

typedef unsigned physical_memory;
typedef unsigned page;

const unsigned MAX_SIZE = 1024;
unsigned page_size = 1024;
unsigned memory_size = 1024;
unsigned process_size = 1024;

processes *process_list;

// byte arrays
physical_memory *memory;

struct FreeFrames
{
    unsigned count;
    char *frames;
};

struct FreeFrames free_frames;

int validate_input(char *name, unsigned max_size)
{
    if (max_size <= 0)
    {
        printf("%s should be more than 0\n", name);
        return 0;
    }
    else if (max_size > MAX_SIZE)
    {
        printf("%s can't be more than %d bytes\n", name, MAX_SIZE);
        return 0;
    }
    else if ((log2(max_size) - (int)log2(max_size)) != 0)
    {
        printf("%s must be a power of 2\n", name);
        return 0;
    }
    return 1;
}

void visualize_memory(unsigned *memory_to_show, int size)
{
    printf("Memory visualization:\n\n");
    int page_count = 0;
    for (int i = 0; i < size; i++)
    {
        if (i % page_size == 0)
        {
            printf("Page %d \n", page_count);
            page_count++;
        }
        printf("%02x ", memory_to_show[i]);
        if ((i + 1) % page_size == 0)
        {
            printf("\n\n");
        }
    }
    printf("\n");
}


void create_process()
{
    int pid;
    int size;

    while (1)
    {
        printf("Process id: ");
        scanf("%d", &pid);

        if (get_process(process_list, pid) != NULL)
        {
            printf("Process %d already exists\n", pid);
            continue;
        }
        else
        {
            break;
        }
    }

    while (1)
    {
        printf("Process size: ");
        scanf("%d", &size);

        if (!validate_input("process", size))
            continue;

        if (size > memory_size)
        {
            printf("Process size can't be more than memory size\n");
            continue;
        }

        if (size > free_frames.count * page_size)
        {
            printf("Not enough free frames\n");
            continue;
        }
        break;
    }

    srand(time(NULL));
    unsigned *content = (unsigned *)malloc(size * sizeof(unsigned));
    for (int i = 0; i < size; i++)
    {
        content[i] = rand() % 100;
    }

    if (content == NULL)
    {
        printf("Memory allocation failed for process content\n");
        exit(1);
    }

    // TODO: change to print content

    process *new_process = (process *)malloc(sizeof(process));
    if (new_process == NULL)
    {
        printf("Memory allocation failed for process\n");
        exit(1);
    }
    new_process->pid = pid;
    new_process->size = size;
    new_process->content = content;
    new_process->page_table = (unsigned *)malloc(size / page_size * sizeof(unsigned));
    if (new_process->page_table == NULL)
    {
        printf("Memory allocation failed for page table\n");
        exit(1);
    }
    insert(process_list, new_process);

    printf("Process %d created with size %d\n", pid, size);
}

void visualize_page_table(unsigned int  *page_table) {
    // Print the page table in a tabular format
    printf("Page table visualization\n");
    printf("+----------------+----------------+\n");
    printf("| Logical Memory | Physical Memory |\n");
    printf("+----------------+----------------+\n");
    for (int i = 0; i < process_size; i++) {
        printf("|      %5d      |      %5d      |\n", i, page_table[i]);
    }
    printf("+----------------+----------------+\n");
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    if (argc != 4)
    {
        printf("Usage: %s <memory_size> <page_size> <process_size>\n", argv[0]);
        exit(0);
    }

    // Initialize memory
    memory_size = atoi(argv[1]);
    if (!validate_input("memory", memory_size))
        exit(0);

    page_size = atoi(argv[2]);
    if (!validate_input("page", page_size))
        exit(0);

    process_size = atoi(argv[3]);
    if (!validate_input("process", process_size))
        exit(0);

    memory = (physical_memory *)malloc(memory_size);
    free_frames.count = memory_size / page_size;
    free_frames.frames = (char *)malloc(free_frames.count);

    process_list = (processes *)malloc(sizeof(processes));
    node *new_node = (node *)malloc(sizeof(node));
    process_list->head = new_node;
    process_list->tail = new_node;

    //Mocked values, remove later
    unsigned page_table[process_size];
    for (int i = 0; i < process_size; i++) {
        page_table[i] = rand() % 100; // Simulated page number/value
    }

    printf("Choose an option \n");
    printf("Visualize memory [1]\n");
    printf("Create process [2]\n");
    printf("Visualize page table [3]\n");
    printf("Visualize process list [4]\n");

    int option;
    scanf("%d", &option);

    if (option == 1)
    {
        visualize_memory(memory, memory_size);
    }
    else if (option == 2)
    {
        create_process();
    }
    else if (option == 3)
    {
        visualize_page_table(page_table);
    }
    else
    {
        printf("Invalid option\n");
    }

    return 0;
}
