// c로 3-wayHandShake를 구현한 코드를 만들어주는데 이 파일 안에 다 구현해줘

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[] = "Hello World!";

    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
    {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        error_handling("bind() error");
    }

    if (listen(serv_sock, 5) == -1)
    {
        error_handling("listen() error");
    }

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    if (clnt_sock == -1)
    {
        error_handling("accept() error");
    }

    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

// 이 코드는 3-wayHandShake를 구현한 코드이다.
// 3-wayHandShake는 서버와 클라이언트가 통신을 시작하기 전에 3번의 메시지를 주고 받는 과정이다.
// 1. 클라이언트가 서버에게 연결 요청을 보내는 과정
// 2. 서버가 클라이언트에게 연결 요청을 수락하는 과정
// 3. 클라이언트가 서버에게 연결 요청을 수락했다는 메시지를 보내는 과정
// 이 과정을 통해 서버와 클라이언트는 통신을 시작할 준비가 되었다는 것을 알 수 있다.
// 이 코드는 서버의 입장에서 3-wayHandShake를 구현한 코드이다.
// 클라이언트의 입장에서 3-wayHandShake를 구현한 코드는 3-wayHandShake_client.c에 있다.
// 이 코드를 실행하면 서버는 클라이언트의 연결 요청을 기다리고 있다가 클라이언트가 연결 요청을 보내면 연결을 수락하고 클라이언트에게 "Hello World!"라는 메시지를 보낸다.
// 그리고 클라이언트와의 연결을 끊는다.
// 이 코드를 실행하려면 3-wayHandShake_client.c를 먼저 실행시켜야 한다.
// 3-wayHandShake_client.c를 실행시키면 서버에게 연결 요청을 보내고 서버는 연결 요청을 수락하고 "Hello World!"라는 메시지를 보내고 연결을 끊는다.
// 이 코드를 실행시키면 서버는 클라이언트의 연결 요청을 기다리고 있다가 클라이언트가 연결 요청을 보내면 연결을 수락하고 "Hello World!"라는 메시지를 보낸다.
// 그리고 클라이언트와의 연결을 끊는다.
