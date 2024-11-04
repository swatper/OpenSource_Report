#include<stdio.h>
#include<stdlib.h>
int main(){
    int row, col;
    int **matrixA;
    int **matrixB;
    printf("행렬의 크기를 입력하세요 (row x col): ");
    scanf("%d x %d", &row, &col);

    //행 생성
    matrixA = (int **)malloc(row*sizeof(int *));
    matrixB = (int **)malloc(row*sizeof(int *));
    //열 생성
    for (int i = 0; i < row; i++){
        matrixA[i] = (int *)malloc(col*sizeof(int *));
        matrixB[i] = (int *)malloc(col*sizeof(int *));
    }

    //A 행렬 값 입력
    printf("A행렬의 값 입력 \n");
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            scanf("%d", &matrixA[i][j]);
        }
    }
    //B 행렬 값 입력
    printf("B행렬의 값 입력 \n");
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            scanf("%d", &matrixB[i][j]);
        }
    }

    //행렬연산
    printf("행렬 더하기 결과 \n");
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            printf("%d ", (matrixA[i][j] + matrixB[i][j]));
        }
        //줄바꿈
        printf("\n");
    }

    //메모리 반환
    for (int i = 0; i < row; i++) {
        free(matrixA[i]);
        free(matrixB[i]);
    }
    free(matrixA);
    free(matrixB);
}