#include <stdio.h>
#include <string.h>

fpos_t Getfilesize(const char* Filepath);

int main(int argc, char *argv[]) {
    int linecount = 1;
    int c;
    if (argc < 2){
        printf("Usage: %s <filepath>\n", argv[0]);
        return 1;
    }
    FILE *file;
    char *filepath = argv[1];
    file = fopen(filepath, "r");
    if (file == NULL){
        printf("File open error : %s\n",filepath);
        return 1;
    }
    else {
        printf("File opened successfully: %s\n", filepath);
    }
    fpos_t filesize = Getfilesize(filepath);
    printf("File size: %ld bytes\n", filesize);

    while ((c = fgetc(file)) != EOF){
        if (c == '\n'){
            linecount++;
        }
    }

    fclose(file);
    printf("Total lines: %d\n", linecount);
    return 0;
}

fpos_t Getfilesize(const char* Filepath){
    fpos_t fsize = 0;
    FILE *file = fopen(Filepath, "rb");

    fseek(file, 0, SEEK_END);
    fgetpos(file, &fsize);

    fclose(file);

    return fsize;
}