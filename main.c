#include <stdio.h>
#include <string.h>

long Getfilesize(FILE *file,char *filepath);
int linecounter(FILE *file,char *filepath);

int main(int argc, char *argv[]) {
    int total_linecount = 0;
    long total_size = 0;
    if (argc < 2){
        printf("Usage: %s <filepath>\n", argv[0]);
        return 1;
    }
    for (int i = 1;i < argc; i++){
        FILE *file;
        file = fopen(argv[i], "r");
        if (file == NULL){
            printf("File open error: %s\n", argv[i]);
            continue;
        }
        long size = Getfilesize(file, argv[i]);
        int linecount = linecounter(file, argv[i]);
        fclose(file);
        total_size = total_size + size;
        total_linecount = total_linecount + linecount;
    }
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

long Getfilesize(FILE *file,char *filepath){
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    printf("%s size: %ld bytes\n", filepath, size);
    return size;
}