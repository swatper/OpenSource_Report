#include <stdio.h>
#include <dlfcn.h>
int main (){
    void *handle;
    void (*Add)(int, int);
    void (*Sub)(int, int);
    void (*Mul)(int, int);
    void (*Div)(int, int);

    handle = dlopen("../library/libshare.so",RTLD_LAZY);
    if (!handle){
        fputs(dlerror(),stderr);
        return 0;
    }
    Add = dlsym(handle, "Add");
    Sub = dlsym(handle, "Sub");
    Mul = dlsym(handle, "Mul");
    Div = dlsym(handle, "Div");

    int a, b;
    printf("두 수를 입력하세요: ");
    scanf("%d %d", &a, &b);

    Add(a, b);
    Sub(a, b);
    Mul(a, b);
    Div(a, b);
    return 0;
}