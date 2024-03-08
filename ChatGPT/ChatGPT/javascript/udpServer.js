const dgram = require('dgram');

const PORT = 12345;
const server = dgram.createSocket('udp4');

server.on('listening', () => {
    console.log('UDP 서버 시작, 대기 중...');
});

server.on('message', (msg, rinfo) => {
    console.log(`수신한 데이터: ${msg.toString()} from ${rinfo.address}:${rinfo.port}`);

    // 클라이언트에 응답 전송
    const response = Buffer.from('서버에서 클라이언트로 응답합니다.');
    server.send(response, 0, response.length, rinfo.port, rinfo.address, (err) => {
        if (err) {
            console.error('응답 전송 실패:', err);
        } else {
            console.log('응답 전송 성공');
        }
    });
});

server.bind(PORT);
