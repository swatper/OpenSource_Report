//메크로 정의
#define MY_ASSERT(x) do {\
        if (!(x)) { \
            fprintf(stdout, "조건 안 맞음 \n");\
            fprintf(stdout,"조건 : %s \n", #x);\
            abort(); \ 
        }\
} while(0)
//"\"를 사용하여 정의 내용 이어감