#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2){
        printf("Usage: %s <filepath>\n", argv[0]);
        return 1;
    }
    FILE *file;
    char *filepath = argv[1];
    file = fopen(filepath, "r");
    if (file == NULL){
        printf("file open error : %s\n",filepath);
        return 1;
    }
    else {
        printf("file opened successfully: %s\n", filepath);
        fclose(file);
    }
    return 0;
}

fpos_t Getfilesize(const char* Filepath[]){
    fpos_t fsize = 0;
    FILE *file = fopen(Filepath, "rb");

    fseek(file, 0, SEEK_END);
    fgetpos(file, &fsize);

    fclose(file);

    return fsize;
}