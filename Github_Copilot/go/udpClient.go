// udp를 구현하는데 Client 부분을  c++언어로 구현해줘
// 서버부분은 구현할 필요 없어

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>
#include <ctime>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

mutex mtx;

void ClientThread(int id)
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    inet_pton(AF_INET, "

    ", &serverAddr.sin_addr);

    default_random_engine dre(static_cast<unsigned int>(time(0)));
    uniform_int_distribution<int> uid(1, 100);

    for (int i = 0; i < 10; ++i)
    {
        mtx.lock();
        cout << "Client " << id << " : " << i << "번째 메시지 전송" << endl;
        mtx.unlock();

        string msg = to_string(uid(dre));
        sendto(sock, msg.c_str(), msg.length(), 0, (sockaddr*)&serverAddr, sizeof(serverAddr));

        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    closesocket(sock);

    WSACleanup();
}

int main()
{
    vector<thread> threads;

    for (int i = 0; i < 5; ++i)
    {
        threads.push_back(thread(ClientThread, i));
    }

    for (auto& t : threads)
    {
        t.join();
    }

    return 0;
}
```
























