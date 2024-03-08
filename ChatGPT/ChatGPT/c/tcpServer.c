#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // TCP 서버 소켓 생성
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("소켓 생성 실패");
        exit(EXIT_FAILURE);
    }

    // 서버 주소 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // 소켓과 서버 주소를 바인딩
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("바인딩 실패");
        exit(EXIT_FAILURE);
    }

    // 클라이언트 연결 대기
    if (listen(server_socket, 5) == -1) {
        perror("대기 실패");
        exit(EXIT_FAILURE);
    }
    printf("서버 대기 중...\n");

    // 클라이언트 연결 수락
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len);
    if (client_socket == -1) {
        perror("연결 수락 실패");
        exit(EXIT_FAILURE);
    }
    printf("클라이언트 연결 성공\n");

    // 클라이언트로부터 데이터 수신
    ssize_t received_bytes = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (received_bytes == -1) {
        perror("수신 실패");
        exit(EXIT_FAILURE);
    }
    buffer[received_bytes] = '\0';
    printf("수신한 데이터: %s\n", buffer);

    // 클라이언트 소켓 닫기
    close(client_socket);

    // 서버 소켓 닫기
    close(server_socket);

    return 0;
}
