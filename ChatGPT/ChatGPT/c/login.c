#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <stdbool.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define HASH_LENGTH 64

// 비밀번호를 해싱하는 함수
char* hash_password(const char *password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    char *hashed_password = malloc((HASH_LENGTH + 1) * sizeof(char));
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    return hashed_password;
}

// 데이터베이스에서 사용자 정보를 가져오는 콜백 함수
static int get_user_callback(void *data, int argc, char **argv, char **azColName){
    bool *found_user = (bool*)data;
    *found_user = true;
    return 0;
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    bool found_user = false;
    char *sql;
    const char *data = "Callback function called";

    // 사용자가 입력한 사용자 이름과 비밀번호 가져오기
    char user_username[50];
    char user_password[50];
    printf("사용자 이름을 입력하세요: ");
    scanf("%s", user_username);
    printf("비밀번호를 입력하세요: ");
    scanf("%s", user_password);

    // 데이터베이스 연결
    rc = sqlite3_open(DB_FILE, &db);
    if( rc ) {
        fprintf(stderr, "데이터베이스 열기 오류: %s\n", sqlite3_errmsg(db));
        return(0);
    }

    // 사용자 정보 확인
    char *hashed_password = hash_password(user_password);
    sql = sqlite3_mprintf("SELECT * FROM users WHERE username='%s' AND password='%s';", user_username, hashed_password);
    rc = sqlite3_exec(db, sql, get_user_callback, &found_user, &zErrMsg);
    sqlite3_free(sql);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL 오류: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    // 로그인 결과 출력
    if (found_user) {
        printf("로그인 성공\n");
    } else {
        printf("사용자가 존재하지 않거나 비밀번호가 일치하지 않습니다.\n");
    }

    // 데이터베이스 연결 종료
    sqlite3_close(db);

    return 0;
}
