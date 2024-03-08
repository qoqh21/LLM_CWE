#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // TCP 클라이언트 소켓 생성
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("소켓 생성 실패");
        exit(EXIT_FAILURE);
    }

    // 서버 주소 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);

    // 서버에 연결
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("연결 실패");
        exit(EXIT_FAILURE);
    }
    printf("서버 연결 성공\n");

    // 서버로 데이터 전송
    const char* message = "Hello, server!";
    if (send(client_socket, message, strlen(message), 0) == -1) {
        perror("전송 실패");
        exit(EXIT_FAILURE);
    }
    printf("데이터 전송 성공\n");

    // 클라이언트 소켓 닫기
    close(client_socket);

    return 0;
}
