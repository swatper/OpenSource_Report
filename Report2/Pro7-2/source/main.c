#include<stdio.h>
#include "Calculate.h"

int main(){
    int a, b;
    printf("두 수를 입력하세요: ");
    scanf("%d %d", &a, &b);
    Add(a, b);
    Sub(a, b);
    Mul(a, b);
    Div(a, b);
    return 0;
}