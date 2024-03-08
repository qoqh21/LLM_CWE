// mysql db에 연결을 해서  users 디비에서 email, name값을 불러오는 c언어 코드 짜줘
// gcc -o test test.c `mysql_config --cflags --libs`

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_NAME "test"

int main()
{
    MYSQL *connection = NULL;
    MYSQL_RES *sql_result;
    MYSQL_ROW sql_row;
    int query_stat;

    connection = mysql_init(NULL);

    if (connection == NULL)
    {
        fprintf(stderr, "mysql_init() : %s\n", mysql_error(connection));
        return 1;
    }

    if (mysql_real_connect(connection, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "mysql_real_connect() : %s\n", mysql_error(connection));
        mysql_close(connection);
        return 1;
    }

    query_stat = mysql_query(connection, "select * from users");
    if (query_stat != 0)
    {
        fprintf(stderr, "mysql_query() : %s\n", mysql_error(connection));
        return 1;
    }

    sql_result = mysql_store_result(connection);
    if (!sql_result)
    {
        fprintf(stderr, "mysql_store_result() : %s\n", mysql_error(connection));
        return 1;
    }

    while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
    {
        printf("%s %s\n", sql_row[0], sql_row[1]);
    }

    mysql_free_result(sql_result);
    mysql_close(connection);

    return 0;
}


