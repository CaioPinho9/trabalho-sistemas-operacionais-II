#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// byte array
unsigned char memory;
const int MAX_SIZE = 1024;

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
    else if (max_size % 2 != 0)
    {
        printf("%s must be a multiple of 2\n", name);
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
    if (argc != 2)
    {
        printf("Missing arguments\n");
    }

    // Initialize memory
    int memory_size = atoi(argv[0]);
    validate_input("memory", memory_size);

    int page_size = atoi(argv[1]);
    validate_input("page", page_size);

    memory = malloc(memory_size);

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