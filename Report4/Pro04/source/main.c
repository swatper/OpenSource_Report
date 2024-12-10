#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define NUMITEMS 30
//공유 데이터 구조체
typedef struct {
    char message[256];        //전송할 메시지
    int message_ready;        //메시지 준비 여부
    pthread_mutex_t mutex;    //뮤텍스
    pthread_cond_t cond_var;  //조건 변수
} server_data_t;
//서버 데이터 초기화
server_data_t server_data = {
    "",
    0,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_COND_INITIALIZER
};
//클라이언트 쓰레드 함수
void *client_thread(int pid) {
    char received_message[256];
    while (1) {
        // 서버가 메시지를 방송하기를 기다림
        pthread_mutex_lock(&server_data.mutex);
        while (server_data.message_ready == 0) {
            pthread_cond_wait(&server_data.cond_var, &server_data.mutex);
        }

        // 메시지 수신
        strcpy(received_message, server_data.message);
        printf("[클라이언트 %d] 받은 메시지: %s\n", pid, received_message);

        // 메시지가 방송되었음을 처리 후, 메시지 준비 상태를 리셋
        server_data.message_ready = 0;
        pthread_mutex_unlock(&server_data.mutex);

        sleep(1);  // 잠시 기다리기
    }
}
// 서버 쓰레드 함수
void *server_thread(void *arg) {
    while (1) {
        // 사용자로부터 메시지 입력받기
        char message[256];
        printf("모든 클라이언트 쓰레드에게 전송할 내용: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0';  // 새 줄 제거

        // 서버가 방송할 메시지 설정
        pthread_mutex_lock(&server_data.mutex);
        strcpy(server_data.message, message);
        server_data.message_ready = 1;

        // 모든 클라이언트에게 메시지 방송(broadcast)
        pthread_cond_broadcast(&server_data.cond_var);
        pthread_mutex_unlock(&server_data.mutex);
        sleep(1);  // 잠시 기다리기
    }

}
int main (){
    //서버 쓰레드
    pthread_t server;
    //클라이언트 쓰레드 3개
    pthread_t clients[3];
    /* 쓰레드 생성 */
    if(pthread_create(&server, NULL, server_thread, NULL)){
        perror("서버 쓰레드 생성 실패");
        exit(1);
    };
    for (int i = 0; i < 3; i++){
        if(pthread_create(&clients[i], NULL, client_thread, i + 1) != 0){
            perror("클라이언트 쓰레드 생성 실패");
            exit(1);
        }
    }
    //쓰레드 조인
    pthread_join(server, NULL);
    for (int i = 0; i < 3; i++) {
        pthread_join(clients[i], NULL);
    }
}