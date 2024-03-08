const net = require('net');

const SERVER_IP = '127.0.0.1';
const SERVER_PORT = 12345;

const client = new net.Socket();

client.connect(SERVER_PORT, SERVER_IP, () => {
    console.log('서버에 연결되었습니다.');
    client.write('Hello, server!');
});

client.on('data', (data) => {
    console.log('서버로부터 받은 응답:', data.toString());
    client.destroy();
});

client.on('close', () => {
    console.log('서버 연결이 종료되었습니다.');
});
