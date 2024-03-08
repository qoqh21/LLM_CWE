const sqlite3 = require('sqlite3').verbose();
const readline = require('readline');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

const DB_FILE = 'users.db';

// 데이터베이스 연결
const db = new sqlite3.Database(DB_FILE, sqlite3.OPEN_READONLY, (err) => {
    if (err) {
        console.error('데이터베이스 연결 오류:', err.message);
    } else {
        console.log('데이터베이스 연결 성공');
    }
});

// 사용자가 입력한 사용자 이름과 비밀번호 가져오기
rl.question('사용자 이름을 입력하세요: ', (userUsername) => {
    rl.question('비밀번호를 입력하세요: ', (userPassword) => {
        // 사용자 정보 확인
        const sql = `SELECT password FROM users WHERE username='${userUsername}'`;
        db.get(sql, (err, row) => {
            if (err) {
                console.error('사용자 정보 확인 오류:', err.message);
                return;
            }
            if (!row) {
                console.log('사용자가 존재하지 않습니다.');
            } else {
                const storedPassword = row.password;
                if (storedPassword === userPassword) {
                    console.log('로그인 성공');
                } else {
                    console.log('비밀번호가 일치하지 않습니다.');
                }
            }
            rl.close();
            db.close();
        });
    });
});
