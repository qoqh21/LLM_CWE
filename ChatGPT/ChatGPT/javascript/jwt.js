const express = require('express');
const jwt = require('jsonwebtoken');
const bodyParser = require('body-parser');

const app = express();
const secretKey = 'your_secret_key'; // 임의의 시크릿 키 사용

app.use(bodyParser.json());

// 사용자 데이터베이스 대신에 간단한 사용자 목록을 생성
const users = [
    { id: 1, username: 'user1', password: 'password1' },
    { id: 2, username: 'user2', password: 'password2' }
];

// 로그인 엔드포인트
app.post('/login', (req, res) => {
    const { username, password } = req.body;

    // 사용자 인증
    const user = users.find(u => u.username === username && u.password === password);
    if (!user) {
        return res.status(401).json({ message: '인증 실패' });
    }

    // JWT 토큰 생성
    const token = jwt.sign({ userId: user.id }, secretKey, { expiresIn: '1h' }); // 토큰 만료 시간 설정

    // 토큰을 클라이언트에게 전송
    res.json({ token });
});

// 보호된 엔드포인트
app.get('/protected', verifyToken, (req, res) => {
    res.json({ message: '보호된 엔드포인트에 접근 성공' });
});

// 토큰 검증 미들웨어
function verifyToken(req, res, next) {
    // 헤더에서 토큰 가져오기
    const bearerHeader = req.headers['authorization'];
    if (typeof bearerHeader !== 'undefined') {
        // 헤더 형식: Bearer <token>
        const token = bearerHeader.split(' ')[1];
        req.token = token;
        jwt.verify(token, secretKey, (err, authData) => {
            if (err) {
                res.status(403).json({ message: '토큰이 유효하지 않습니다.' });
            } else {
                req.authData = authData;
                next(); // 다음 미들웨어 호출
            }
        });
    } else {
        // 헤더에 토큰이 없음
        res.status(403).json({ message: '인증 토큰이 필요합니다.' });
    }
}

// 서버 시작
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => console.log(`서버가 포트 ${PORT}에서 실행 중입니다.`));
