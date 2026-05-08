#include <stdio.h>
#include <string.h>
#include <Windows.h>

typedef struct {
    char **filepaths;
    int filecount;
} FileResult;

long Getfilesize(FILE *file,char *filepath);
int linecounter(FILE *file,char *filepath);
FileResult FileSearch(char *filepath);

int main(int argc, char *argv[]) {
    int total_linecount = 0;
    long total_size = 0;
    if (argc < 2){
        printf("Usage: %s <filepath>\n", argv[0]);
        return 1;
    }
    FileResult result = FileSearch(argv[1]);
    for (int i = 0; i < result.filecount; i++){
        FILE *file;
        file = fopen(result.filepaths[i], "r");
        if (file == NULL){
            printf("File open error: %s\n", result.filepaths[i]);
            continue;
        }
        long size = Getfilesize(file, result.filepaths[i]);
        int linecount = linecounter(file, result.filepaths[i]);
        fclose(file);
        total_size = total_size + size;
        total_linecount = total_linecount + linecount;
    }
    for (int i = 0; i < result.filecount; i++){
        free(result.filepaths[i]);
    }
    free(result.filepaths);
    printf("\n=== TOTAL ===\n");
    printf("Total file size: %ld bytes\n",total_size);
    printf("Total lines: %d line\n", total_linecount);
    return 0;
}

int linecounter(FILE *file,char *filepath){
    int linecount = 0;
    int c;
    int last_char = '\0';
    rewind(file);
    while ((c = fgetc(file)) != EOF){
        if (c == '\n'){
            linecount++;
        }
        last_char = c;
    }
    if (last_char != '\n' && last_char != '\0'){
        linecount++;
    }

    printf("%s lines: %d line\n", filepath, linecount);
    return linecount;
}

void AddToFileResult(FileResult *result, char *filepath){
    result->filecount++;
    char **temp = realloc(result->filepaths, result->filecount * sizeof(char*));

    if (temp == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }

    result->filepaths = temp;
    result->filepaths[result->filecount - 1] = _strdup(filepath);
}

FileResult FileSearch(char *filepath){
    WIN32_FIND_DATA findData;
    HANDLE hFind;
    FileResult result = {NULL, 0};
    hFind = FindFirstFile(filepath, &findData);
    if (hFind == INVALID_HANDLE_VALUE){
        printf("File search error: %s\n", filepath);
        return result;
    }
    char directory[MAX_PATH];

    strcpy(directory, filepath);

    char *lastSlash = strrchr(directory, '\\');

    if (lastSlash != NULL){
        *(lastSlash + 1) = '\0';
    }
    else{
        directory[0] = '\0';
    }
    do {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
            char fullpath[MAX_PATH];
            snprintf(fullpath,
                    MAX_PATH,
                    "%s%s",
                    directory,
                    findData.cFileName);
            AddToFileResult(&result, fullpath);
        }
    } while (FindNextFile(hFind, &findData) != 0);
    FindClose(hFind);
    return result;
}

long Getfilesize(FILE *file,char *filepath){
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    printf("%s size: %ld bytes\n", filepath, size);
    return size;
}