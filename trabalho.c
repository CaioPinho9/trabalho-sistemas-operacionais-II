#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef unsigned physical_memory;
typedef unsigned logical_memory;
typedef unsigned page;

const int MAX_SIZE = 1024;
int page_size = 1024;
int memory_size = 1024;

// byte arrays
physical_memory *memory;

struct FreeFrames
{
    int count;
    char *frames;
};

struct Process
{
    int pid;
    int size;
    int *page_table;
    logical_memory *content;
};

void validate_input(char *name, int max_size)
{
    if (max_size <= 0)
    {
        printf("%s should be more than 0\n", name);
        exit(0);
    }
    else if (max_size > MAX_SIZE)
    {
        printf("%s can't be more than %d bytes\n", name, MAX_SIZE);
        exit(0);
    }
    else if ((log2(max_size) - (int)log2(max_size)) != 0)
    {
        printf("%s must be a power of 2\n", name);
        exit(0);
    }
}

void visualize_memory()
{
    printf("Memory visualization\n");
}

void create_process()
{
    printf("Process creation\n");
}

void visualize_page_table()
{
    printf("Page table visualization\n");
}

int main(int argc, char *argv[])
{
    printf(argc);
    if (argc != 4)
    {
        printf("Missing arguments\n");
        exit(0);
    }

    // Initialize memory
    int memory_size = atoi(argv[1]);
    validate_input("memory", memory_size);

    int page_size = atoi(argv[2]);
    validate_input("page", page_size);

    int process_size = atoi(argv[3]);
    validate_input("process", page_size);

    memory = (physical_memory *)malloc(memory_size);

    printf("Choose an option \n");
    printf("Visualize memory [1]\n");
    printf("Create process [2]\n");
    printf("Visualize page table [3]\n");

    int option;
    scanf("%d", &option);

    if (option == 1)
    {
        visualize_memory();
    }
    else if (option == 2)
    {
        create_process();
    }
    else if (option == 3)
    {
        visualize_page_table();
    }
    else
    {
        printf("Invalid option\n");
    }

    return 0;
}