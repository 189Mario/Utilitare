#include "header.h"

int find_parent_for_relative_path(const char *absolute_path1,const char *absolute_path2)
{
    int end_of_parent=1,i=1;
    int len1=strlen(absolute_path1), len2=strlen(absolute_path2);
    while(absolute_path1[i] == absolute_path2[i])
    {
        if(i == len1 || i == len2)break;
        if(absolute_path1[i] == '/')end_of_parent = i;
        i++;
    }
    if(absolute_path1[i] == '\0' || absolute_path2[i] == '\0')
    {
        end_of_parent = i;
    }
    return end_of_parent;
}

void creare_output_3(FILE *out,const char *absolute_path1,const char *absolute_path2,int end_of_parent)
{
    absolute_path1 = absolute_path1 + end_of_parent;
    while((absolute_path1=strchr(absolute_path1,'/')) != NULL)
    {
        fprintf(out,"%s","../");
        absolute_path1++;
    }
    if(end_of_parent != strlen(absolute_path2))fprintf(out,"%s/",absolute_path2 + end_of_parent + 1);
}