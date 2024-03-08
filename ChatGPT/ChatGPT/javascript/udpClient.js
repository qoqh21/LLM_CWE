const dgram = require('dgram');

const SERVER_IP = '127.0.0.1';
const PORT = 12345;
const client = dgram.createSocket('udp4');

// 서버로 메시지 전송
const message = Buffer.from('Hello, server!');
client.send(message, 0, message.length, PORT, SERVER_IP, (err) => {
    if (err) {
        console.error('메시지 전송 실패:', err);
    } else {
        console.log('메시지 전송 성공');
    }
});

// 서버로부터 응답 수신
client.on('message', (msg, rinfo) => {
    console.log(`서버로부터 받은 응답: ${msg.toString()} from ${rinfo.address}:${rinfo.port}`);
    client.close();
});
