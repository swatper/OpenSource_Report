#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define BUFFER_SIZE 20
#define NUMITEMS 30
typedef struct {
    int item[BUFFER_SIZE];
    int totalitems;
    int in, out;
    pthread_mutex_t mutex;
    pthread_cond_t full;
    pthread_cond_t empty;
} buffer_t;
buffer_t bb = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_COND_INITIALIZER,
    PTHREAD_COND_INITIALIZER
};
int produce_item (int pid){
    int item = (int) (100.0*rand()/(RAND_MAX+1.0));
    sleep((unsigned long) (5.0*rand()/(RAND_MAX+1.0)));
    printf("[생산자 %d]produce_item: item=%d\n", pid, item);
    return item;
}
int insert_item (int item){
    int status;
    status = pthread_mutex_lock (&bb.mutex);
    if (status != 0)
        return status;
    while (bb.totalitems >= BUFFER_SIZE && status == NULL)
        status = pthread_cond_wait (&bb.empty, &bb.mutex);
    if (status != 0) {
        pthread_mutex_unlock(&bb.mutex);
        return status;
    }
    bb.item[bb.in] = item;
    bb.in = (bb.in + 1) % BUFFER_SIZE;
    bb.totalitems++;
    if (status = pthread_cond_signal(&bb.full)) {
        pthread_mutex_unlock (&bb.mutex);
        return status;
    }
    return pthread_mutex_unlock (&bb.mutex);
}
int consume_item (int item, int pid){
    sleep((unsigned long)(5.0*rand()/(RAND_MAX+1.0)));
    printf("\t\t[소비자 %d]consume_item: item=%d\n", pid, item);
}
int remove_item (int *temp){
    int status;
    status = pthread_mutex_lock (&bb.mutex);
    if (status != 0)
        return status;
    while (bb.totalitems <= 0 && status == NULL)
        status = pthread_cond_wait (&bb.full, &bb.mutex);
    if (status != 0) {
        pthread_mutex_unlock(&bb.mutex);
        return status;
    }
    *temp = bb.item[bb.out];
    bb.out = (bb.out + 1) % BUFFER_SIZE;
    bb.totalitems--;
    if (status = pthread_cond_signal(&bb.empty)) {
        pthread_mutex_unlock (&bb.mutex);
        return status;
    }   
    return pthread_mutex_unlock (&bb.mutex);
}
void * producer(int pid){
    int item;
    while (1) {
        item = produce_item(pid);
        insert_item(item);
    }
}
void * consumer(int pid){
    int item;
    while (1) {
        remove_item(&item);
        consume_item(item, pid);
    }
}
int main (){
    //생산 쓰레드 2개
    pthread_t producers[2];
    //소비 쓰레드 2개
    pthread_t consumers[2];
    /* 쓰레드 생성 */
    for (int i = 0; i < 2; i++){
        if(pthread_create(&producers[i], NULL, producer, i + 1) != 0){
            perror("생산자 쓰레드 생성 실패");
            exit(1);
        }
    }
    for (int i = 0; i < 2; i++){
        if(pthread_create(&consumers[i], NULL, consumer, i + 1) != 0){
            perror("소비자 쓰레드 생성 실패");
            exit(1);
        }
    }
    //쓰레드 조인
    for (int i = 0; i < 2; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }
}