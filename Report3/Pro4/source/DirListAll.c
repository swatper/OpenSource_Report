#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#define MAX_PATH 1024

//포로토타입 선언
void DirectoryList(const char *path);

int main(int argc, char *argv[]){   
    if (argc < 2) {
        exit(1);
    } 
    DirectoryList(argv[1]);
} 

void DirectoryList(const char *path){
    DIR *pdir;
    struct dirent *pde;
    int i = 0;
    char subPath[MAX_PATH];
    //디렉토리 열기
    if ( (pdir = opendir(path)) == NULL) {
        perror("opendir");
        exit(1);
    }

    printf("Current directory: %s\n",path);

    //목록 읽기
    while ((pde = readdir(pdir)) != NULL) {
        if(strcmp(pde->d_name,".") == 0 || strcmp(pde->d_name,"..") == 0){
            continue;
        }
        printf("%20s ", pde->d_name);
        if (++i % 5 == 0) printf("\n");
        
        //읽은 파일이 만약 디렉토리면
        //디렉토리 구조채(dirent)의 d_type을 가져와서 확인
        if(pde->d_type == DT_DIR){
            printf("\n%s is directory, So Open this directory.\n", pde->d_name);
            //현재 경로 + 파일 이름 -> 다음 경로
            snprintf(subPath, sizeof(subPath), "%s/%s", path, pde->d_name);
            //재귀
            DirectoryList(subPath);
        }
    }
    printf("\n");
    //디렉토리 닫음
    closedir(pdir);
}