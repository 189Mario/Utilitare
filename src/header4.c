#include "header.h"

struct p
{
    int x;
    int y;
};
typedef struct p POINT;

int MIN(int a, int b) 
{
    if(a < b)return a;
    else return b;
}

void task4(FILE* out,const char* ref,const char* compare,int** m)
{
    int D,I,R;
    int i,j,k;
    int len1 = strlen(ref), len2 = strlen(compare);

    //initialize matrix properly
    for(i = 0 ; i < len2 ; i++)
    {
        for(j = 0 ; j < len1 ; j++)
        {
            if(ref[j] == compare[i])m[i][j] = 1;
            else m[i][j] = 0;
        }
    }
    for(j = 0; j <= len1 ; j++)
    {
        m[len2][j] = 0;
    }
    for(i = 0; i <= len2 ; i++)
    {
        m[i][len1] = 0;
    }

    int *values1 = (int *) malloc (40* sizeof ( int ));
    if(values1 == NULL)
    {
        printf("Failed to dynamically allocate memory at line: %d \n",__LINE__);
        exit(1);
    }
    int *values2 = (int *) malloc (40* sizeof ( int ));
    if(values2 == NULL)
    {
        printf("Failed to dynamically allocate memory at line: %d \n",__LINE__);
        exit(1);
    }

    for(i = 0; i < 40 ; i++)
    {
        values1[i] = values2[i] = 0;
    }

    for(i = len2 - 1 ; i > -1 ; i--)
    {
        for(j = len1 - 1 ; j > -1 ; j--)
        {
            if(m[i][j] == 1)
            {
                m[i][j] += values1[j + 1];
                values2[j] = m[i][j];
            }
            else
            {
                if(values2[j + 1] > values2[j])values2[j] = values2[j + 1];
            }
        }
        for( k = 0 ; k < 40 ; k++)
        {
            values1[k] = values2[k];
        }
    }

    int max = values1[0],min;


    
    POINT left_top;
    left_top.x = left_top.y = 0;
    D=I=R=0;
    for(j = left_top.x ; j <= len1 ; j++)
    {
        for(i = left_top.y ; i <= len2 ; i++)
        {
            if(m[i][j] == max)
            {
                if((len2 >= len1) && (m[i + 1][j] == max))continue;
                min = MIN(j - left_top.x ,i - left_top.y);
                R += min ;
                D += (j - (min + left_top.x));
                I += (i - (min + left_top.y));
                left_top.x = j + 1;
                left_top.y = i + 1;
                j = j + 1;
                max--;
                if(max == 0)
                {
                    left_top.x = j + 1;
                    left_top.y = i + 2;
                    min = MIN((len1 + 1) - left_top.x ,(len2 + 1) - left_top.y);
                    R += min ;
                    D += ((len1 + 1) - (min + left_top.x));
                    I += ((len2 + 1) - (min + left_top.y));
                    i = len2 + 1;
                    j = len1 + 1;
                }
            }
        }
    }

    if(len1 == 0)
    {
        fprintf(out,"%dD %dI %dR \n",0,len2,0);
    }
    else if(len2 == 0)
        {
            fprintf(out,"%dD %dI %dR \n",len1,0,0);
        }
        else
        {
            fprintf(out,"%dD %dI %dR \n",D,I,R);
        } 

    //output matrix
    /*
    for(i = 0 ; i < len2 + 1 ; i++)
    {
        for(j = 0 ; j < len1 + 1; j++)
        {
            fprintf(out,"%d ",m[i][j]);
        }
        fprintf(out,"\n");
    }
    fprintf(out,"%d\n",max);
    */
    free(values1);
    free(values2);
}