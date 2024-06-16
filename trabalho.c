#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "process_list.h"

typedef unsigned physical_memory;
typedef unsigned page;

const int MAX_SIZE = 1024;
int page_size = 1024;
int memory_size = 1024;
int process_size = 1024;

// byte arrays
physical_memory *memory;

struct FreeFrames
{
    int count;
    char *frames;
};

struct FreeFrames free_frames;

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
    printf("Process creation\n");
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
    printf("Usage: %s <memory_size> <page_size> <process_size>\n", argv[0]);
    if (argc != 4)
    {
        printf("Missing arguments\n");
        exit(0);
    }

    // Initialize memory
    memory_size = atoi(argv[1]);
    validate_input("memory", memory_size);

    page_size = atoi(argv[2]);
    validate_input("page", page_size);

    process_size = atoi(argv[3]);
    validate_input("process", process_size);

    memory = (physical_memory *)malloc(memory_size);
    free_frames.count = memory_size / page_size;
    free_frames.frames = (char *)malloc(free_frames.count);


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