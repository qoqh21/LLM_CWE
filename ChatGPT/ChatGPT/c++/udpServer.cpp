#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // UDP 서버 소켓 생성
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == -1) {
        perror("소켓 생성 실패");
        return EXIT_FAILURE;
    }

    // 서버 주소 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // 소켓과 서버 주소를 바인딩
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("바인딩 실패");
        return EXIT_FAILURE;
    }

    std::cout << "서버 시작, 대기 중..." << std::endl;

    // 클라이언트로부터 데이터 수신 및 응답 전송
    while (true) {
        ssize_t received_bytes = recvfrom(server_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &addr_len);
        if (received_bytes == -1) {
            perror("수신 실패");
            continue;
        }
        buffer[received_bytes] = '\0';
        std::cout << "수신한 데이터: " << buffer << std::endl;

        // 클라이언트로 응답 전송
        ssize_t sent_bytes = sendto(server_socket, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, addr_len);
        if (sent_bytes == -1) {
            perror("송신 실패");
            continue;
        }
        std::cout << "응답 전송 성공" << std::endl;
    }

    // 소켓 닫기
    close(server_socket);

    return EXIT_SUCCESS;
}
