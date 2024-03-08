#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    char buffer[BUFFER_SIZE];

    // UDP 클라이언트 소켓 생성
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        perror("소켓 생성 실패");
        return EXIT_FAILURE;
    }

    // 서버 주소 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);

    // 서버로 메시지 전송
    const char* message = "Hello, server!";
    ssize_t sent_bytes = sendto(client_socket, message, strlen(message), 0, (struct sockaddr*)&server_addr, addr_len);
    if (sent_bytes == -1) {
        perror("전송 실패");
        return EXIT_FAILURE;
    }
    std::cout << "메시지 전송 성공" << std::endl;

    // 서버로부터 응답 수신
    ssize_t received_bytes = recvfrom(client_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&server_addr, &addr_len);
    if (received_bytes == -1) {
        perror("수신 실패");
        return EXIT_FAILURE;
    }
    buffer[received_bytes] = '\0';
    std::cout << "서버로부터 받은 응답: " << buffer << std::endl;

    // 소켓 닫기
    close(client_socket);

    return EXIT_SUCCESS;
}
