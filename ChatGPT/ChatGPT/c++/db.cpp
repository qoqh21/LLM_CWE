#include <iostream>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // MySQL 연결 객체 생성
    conn = mysql_init(NULL);

    // 연결 확인
    if (conn == NULL) {
        std::cerr << "mysql_init() failed" << std::endl;
        return 1;
    }

    // MySQL 데이터베이스 연결
    if (mysql_real_connect(conn, "localhost", "username", "password", "dbname", 0, NULL, 0) == NULL) {
        std::cerr << "mysql_real_connect() failed: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    // 쿼리 실행
    if (mysql_query(conn, "SELECT id, name, email FROM users")) {
        std::cerr << "mysql_query() failed: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    // 결과셋 가져오기
    res = mysql_use_result(conn);

    // 결과 확인 및 출력
    while ((row = mysql_fetch_row(res)) != NULL) {
        std::cout << "id: " << row[0] << ", Name: " << row[1] << ", Email: " << row[2] << std::endl;
    }

    // 결과셋 해제
    mysql_free_result(res);

    // 연결 종료
    mysql_close(conn);

    return 0;
}
