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
    
    if(*(argv[1] + strlen(argv[1]) - 1) == '4')
    {
    FILE *out,*in1,*in2;
    if((out=fopen(argv[argc - 1] + 6,"wt")) == NULL)
    {
        printf("The output file cannot be opened at line: %d \n",__LINE__);
        exit(1);
    }

    if((in1=fopen(argv[argc - 3],"rt")) == NULL)
    {
        printf("The intput file cannot be opened at line: %d \n",__LINE__);
        exit(1);
    }
    if((in2=fopen(argv[argc - 2],"rt")) == NULL)
    {
        printf("The intput file cannot be opened at line: %d \n",__LINE__);
        exit(1);
    }

    char* ref = (char*)malloc(40*sizeof(char));
    {
        if(ref == NULL)
        {
            printf("Failed to dynamically allocate memory at line: %d \n",__LINE__);
            exit(1);
        }
    }
    char* compare = (char*)malloc(40*sizeof(char));
    {
        if(compare == NULL)
        {
            printf("Failed to dynamically allocate memory at line: %d \n",__LINE__);
            exit(1);
        }
    }

    /*
    int ok=1;
    int i,j,D,I,R;
    int **m = ( int **) malloc (40* sizeof ( int *));
    if(m == NULL)
    {
        printf("Failed to dynamically allocate memory at line: %d \n",__LINE__);
        exit(1);
    }
    for (i=0; i<40; i++)
    {
	    m [i] = (int *) malloc (40* sizeof ( int ));
        if(m [i] == NULL)
        {
            printf("Failed to dynamically allocate memory at line: %d \n",__LINE__);
            exit(1);
        }
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

            for (i = 0 ; i < strlen(compare)+1 ; i++)
            {
                m[i][0] = i;
            }
            for (j = 1 ; j < strlen(ref)+1 ; j++)
            {
                m[0][j] = j;
            }
            for (i = 1 ; i < strlen(compare)+1 ; i++)
            {
                for (j = 1 ; j < strlen(ref)+1 ; j++)
                {
                    if(ref[j-1] == compare[i-1])m[i][j] = m[i-1][j-1];
                    else
                    {
                        m[i][j] = m[i][j-1] + 1;
                        if(m[i-1][j] + 1 < m[i][j])m[i][j] = m[i-1][j]+1;
                        if(m[i-1][j-1] + 2 < m[i][j])m[i][j] = m[i-1][j-1]+2;
                    }
                }
            }

            i = strlen(compare);
            j = strlen(ref);
            D=I=R=0;

            while((i != 0) && (j != 0))
            {
                if(ref[j-1] == compare[i-1])
                {
                    i--;
                    j--;
                }
                else
                {

                    if(m[i][j] == m[i-1][j-1] + 2)
                    {
                        R++;
                        i--;
                        j--;
                    }
                    else
                    {
                        if(m[i][j] == m[i][j-1] + 1)
                        {
                            D++;
                            j--;
                        }
                        else
                        {
                            I++;
                            i--;
                        }
                    }
                
                }
            }

            if(i == 0 && j != 0)D+=j;
            if(j == 0 && i != 0)I+=i;

            fprintf(out,"%dD %dI %dR \n",D,I,R);
        }
    }
    
    for (i=0; i<40; i++)
    {
        free(m[i]);
    }
    free(m);
    */

    int ok=1,i;

    int **m = ( int **) malloc (40* sizeof ( int *));
    if(m == NULL)
    {
        printf("Failed to dynamically allocate memory at line: %d \n",__LINE__);
        exit(1);
    }
    for (i=0; i<40; i++)
    {
	    m [i] = (int *) malloc (40* sizeof ( int ));
        if(m [i] == NULL)
        {
            printf("Failed to dynamically allocate memory at line: %d \n",__LINE__);
            exit(1);
        }
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