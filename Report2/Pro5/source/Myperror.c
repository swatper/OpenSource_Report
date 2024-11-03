#include <stdio.h>
#include <errno.h>
void my_perror(char *errtype){
    if(errtype!= NULL){
        fprintf(stderr,"%s: ", errtype);
    }
    switch (errno){
    case EBADF:
        fprintf(stderr, "잘못된 파일 기술자\n");
        break;
    case EINPROGRESS:
        fprintf(stderr, "진행중인 오퍼레이션\n");
        break;
    case EINVAL:
        fprintf(stderr, "잘못된 프로그램 인자\n");
        break;
    case ENOENT:
        fprintf(stderr, "없는 파일 또는 디렉토리\n");
        break;
    case ERANGE:
        fprintf(stderr, "결과 값이 너무 큼\n");
        break;
    case ETIMEDOUT:
        fprintf(stderr, "시간 초가된 오퍼레이션\n");
        break;   
    }
}