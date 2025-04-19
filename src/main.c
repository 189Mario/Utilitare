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

    if(*(argv[1] + strlen(argv[1]) - 1) == '3')
    {
    char *initial1, *initial2;
    char* absolute_path1 = (char*)malloc(150*sizeof(char));
    {
        if(absolute_path1 == NULL)
        {
            printf("Failed to dynamically allocate memory at line: %d \n",__LINE__);
            exit(1);
        }
    }
    initial1 = absolute_path1;
    strcpy(absolute_path1,argv[argc - 3]);
    absolute_path1 = strstr(absolute_path1,"/teste/");


    char* absolute_path2 = (char*)malloc(150*sizeof(char));
    {
        if(absolute_path2 == NULL)
        {
            printf("Failed to dynamically allocate memory at line: %d \n",__LINE__);
            exit(1);
        }
    }
    initial2 = absolute_path2;
    strcpy(absolute_path2,argv[argc - 2]);
    absolute_path2 = strstr(absolute_path2,"/teste/");

    FILE *out;
    if((out=fopen(argv[argc - 1] + 6,"wt")) == NULL)
    {
        printf("The output file cannot be opened at line: %d \n",__LINE__);
        exit(1);
    }

    int end_of_parent = find_parent_for_relative_path(absolute_path1,absolute_path2);
    creare_output_3(out, absolute_path1, absolute_path2, end_of_parent);

    free(initial1);
    free(initial2);
    fclose(out);
    }
    /*
    if(*(argv[1] + strlen(argv[1]) - 1) == '4')
    {
    FILE *out,*in1,*in2;
    if((out=fopen(argv[argc - 1] + 6,"wt")) == NULL)
    {
        printf("The output file cannot be opened at line: %d \n",__LINE__);
        exit(1);
    }

    if((in1=fopen(strrchr(argv[argc - 3],'/') + 1,"rt")) == NULL)
    {
        printf("The intput file cannot be opened at line: %d \n",__LINE__);
        exit(1);
    }
    if((in2=fopen(strrchr(argv[argc - 2],'/') + 1,"rt")) == NULL)
    {
        printf("The intput file cannot be opened at line: %d \n",__LINE__);
        exit(1);
    }

    char* ref = (char*)malloc(30*sizeof(char));
    {
        if(ref == NULL)
        {
            printf("Failed to dynamically allocate memory at line: %d \n",__LINE__);
            exit(1);
        }
    }
    char* compare = (char*)malloc(30*sizeof(char));
    {
        if(compare == NULL)
        {
            printf("Failed to dynamically allocate memory at line: %d \n",__LINE__);
            exit(1);
        }
    }
    int ok=1;
    while(ok == 1)
    {
        ok=0;
        if((fscanf(in1,"%s",ref) == 1))
        {
            fprintf(out,"%s \n",ref);
            ok=1;
        }
        if((fscanf(in2,"%s",compare) == 1))
        {
            fprintf(out,"%s \n",compare);
            ok=1;
        }
    }
    free(ref);
    free(compare);
    fclose(in1);
    fclose(in2);
    fclose(out);
    }*/
    return 0;
}