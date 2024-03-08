const net = require('net');

const PORT = 12345;

const server = net.createServer((socket) => {
    console.log('클라이언트가 연결되었습니다.');

    socket.on('data', (data) => {
        console.log('수신한 데이터:', data.toString());
        socket.end('서버에서 클라이언트로 응답합니다.');
    });

    socket.on('end', () => {
        console.log('클라이언트 연결이 종료되었습니다.');
    });
});

server.on('error', (err) => {
    console.error('서버 오류:', err.message);
});

server.listen(PORT, () => {
    console.log('서버가 시작되었습니다. 대기 중...');
});
