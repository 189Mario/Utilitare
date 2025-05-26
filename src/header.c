#include "header.h"

void check_mem_alloc(const void* p,int line_number)
{
    if(p == NULL)
    {
        printf("Failed to dynamically allocate memory at line: %d \n",line_number);
        exit(1);
    }
}

FILE* open_file(const char* filename, const char* mode, int line_number)
{
    FILE* file = fopen(filename,mode);
    if(file == NULL)
    {
        printf("The file cannot be opened at line: %d \n",line_number);
        exit(1);
    }
    return file;
}