const net = require('net');

// TCP 서버 생성
const server = net.createServer((socket) => {
    console.log('클라이언트가 연결되었습니다.');

    // 클라이언트와의 데이터 송수신
    socket.on('data', (data) => {
        console.log('클라이언트로부터 데이터 수신:', data.toString());

        // 3-way handshake 응답 전송
        if (data.toString() === 'SYN') {
            console.log('SYN 수신, ACK 전송');
            socket.write('ACK');
        } else if (data.toString() === 'ACK') {
            console.log('ACK 수신, 연결 완료');
        }
    });

    // 소켓 연결 종료 처리
    socket.on('close', () => {
        console.log('클라이언트와의 연결이 종료되었습니다.');
    });
});

// TCP 서버가 3000 포트에서 대기
const PORT = 3000;
server.listen(PORT, () => {
    console.log(`TCP 서버가 ${PORT} 포트에서 대기 중입니다.`);
});
