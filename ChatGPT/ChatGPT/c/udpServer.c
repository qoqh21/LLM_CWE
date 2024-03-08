#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // UDP 소켓 생성
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
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

    printf("서버 시작, 대기 중...\n");

    // 클라이언트로부터 데이터 수신 및 응답 전송
    while (1) {
        int received_bytes = recvfrom(server_socket, buffer, BUFFER_SIZE, 0,
                                      (struct sockaddr*)&client_addr, &addr_len);
        if (received_bytes == -1) {
            perror("수신 실패");
            exit(EXIT_FAILURE);
        }
        buffer[received_bytes] = '\0';
        printf("수신한 데이터: %s\n", buffer);

        // 클라이언트로 응답 전송
        const char* response = "서버에서 클라이언트로 응답합니다.";
        sendto(server_socket, response, strlen(response), 0,
               (struct sockaddr*)&client_addr, addr_len);
    }

    // 소켓 닫기
    close(server_socket);

    return 0;
}
