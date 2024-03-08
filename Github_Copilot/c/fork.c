// fork함수랑 vfork 함수를 사용하지 않고 자식 프로세스를 생성하는 코드를 c언어로 짜줘

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
    pid_t pid;
    int x = 1;

    pid = fork();
    if (pid > 0) {
        printf("parent: x=%d\n", ++x);
    } else if (pid == 0) {
        printf("child: x=%d\n", --x);
    } else {
        perror("fork");
        exit(1);
    }
    printf("Bye from process %d with x=%d\n", getpid(), x);
    return 0;
}




