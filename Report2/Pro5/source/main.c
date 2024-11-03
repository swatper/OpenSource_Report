#include <stdio.h>
#include <stdlib.h>
#include "Myperror.h"
//PPT 예제
int main(int argc, char*argv[]){
    FILE *f;
    if (argc < 2){
        printf("Usage: errono_show file_name \n");
        exit(1);
    }

    if((f = fopen(argv[1],"r"))==NULL){
        my_perror(NULL);
        exit(1);
    }
    printf("Open a file \"%s\"",argv[1]);
    fclose(f);
}