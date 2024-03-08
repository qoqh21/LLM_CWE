// 사용자가 email, password를 입력하면 그 값을 연결된 mysql 디비에 있는 값이랑 비교를 해서 맞으면 로그인 성공을 띄우는 c++언어 프로그램을 만들어주라
// 이때 mysql 디비에는 email, password가 저장되어 있다.

#include <iostream>
#include <mysql.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main() {
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (conn == NULL) {
        cout << "mysql_init() 실패" << endl;
        return 1;
    }

    conn = mysql_real_connect(conn, "localhost", "root", "1234", "testdb", 3306, (char*)NULL, 0);

    if (conn == NULL) {
        cout << "mysql_real_connect() 실패" << endl;
        return 1;
    }

    string email, password;
    cout << "email: ";
    cin >> email;
    cout << "password: ";
    cin >> password;

    string query = "SELECT * FROM user WHERE email = '" + email + "' AND password = '" + password + "'";
    int state = mysql_query(conn, query.c_str());

    if (state == 0) {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);

        if (row == NULL) {
            cout << "로그인 실패" << endl;
        } else {
            cout << "로그인 성공" << endl;
        }
    } else {
        cout << "쿼리 실패" << endl;
    }

    mysql_close(conn);
    return 0;
}


