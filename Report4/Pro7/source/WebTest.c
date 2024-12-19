#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT 3490
#define QLEN 10
#define BUF_SIZE 2048
void *handle_clnt(int sockfd);
void Handle_Post(int client_sock, char *body);
void Handle_Get(int client_sock, char *body);
void send_err(int sockfd);

int main(int argc, char *argv[]){
    int sockfd, new_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
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
        fprintf(stderr, "listen fail\n");
        exit(1);
    }
    alen = sizeof(client_addr);
    FD_ZERO(&activefds);
    FD_SET(sockfd, &activefds);
    maxfd = sockfd;
    fprintf(stderr, "Server up and running.\n");
    while (1){
        readfds = activefds;
        if (select(maxfd + 1, &readfds, NULL, NULL, NULL) < 0){
            perror("select");
            exit(EXIT_FAILURE);
        }
        for (i = 0; i <= maxfd; i++){
            if (FD_ISSET(i, &readfds)){
                if (i == sockfd){
                    if ((new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &alen)) < 0){
                        fprintf(stderr, "accept failed\n");
                        exit(1);
                    }
                    FD_SET(new_fd, &activefds);
                    if (new_fd > maxfd)
                        maxfd = new_fd;
                }
                else{
                    printf("handle clnt\n");
                    handle_clnt(i);
                    close(i);
                    FD_CLR(i, &activefds);
                }
            }
        }
    }
    close(sockfd);
}

void *handle_clnt(int client_sock){
    char buf[BUF_SIZE];
    char method[10];
    char path[BUF_SIZE];
    char body[BUF_SIZE] = {0};
    int str_len;
    // 요청 읽기
    if ((str_len = read(client_sock, buf, BUF_SIZE - 1)) <= 0) {
        perror("read error");
        return NULL;
    }
    buf[str_len] = '\0';
    //HTTP 요청 메시지 첫 줄 파싱
    sscanf(buf, "%s %s", method, path);
    //GET 요청 처리
    if (strcmp(method, "GET") == 0) {
        Handle_Get(client_sock, path);
    }
    //POST 요청 처리
    else if (strcmp(method, "POST") == 0) {
        //Body 부분 추출
        char *body_ptr = strstr(buf, "\r\n\r\n") + 4;
        strncpy(body, body_ptr, BUF_SIZE - 1);
        Handle_Post(client_sock, body);
    } 
    else {
        send_err(client_sock);
    }
    return NULL;
}

void send_err(int client_sock){
    char protocol[] = "HTTP/1.1 400 Bad Request\r\n";
    char server[] = "Server:NetscapeEnterprise/6.0\r\n";
    char contenttype[] = "ContentType:text/html\r\n";
    char html[] = "<html><head>BAD Connection</head><body><H1>BadRequest</H1></body></html>\r\n";
    char end[] = "\r\n";
    printf("send err\n");
    write(client_sock, protocol, strlen(protocol));
    write(client_sock, server, strlen(server));
    write(client_sock, contenttype, strlen(contenttype));
    write(client_sock, end, strlen(end));
    write(client_sock, html, strlen(html));
    fflush(fdopen(client_sock, "w"));
}

void Handle_Post(int client_sock, char *body) {
    char response_header[BUF_SIZE];
    char response_body[BUF_SIZE];
    printf("POST Data: %s\n", body);
    snprintf(response_body, sizeof(response_body),
             "<html><body><h1>POST Request Received</h1><p>Data: %s</p></body></html>", body);
    snprintf(response_header, sizeof(response_header),
             "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\nContent-Type: text/html\r\n\r\n",
             strlen(response_body));
    write(client_sock, response_header, strlen(response_header));
    write(client_sock, response_body, strlen(response_body));
}

void Handle_Get(int client_sock, char *path) {
    char response_header[BUF_SIZE];
    char response_body[BUF_SIZE];
    char realPath[1024];
    char curPath[1024];
    FILE *fp;

    path = "/source/index.html";

    if (getcwd(curPath, sizeof(curPath)) == NULL) {
        perror("getcwd");
        exit(1);  // 에러 발생 시 프로그램 종료
    }    

    snprintf(realPath, sizeof(realPath), "%s%s", curPath, path);
    //printf(realPath);

    // 파일 열기
    fp = fopen(realPath, "r");

    if (fp == NULL) {
        // 파일을 찾을 수 없을 때
        snprintf(response_body, sizeof(response_body), "<h1>404 Not Found</h1>");
        snprintf(response_header, sizeof(response_header),
                 "HTTP/1.1 404 Not Found\r\nContent-Length: %ld\r\nContent-Type: text/html\r\n\r\n",
                 strlen(response_body));
        write(client_sock, response_header, strlen(response_header));
        write(client_sock, response_body, strlen(response_body));
    } else {
        // 파일을 성공적으로 읽었을 때
        fread(response_body, 1, sizeof(response_body), fp);
        fclose(fp);
        snprintf(response_header, sizeof(response_header),
                 "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\nContent-Type: text/html\r\n\r\n",
                 strlen(response_body));
        write(client_sock, response_header, strlen(response_header));
        write(client_sock, response_body, strlen(response_body));
    }
}