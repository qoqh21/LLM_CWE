#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_PORT 12345

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // 소켓 생성
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return 1;
    }

    // 서버 주소 설정
    memset(&server_addr, '0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    // IPv4 주소 설정
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address / Address not supported" << std::endl;
        return 1;
    }

    // 서버에 연결 요청
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return 1;
    }

    // SYN 패킷 전송
    strcpy(buffer, "SYN");
    send(client_socket, buffer, strlen(buffer), 0);
    std::cout << "SYN sent" << std::endl;

    // SYN-ACK 패킷 수신
    memset(buffer, 0, sizeof(buffer));
    recv(client_socket, buffer, 1024, 0);
    std::cout << "SYN-ACK received: " << buffer << std::endl;

    // ACK 패킷 전송
    strcpy(buffer, "ACK");
    send(client_socket, buffer, strlen(buffer), 0);
    std::cout << "ACK sent" << std::endl;

    // 연결 완료 메시지 수신
    memset(buffer, 0, sizeof(buffer));
    recv(client_socket, buffer, 1024, 0);
    std::cout << "Connection established: " << buffer << std::endl;

    // 소켓 연결 종료
    close(client_socket);

    return 0;
}
