#include <stdio.h>
#include <ctype.h>

#define ALPHABET_COUNT 26

int main() {
    char input[100];
    int counts[ALPHABET_COUNT] = {0};

    printf("알파벳을 입력하세요: ");
    fgets(input, sizeof(input), stdin);

    for (int i = 0; input[i] != '\0'; ++i) {
        if (isalpha(input[i])) {
            char c = tolower(input[i]);
            counts[c - 'a']++;
        }
    }

    printf("입력한 알파벳의 개수:\n");
    for (char c = 'a'; c <= 'z'; ++c) {
        printf("%c: %d\n", c, counts[c - 'a']);
    }

    return 0;
}
