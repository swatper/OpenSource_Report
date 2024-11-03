#include <stdio.h>
#include <stdlib.h>
#include "Myassert.h"

void foo(int n){
    MY_ASSERT(((n >= 0) && (n <= 100)));
    printf("foo: num = %d\n",n);
}

int main(int argc, char *argv[]){
    int num;
    if (argc < 2){
       fprintf(stderr,"Usage: assert_test aNumber\n (0 <= aNumber <= 100)\n");
       exit(1);
    }
    num = atoi(argv[1]);
    foo(num);
}