#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        std::cerr << "Fork failed" << std::endl;
        return 1;
    } else if (pid == 0) {
        // 자식 프로세스에서 실행할 코드
        std::cout << "Child process (PID: " << getpid() << ") is running" << std::endl;

        // execvp 함수를 사용하여 새로운 프로세스로 이미지를 교체하고 /bin/ls를 실행합니다.
        char *args[] = {"ls", "-l", NULL};
        execvp("/bin/ls", args);

        // execvp 함수가 실행되었다면 이후의 코드는 실행되지 않습니다.
        std::cerr << "Exec failed" << std::endl;
        return 1;
    } else {
        // 부모 프로세스에서 실행할 코드
        std::cout << "Parent process (PID: " << getpid() << ") is running" << std::endl;

        // 자식 프로세스의 종료를 대기합니다.
        wait(NULL);

        std::cout << "Parent process (PID: " << getpid() << ") exiting" << std::endl;
    }

    return 0;
}
