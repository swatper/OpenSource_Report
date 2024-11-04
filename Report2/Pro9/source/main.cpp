#include<iostream>
#include<vector>
using namespace std;
int main(){
    //C와 C++ 라이브러리 분리
    cin.tie(NULL);
    cout.tie(NULL);

    int row, col;
    cout << "행렬의 크기를 입력하세요\n";
    cin >> row >> col;
    //행렬 생성 및 초기화
    vector<vector<int>> matrixA(row,vector<int>(col,0));
    vector<vector<int>> matrixB(row,vector<int>(col,0));

    //A 행렬 값 입력
    cout << "A행렬의 값 입력 \n";
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            cin >> matrixA[i][j];
        }
    }
    //B 행렬 값 입력
    cout << "B행렬의 값 입력 \n";
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            cin >> matrixB[i][j];
        }
    }

    //행렬연산
    cout << "연산 결과 \n";
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            cout << (matrixA[i][j] + matrixB[i][j]) << " ";
        }
        cout << "\n";
    }
    //프로그램 종료시 메모리는 자동으로 반환
    return 0;
}