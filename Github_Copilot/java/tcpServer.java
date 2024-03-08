// tcp를 구현하는데 Server부분만  c++언어로 구현해줘

#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <map>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
#include <functional>
#include <memory>
#include <atomic>

#pragma comment(lib, "ws2_32.lib")

#define MAX_BUFFER_SIZE 1024
#define MAX_CLIENT 100
#define MAX_THREAD 10

using namespace std;

class Server
{
public:
    Server();
    ~Server();

    void Init();
    void Run();
    void Close();

}

Server::Server()
{
    Init();
}

Server::~Server()
{
    Close();
}

void Server::Init()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    m_listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_listenSocket == INVALID_SOCKET)
    {
        cout << "socket() error" << endl;
        return;
    }

    SOCKADDR_IN serverAddr;
    ZeroMemory(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9000);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(m_listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        cout << "bind() error" << endl;
        return;
    }

    if (listen(m_listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        cout << "listen() error" << endl;
        return;
    }

    m_thread = thread(&Server::Run, this);
}

void Server::Run()
{
    while (true)
    {
        SOCKADDR_IN clientAddr;
        int addrLen = sizeof(clientAddr);
        SOCKET clientSocket = accept(m_listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
        if (clientSocket == INVALID_SOCKET)
        {
            cout << "accept() error" << endl;
            break;
        }

        char recvBuffer[MAX_BUFFER_SIZE];
        int recvLen = recv(clientSocket, recvBuffer, MAX_BUFFER_SIZE, 0);
        if (recvLen > 0)
        {
            recvBuffer[recvLen] = '\0';
            cout << "recv: " << recvBuffer << endl;
        }

        closesocket(clientSocket);
    }
}

void Server::Close()
{
    closesocket(m_listenSocket);
    WSACleanup();
}

int main()
{
    Server server;
    return 0;
}
```









