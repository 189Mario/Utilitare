#include "header.h"

int main(int argc, char** argv)
{
    if(*(argv[1] + strlen(argv[1]) - 1) == '1')
    {
    int i,pozition_of_first_non_argument,dim_of_arguments,j,found;
    char *line = (char*)malloc(50*sizeof(ARG));
    check_mem_alloc(line,__LINE__);
    ARG *arguments = (ARG*)malloc(10*sizeof(ARG));
    check_mem_alloc(arguments,__LINE__);
    
    FILE *out,*in;
    in = open_file(argv[argc - 2] + 7,"rt",__LINE__);
    out = open_file(argv[argc - 1] + 6,"wt",__LINE__);
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
    out = open_file(argv[argc - 1] + 6,"wt",__LINE__);
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
    check_mem_alloc(absolute_path1,__LINE__);
    initial1 = absolute_path1;
    strcpy(absolute_path1,argv[argc - 3]);
    absolute_path1 = strstr(absolute_path1,"/teste/");

    char* absolute_path2 = (char*)malloc(150*sizeof(char));
    check_mem_alloc(absolute_path2,__LINE__);
    initial2 = absolute_path2;
    strcpy(absolute_path2,argv[argc - 2]);
    absolute_path2 = strstr(absolute_path2,"/teste/");

    FILE *out;
    out = open_file(argv[argc - 1] + 6,"wt",__LINE__);

    int end_of_parent = find_parent_for_relative_path(absolute_path1,absolute_path2);
    creare_output_3(out, absolute_path1, absolute_path2, end_of_parent);

    free(initial1);
    free(initial2);
    fclose(out);
    }
    
    if(*(argv[1] + strlen(argv[1]) - 1) == '4')
    {
    FILE *out,*in1,*in2;
    out = open_file(argv[argc - 1] + 6,"wt",__LINE__);
    in1 = open_file(argv[argc - 3],"rt",__LINE__);
    in2 = open_file(argv[argc - 2],"rt",__LINE__);

    char* ref = (char*)malloc(40*sizeof(char));
    check_mem_alloc(ref,__LINE__);
    char* compare = (char*)malloc(40*sizeof(char));
    check_mem_alloc(compare,__LINE__);
    int ok=1,i;
    int **m = ( int **) malloc (40* sizeof ( int *));
    check_mem_alloc(m,__LINE__);
    for (i=0; i<40; i++)
    {
	    m[i] = (int *) malloc (40* sizeof ( int ));
        check_mem_alloc(m[i],__LINE__);
    }

    while(ok == 1)
    {
        ok=0;
        if((fgets(ref,40*sizeof(char),in1) != NULL))
        {
            ref[strlen(ref)-1] = '\0';
            ok=1;
        }
        else strcpy(ref,"");
        if((fgets(compare,40*sizeof(char),in2) != NULL))
        {
            compare[strlen(compare)-1] = '\0';
            ok=1;
        }
        else strcpy(compare,"");
        if(ok == 1)
        {
            task4(out,ref,compare,m);
        }
    }

    for (i=0; i<40; i++)
    {
        free(m[i]);
    }
    free(m);


    free(ref);
    free(compare);
    fclose(in1);
    fclose(in2);
    fclose(out);
    }
    return 0;
}