const mysql = require('mysql');

// MySQL 데이터베이스 연결 정보
const connection = mysql.createConnection({
    host: 'localhost',
    user: 'username',
    password: 'password',
    database: 'dbname'
});

// 데이터베이스 연결
connection.connect((err) => {
    if (err) {
        console.error('Database connection failed: ' + err.stack);
        return;
    }

    console.log('Database connected as id ' + connection.threadId);

    // 쿼리 실행
    connection.query('SELECT id, name, email FROM users', (err, rows) => {
        if (err) {
            console.error('Error executing query: ' + err.stack);
            return;
        }

        // 결과 처리
        rows.forEach((row) => {
            console.log(`id: ${row.id}, Name: ${row.name}, Email: ${row.email}`);
        });
    });

    // 연결 종료
    connection.end((err) => {
        if (err) {
            console.error('Error closing connection: ' + err.stack);
            return;
        }

        console.log('Connection closed');
    });
});
