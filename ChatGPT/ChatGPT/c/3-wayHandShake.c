#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define SERVER_PORT 12345

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // 소켓 생성
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 서버 주소 설정
    memset(&server_addr, '0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    // IPv4 주소 설정
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        exit(EXIT_FAILURE);
    }

    // 서버에 연결 요청
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // SYN 패킷 전송
    strcpy(buffer, "SYN");
    send(client_socket, buffer, strlen(buffer), 0);
    printf("SYN sent\n");

    // SYN-ACK 패킷 수신
    memset(buffer, 0, sizeof(buffer));
    recv(client_socket, buffer, 1024, 0);
    printf("SYN-ACK received: %s\n", buffer);

    // ACK 패킷 전송
    strcpy(buffer, "ACK");
    send(client_socket, buffer, strlen(buffer), 0);
    printf("ACK sent\n");

    // 연결 완료 메시지 수신
    memset(buffer, 0, sizeof(buffer));
    recv(client_socket, buffer, 1024, 0);
    printf("Connection established: %s\n", buffer);

    // 소켓 연결 종료
    close(client_socket);

    return 0;
}
