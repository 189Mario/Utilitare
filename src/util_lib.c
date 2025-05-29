#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

typedef struct FileNode
{
    char path[100];
    char includes[50][100];
    int include_count;
}FileNode;

typedef struct IncludeMap
{
    char libname[100];
    char used_in[50][100];
    int count;
} IncludeMap;

FileNode files[50];
int file_count = 0;
IncludeMap includes[50];
int include_count = 0;
int show_warnings = 0;
int loop_detected = 0;

void add_include(const char* libname, const char* filename)
{
    for (int i = 0; i < include_count; i++)
    {
        if (strcmp(includes[i].libname, libname) == 0)
        {
            strcpy(includes[i].used_in[includes[i].count++], filename);
            return;
        }
    }
    strcpy(includes[include_count].libname, libname);
    strcpy(includes[include_count].used_in[0], filename);
    includes[include_count++].count = 1;
}

void parse_file(const char* filepath)
{
    FILE* f = fopen(filepath, "r");
    if (f == NULL) return;
    FileNode* node = &files[file_count++];
    strcpy(node->path, filepath);
    node->include_count = 0;
    char line[100];
    while (fgets(line, sizeof(line), f)) {
        char lib[100];
        char* inc = strstr(line, "#include");
        if (inc) {
            inc += 8;
            while (*inc == ' ' || *inc == '\t') inc++;
            char* start = NULL;
            char* end = NULL;
            if (*inc == '\"') {
                start = inc + 1;
                end = strchr(start, '\"');
            } else if (*inc == '<') {
                start = inc + 1;
                end = strchr(start, '>');
            }

            if (start && end && (end > start)) {
                size_t len = end - start;
                if (len < sizeof(lib)) {
                    strncpy(lib, start, len);
                    lib[len] = '\0';
                    strcpy(node->includes[node->include_count++], lib);
                    add_include(lib, filepath);
                }
            }
        }
    }
    fclose(f);
}


void find_c_h_in_dir(const char* dirname)
{
    struct dirent* entry;
    DIR* dir = opendir(dirname);
    if (!dir) return;
    while ((entry = readdir(dir)))
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)continue;
        char path[100];
        path[0] = '\0';
        strncat(path, dirname, sizeof(path) - strlen(path) - 1);
        strncat(path, "/", sizeof(path) - strlen(path) - 1);
        strncat(path, entry->d_name, sizeof(path) - strlen(path) - 1);
        struct stat st;
        if (stat(path, &st) == -1) continue;
        if (S_ISDIR(st.st_mode))
        {
            find_c_h_in_dir(path);
        } else if (strstr(path, ".c") || strstr(path, ".h"))
        {
            parse_file(path);
        }
    }
    closedir(dir);
}

int get_file_index(const char* path)
{
    for (int i = 0; i < file_count; i++)
    {
        if (strcmp(files[i].path, path) == 0)return i;
    }
    return -1;
}

int state[50];

void dfs(int idx)
{
    state[idx] = 1;
    for (int i = 0; i < files[idx].include_count; i++)
    {
        char included_path[100];
        strcpy(included_path, files[idx].includes[i]);
        for (int j = 0; j < file_count; j++)
        {
            if (strstr(included_path, files[j].path)) continue;
            if (strstr(files[j].path, included_path))
            {
                int next = j;
                if (state[next] == 1)
                {
                    loop_detected = 1;
                    return;
                }
                if (state[next] == 0) dfs(next);
            }
        }
    }
    state[idx] = 2;
}

void detect_loops()
{
    for (int i = 0; i < file_count; i++) state[i] = 0;
    for (int i = 0; i < file_count; i++)
    {
        if (state[i] == 0) dfs(i);
    }
}

void report_warnings()
{
    for (int i = 0; i < include_count; i++)
    {
        if (includes[i].count > 1)
        {
            printf("WARNING double include: %s in", includes[i].libname);
            for (int j = 0; j < includes[i].count; j++)
                printf(" %s", includes[i].used_in[j]);
            printf("\n");
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <dir> [--full]\n", argv[0]);
        return 1;
    }
    if (argc == 3 && strcmp(argv[2], "--full") == 0)
    {
        show_warnings = 1;
    }
    find_c_h_in_dir(argv[1]);
    detect_loops();
    if (show_warnings) report_warnings();
    if (loop_detected) printf("ERROR loop detected\n");
    if(loop_detected) return 1;
    else return 0;
}