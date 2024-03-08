// 사용자가 email, password를 입력하면 그 값을 연결된 mysql 디비에 있는 값이랑 비교를 해서 맞으면 로그인 성공을 띄우는 c언어 프로그램을 만들어줘

#include <stdio.h>

int main() {
    char email[100];
    char password[100];
    char email_db[100];
    char password_db[100];
    int is_login = 0;

    printf("email: ");
    scanf("%s", email);
    printf("password: ");
    scanf("%s", password);

    FILE *fp = fopen("db.txt", "r");
    while (fscanf(fp, "%s %s", email_db, password_db) != EOF) {
        if (strcmp(email, email_db) == 0 && strcmp(password, password_db) == 0) {
            is_login = 1;
            break;
        }
    }
    fclose(fp);

    if (is_login) {
        printf("로그인 성공\n");
    } else {
        printf("로그인 실패\n");
    }
    return 0;
}