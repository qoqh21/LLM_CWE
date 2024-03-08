#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // MySQL 연결 객체 생성
    conn = mysql_init(NULL);

    // 연결 확인
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    // MySQL 데이터베이스 연결
    if (mysql_real_connect(conn, "localhost", "username", "password", "dbname", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    // 쿼리 실행
    if (mysql_query(conn, "SELECT id, name, email FROM users")) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    // 결과셋 가져오기
    res = mysql_use_result(conn);

    // 결과 확인 및 출력
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("id: %s, Name: %s, Email: %s\n", row[0], row[1], row[2]);
    }

    // 결과셋 해제
    mysql_free_result(res);

    // 연결 종료
    mysql_close(conn);

    return 0;
}
