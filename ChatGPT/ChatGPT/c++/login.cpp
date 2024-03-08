#include <iostream>
#include <sqlite3.h>
#include <string>
#include <cstring>
#include <openssl/sha.h>

using namespace std;

#define DB_FILE "users.db"
#define HASH_LENGTH 64

// 비밀번호를 해싱하는 함수
string hash_password(const string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.length());
    SHA256_Final(hash, &sha256);
    char hashed_password[HASH_LENGTH + 1];
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    return string(hashed_password);
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
    string user_username, user_password;
    string sql;

    // 사용자가 입력한 사용자 이름과 비밀번호 가져오기
    cout << "사용자 이름을 입력하세요: ";
    cin >> user_username;
    cout << "비밀번호를 입력하세요: ";
    cin >> user_password;

    // 데이터베이스 연결
    rc = sqlite3_open(DB_FILE, &db);
    if( rc ) {
        cerr << "데이터베이스 열기 오류: " << sqlite3_errmsg(db) << endl;
        return 0;
    }

    // 사용자 정보 확인
    string hashed_password = hash_password(user_password);
    sql = "SELECT * FROM users WHERE username='" + user_username + "' AND password='" + hashed_password + "';";
    rc = sqlite3_exec(db, sql.c_str(), get_user_callback, &found_user, &zErrMsg);

    if( rc != SQLITE_OK ) {
        cerr << "SQL 오류: " << zErrMsg << endl;
        sqlite3_free(zErrMsg);
    }

    // 로그인 결과 출력
    if (found_user) {
        cout << "로그인 성공" << endl;
    } else {
        cout << "사용자가 존재하지 않거나 비밀번호가 일치하지 않습니다." << endl;
    }

    // 데이터베이스 연결 종료
    sqlite3_close(db);

    return 0;
}
