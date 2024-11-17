#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int fd; /* file descriptor */
    char *buf = "This test is from FileDes.c \n";
    int flags = O_WRONLY | O_CREAT | O_TRUNC;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; /* == 0644 */
    if (argc < 2) {
        fprintf(stderr, "Usage: file_output filename\n");
        exit(1);
    }
    if ( (fd = open(argv[1], flags, mode)) == -1 ) {
        perror("open"); 
        exit(1);
    }
    if ( dup2(fd, 1) == -1 ) {
        perror("dup2");
        exit(1);
    }
    if ( close(fd) == -1 ) {
        perror("close"); 
    exit(1);
    }
    write(1, buf, strlen(buf));
    exit(0);
}
