//#include "header1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct argument 
{
    char tip;
    char valoare[50];
    char l_or_s;
    char id[50];
} ARG;

int populare(int argc, char **argv, ARG *arguments, int *dim_of_arguments)
{
    int pozition_of_first_non_argument=2,i,j,k;
    const char* p;
    (*dim_of_arguments) = argc - 4;

    while(pozition_of_first_non_argument < argc - 2)
    {
        if( *(argv[pozition_of_first_non_argument]) == '-' )break;
        else pozition_of_first_non_argument++;
    }

    i=2;
    j=0;
    while( i < pozition_of_first_non_argument )
    {
        arguments[j].tip = 'a';
        strcpy(arguments[j].valoare,argv[i]);
        arguments[j].l_or_s = 0;
        strcpy(arguments[j].id,"");
        j++;
        i++;
    }
    for( i = pozition_of_first_non_argument ; i < argc - 2 ; i++)
    {
        if(*(argv[i]) == '-' && *(argv[i+1]) != '-')
        {
            arguments[j].tip = 'o';
            strcpy(arguments[j].valoare,(argv[i+1]));
            if(*((argv[i]) + 1) == '-')
            {
                arguments[j].l_or_s='l';
                strcpy(arguments[j].id,argv[i] + 2 );
            }
            else
            {
                arguments[j].l_or_s='s';
                strcpy(arguments[j].id,argv[i] + 1 );
            }
            i++;
        }
        else if( (p=strchr(argv[i],'=')) != NULL )
             {
                arguments[j].tip = 'o';
                strcpy(arguments[j].valoare,p + 1);
                if(*((argv[i]) + 1) == '-')
                {
                    arguments[j].l_or_s='l';
                    strncpy(arguments[j].id,argv[i] + 2, p - argv[i] - 2);
                    arguments[j].id[p - argv[i] - 2]='\0';
                }
                else 
                {
                    arguments[j].l_or_s='s';
                    strncpy(arguments[j].id,argv[i] + 1, p - argv[i] - 1);
                    arguments[j].id[p - argv[i] - 1]='\0';
                }
             }
             else
             {
                if(*((argv[i]) + 1) == '-')
                {
                    arguments[j].tip = 'f';
                    strcpy(arguments[j].valoare,"1");
                    arguments[j].l_or_s='l';
                    strcpy(arguments[j].id,argv[i] + 2 );
                }
                else 
                {
                    k=0;
                    while(k < strlen(argv[i]) - 1)
                    {
                        arguments[j].tip = 'f';
                        strcpy(arguments[j].valoare,"1");
                        arguments[j].l_or_s='s';
                        strncpy(arguments[j].id,argv[i] + k + 1 , 1);
                        arguments[j].id[1]='\0';
                        j++;
                        k++;
                    }
                    j--;
                    k--;
                    (*dim_of_arguments)+=k;
                }
             }
        j++;
    }
    pozition_of_first_non_argument -= 2;
    return pozition_of_first_non_argument;
}

void open_in_out_task1(int argc, char** argv,FILE **in ,FILE **out)
{
    if((*in=fopen(argv[argc - 2] + 7,"rt")) == NULL)
    {
        printf("The input file cannot be opened at line: %d \n",__LINE__);
        exit(1);
    }
    if((*out=fopen(argv[argc - 1] + 6,"wt")) == NULL)
    {
        printf("The output file cannot be opened at line: %d \n",__LINE__);
        exit(1);
    }
}

int main(int argc, char** argv)
{
    if(*(argv[1] + strlen(argv[1]) - 1) == '1')
    {
    FILE *out,*in;
    int i,pozition_of_first_non_argument,dim_of_arguments,j,found;
    char *line = (char*)malloc(50*sizeof(char));
    if(line==NULL)
    {
        printf("Failed to dynamically allocate memory at line: %d \n",__LINE__);
        exit(1);
    }
    ARG *arguments = (ARG*)malloc(10*sizeof(ARG));
    if(arguments==NULL)
    {
        printf("Failed to dynamically allocate memory at line: %d \n",__LINE__);
        exit(1);
    }
    open_in_out_task1(argc,argv,&in ,&out);
    i=0;
    pozition_of_first_non_argument=populare(argc,argv,arguments,&dim_of_arguments);
    i=0;
    while( fgets(line,50,in) != NULL)
    {
        if(line[strlen(line) - 1] == '\n')line[strlen(line) - 1] = '\0';
        if((line[strlen(line) - 1]) == 'a')
        {
            if(i < pozition_of_first_non_argument )
            {
                strcat(line," ");
                strcat(line,arguments[i].valoare);
                i++;
                strcat(line," \n");
                fputs(line,out);
            }
            else
            {
                strcat(line," \n");
                fputs(line,out);
            } 
        }
        else
        {
            found=0;
            for ( j=pozition_of_first_non_argument ; j < dim_of_arguments ; j++ )
            {
                if((line[strlen(line) - 1]) == 'o' && 
                    strstr(line,arguments[j].id) != NULL && 
                    arguments[j].tip == 'o')
                {
                    found=1;
                    strcat(line," ");
                    strcat(line,arguments[j].valoare);
                    strcat(line," \n");
                    fputs(line,out);
                    break;
                }
                if((line[strlen(line) - 1]) == 'f' && 
                    strstr(line,arguments[j].id) != NULL && 
                    arguments[j].tip == 'f')
                {
                    found=1;
                    strcat(line," 1 \n");
                    fputs(line,out);
                    break;
                }
            }
            if (!found)
            {
                strcat(line," \n");
                fputs(line,out);
            }
        }   
    }
    free(arguments);
    free(line);
    fclose(in);
    fclose(out);
    }

    
    
    return 0;
}