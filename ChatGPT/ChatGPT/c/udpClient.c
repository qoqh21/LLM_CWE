#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // UDP 소켓 생성
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        perror("소켓 생성 실패");
        exit(EXIT_FAILURE);
    }

    // 서버 주소 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);

    // 서버에 메시지 전송
    const char* message = "Hello, server!";
    sendto(client_socket, message, strlen(message), 0,
           (struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("메시지 전송 성공\n");

    // 서버로부터 응답 수신
    socklen_t addr_len = sizeof(server_addr);
    int received_bytes = recvfrom(client_socket, buffer, BUFFER_SIZE, 0,
                                  (struct sockaddr*)&server_addr, &addr_len);
    if (received_bytes == -1) {
        perror("수신 실패");
        exit(EXIT_FAILURE);
    }
    buffer[received_bytes] = '\0';
    printf("서버로부터 받은 응답: %s\n", buffer);

    // 소켓 닫기
    close(client_socket);

    return 0;
}
