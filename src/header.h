#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

//General use
void check_mem_alloc(const void* p,int line_number);
FILE* open_file(const char* filename, const char* mode, int line_number);

//Task1
struct argument 
{
    char tip;
    char valoare[50];
    char l_or_s;
    char id[50];
};
typedef struct argument ARG; 

int populare(int argc, char **argv, ARG *arguments, int *dim_of_arguments);

//Task2
struct list
{
	char path[200];
    char dim[20];
    char type;
	struct list * next ;
};
typedef struct list L;

char printType(mode_t iMode);
void free_list(L *cap_lista);
char* long_int_to_string(long int n);
L* creaza_lista(const char *initial_path,char* path,DIR *dir,int height, int option);
void sorteaza_lista(L *cap_lista);
void output_r(const char* initial_path, int height, FILE* out, int option);

//Task3
int find_parent_for_relative_path(const char *absolute_path1,const char *absolute_path2);
void creare_output_3(FILE *out,const char *absolute_path1,const char *absolute_path2,int end_of_parent);
//
struct non_binary_tree
{
    char *s;
    int nr_children;
    struct non_binary_tree **a;
};
typedef struct non_binary_tree NBT;




//Task4
void task4(FILE* out,const char* ref,const char* compare,int** m);
int MIN(int a, int b);