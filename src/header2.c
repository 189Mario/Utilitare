#include "header.h"

char printType(mode_t iMode)
{
    if(S_ISREG(iMode))
    {
        return 'f';
    }
    else return 'd';
}

void free_list(L *cap_lista) 
{
    while (cap_lista != NULL) 
    {
        L *temp = cap_lista;
        cap_lista = cap_lista->next;
        free(temp);
    }
}

char* long_int_to_string(long int n)
{
    char buffer[30];
    snprintf(buffer, sizeof(buffer), "%ld", n);
    char* result = malloc(strlen(buffer) + 1);  
    if (result != NULL)strcpy(result, buffer);
    return result;
}

L* creaza_lista(const char *initial_path,char* path,DIR *dir,int height, int option)
{   
    char *dim;
    struct stat st;
    const struct dirent *chosen;
    L* cap_lista = NULL;
    L* nod1;
    while ((chosen = readdir(dir)) != NULL) 
	{
        if (height > 0 && (strcmp(chosen->d_name, ".") == 0 || strcmp(chosen->d_name, "..") == 0))
        {
            continue;
        }
        strcpy(path,initial_path);
        strcat(path, "/");
        strcat(path,chosen->d_name);
        if(stat(path, &st) == 0)
        {
            L* nod2 = ( L *) malloc ( sizeof ( L ));
            nod2 -> next = NULL ;
            strcpy(nod2 -> path,path);
            dim=long_int_to_string(st.st_size);
            if( option == 1 || option == 3)
            {
                if(strlen(dim)>3)
                {
                    dim[1]='K';
                    dim[2]='\0';
                }
            }
            strcpy(nod2 -> dim,dim);
            free(dim);
            if((strcmp(chosen->d_name, ".") != 0 && strcmp(chosen->d_name, "..") != 0))
            {
                (nod2 -> type) = printType(st.st_mode);
            }
            else (nod2 -> type) = 'f';

            if(cap_lista == NULL)cap_lista = nod2;
            else (nod1->next) = nod2;
            nod1=nod2;
        }
    } 
    return cap_lista;
}

void sorteaza_lista(L *cap_lista) 
{
    if (cap_lista == NULL || cap_lista->next == NULL)return;
    int schimbat;
    L *n1, *n2;
    char temp_path[200],temp_type,temp_dim[20];
    do 
    {
        schimbat = 0;
        n1 = cap_lista;
        while (n1->next != NULL) 
        {
            n2 = n1->next;
            if (strcmp(n1->path, n2->path) > 0) 
            {
                strcpy(temp_path, n1->path);
                strcpy(n1->path, n2->path);
                strcpy(n2->path, temp_path);
                strcpy(temp_dim , n1->dim);
                strcpy(n1->dim , n2->dim);
                strcpy(n2->dim , temp_dim);
                temp_type = n1->type;
                n1->type = n2->type;
                n2->type = temp_type;
                schimbat = 1;
            }
            n1 = n1->next;
        }
    }while(schimbat);
}


void output_r(const char* initial_path, int height, FILE* out, int option)
{
    int i;
    DIR* dir = opendir(initial_path);
    if(dir == NULL)
    {
        printf("Directory failed to open at line: %d \n",__LINE__);
        exit(1);
    }

    char* new_path = (char*)malloc(200*sizeof(char));
    if(new_path == NULL)exit(1);

    L* list = creaza_lista(initial_path, new_path, dir, height, option);

    free(new_path);
    closedir(dir);

    sorteaza_lista(list);

    L* node = list; 
    while(node != NULL) 
    {
        for(i = 0; i < height; i++)
        {
            fprintf(out, "    ");
        }
        //de modificat nu mai este necesara utilizarea optiunilor, ref-urile sunt ok acum
        /*
        if(option == 1 || option == 3)fprintf(out, "%s %s\n", node->dim, strrchr(node->path, '/') + 1);
        else fprintf(out, "%s %s\n", node->dim, strrchr(node->path, '/') + 1);*/
        fprintf(out, "%s %s\n", node->dim, strrchr(node->path, '/') + 1);
        if(option == 0 || option == 1)
        {
            node = node->next;
            continue;
        }
        if(node->type == 'd') 
        {
            output_r(node->path, height + 1, out, option);
        }
        node = node->next;
    }
    free_list(list);
}