#include <stdio.h>
#include <stdlib.h>
#define MY_ASSERT(x) do {\
	if (!(x)) { \
        fprintf(stdout,"조건 안 맞음 \n");\
		fprintf(stdout,"조건 : %s \n", #x);\
		abort(); \
	}\
} while(0)