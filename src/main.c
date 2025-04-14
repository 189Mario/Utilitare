#include "header.h"

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

    if(*(argv[1] + strlen(argv[1]) - 1) == '2')
    {
    int option = 0;
    FILE *out;
    if((out=fopen(argv[argc - 1] + 6,"wt")) == NULL)
    {
        printf("The output file cannot be opened at line: %d \n",__LINE__);
        exit(1);
    }

    char initial_path[200];
    if ((*argv[argc - 2]) == '/')
    {
        strcpy(initial_path,argv[argc - 2]);
        option = 0;
    }
    else 
    {
        strcpy(initial_path,argv[argc - 3]);
        if( strlen(argv[argc - 2]) == 3)option = 3;
        else
        {
            if(*(argv[argc - 2] + 1) == 'r')option = 2;
            else if(*(argv[argc - 2] + 1) == 'h')option = 1;
        }
    }   
    output_r(initial_path, 0, out, option);
    fclose(out);
    }
    return 0;
}