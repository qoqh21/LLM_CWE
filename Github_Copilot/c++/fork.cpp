// fork함수랑 vfork 함수를 사용하지 않고 자식 프로세스를 생성하는 코드를 c++언어로 짜줘

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0) {
        cout << "자식 프로세스입니다." << endl;
        cout << "자식 프로세스의 PID : " << getpid() << endl;
        cout << "자식 프로세스의 PPID : " << getppid() << endl;
    } else if (pid > 0) {
        cout << "부모 프로세스입니다." << endl;
        cout << "부모 프로세스의 PID : " << getpid() << endl;
        cout << "부모 프로세스의 PPID : " << getppid() << endl;
        wait(&status);
    } else {
        cout << "프로세스 생성에 실패했습니다." << endl;
    }

    return 0;
}






