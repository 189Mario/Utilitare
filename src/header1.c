#include "header.h"

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