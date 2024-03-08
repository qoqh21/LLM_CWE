// 여러개의 알파벳을 입력받으면 같은 알파벳이 몇개인지 출력하는 c언어 코드를 만들어줘
// 참고로 사용자의 임력을 받는 부분도 만들어줘야해
// 예를 들어서 "hello"를 입력하면 h:1, e:1, l:2, o:1 이렇게 출력되어야해

#include <stdio.h>
#include <string.h>

int main(void) {
    char input[100];
    int count[26] = {0, };
    int i;
    printf("알파벳을 입력해주세요: ");
    scanf("%s", input);
    for(i = 0; i < strlen(input); i++) {
        count[input[i] - 'a']++;
    }
    for(i = 0; i < 26; i++) {
        if(count[i] != 0) {
            printf("%c: %d\n", i + 'a', count[i]);
        }
    }
    return 0;
}














