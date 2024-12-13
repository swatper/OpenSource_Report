#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#define PORT 3490
#define QLEN 6 
#define MAXDATASIZE 100
void *ServerTODO(){
    struct sockaddr_in server_addr;
    int sockfd, new_fd;       
    struct sockaddr_in cad;   
    int alen;                 
    fd_set readfds, activefds; 
    int i, maxfd = 0, numbytes;
    char buf[100];
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket() failed");
        exit(1);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("bind() failed");
        exit(1);
    }
    if (listen(sockfd, QLEN) < 0){
        fprintf(stderr, "listen failed\n");
        exit(1);
    }
    alen = sizeof(cad);
    FD_ZERO(&activefds);
    FD_SET(sockfd, &activefds);
    maxfd = sockfd;
    fprintf(stderr, "Server up and running.\n");
    while (1){
        //printf("SERVER: Waiting for contact ..., %d\n", maxfd);
        readfds = activefds;
        if (select (maxfd + 1, &readfds, NULL, NULL, NULL) < 0) {
                perror("select");
                exit(EXIT_FAILURE);
        }
        for (i = 0; i <= maxfd; ++i) {
            if (FD_ISSET(i, &readfds)){
                if (i == sockfd){
                    if ((new_fd = accept(sockfd, (struct sockaddr *)&cad, &alen)) < 0){
                        fprintf(stderr, "accept failed\n");
                        exit(1);
                    }
                    FD_SET(new_fd, &activefds); 
                    printf("New client connected: %d\n", new_fd);
                    if (new_fd > maxfd)
                        maxfd = new_fd;
                }
                else{
                    if ((numbytes = recv(i, buf, 100, 0)) == -1)
                            perror("recv");
                    buf[numbytes] = '\0';
                    if (send(i, buf, strlen(buf), 0) == -1)
                        perror("send");
                    close(i);
                    FD_CLR(i, &activefds);
                }
            }
        }
    }
    close(sockfd);
}
void *ClientTODO(int pid){
    int csock, numbytes;
    char buf[MAXDATASIZE];
    struct sockaddr_in serv_addr;
    int len;
    /* 클라이언트 소켓 생성 */
    if ((csock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }
    /* 서버 주소 설정 */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(PORT);
    /* 서버 연결 */
    if (connect(csock, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1){
        perror("connect");
        exit(1);
    }
    /* 메시지 송수신 */
    memset(buf, 0, MAXDATASIZE);
    sprintf(buf, "Hello Server, I'm Client %d", pid);
    len = strlen(buf);
    if (send(csock, buf, len, 0) != len){
        fprintf(stderr, "send failed...\n");
        exit(1);
    }
    memset(buf, 0, MAXDATASIZE);
    if ((numbytes = recv(csock, buf, MAXDATASIZE, 0)) == -1){
        perror("recv");
        exit(1);
    }
    printf("Received: %s\n", buf);
    close(csock);
}

int main(){
    //서버 쓰레드
    pthread_t server;
    //클라이언트 쓰레드 2개
    pthread_t client[2];
    /* 쓰레드 생성 */
    if(pthread_create(&server, NULL, ServerTODO, NULL) != 0){
            perror("서버 쓰레드 생성 실패");
            exit(1);
    }
    for (int i = 0; i < 2; i++){
        if(pthread_create(&client[i], NULL, ClientTODO, i + 1) != 0){
            perror("클라이언트 쓰레드 생성 실패");
            exit(1);
        }
    }
    //쓰레드 조인
    pthread_join(server, NULL);
    for (int i = 0; i < 2; i++) {
        pthread_join(client[i], NULL);
    }
}