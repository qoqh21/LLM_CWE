<?php

$host = "127.0.0.1";
$port = 12345;

// TCP 소켓 생성
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    echo "소켓 생성 실패: " . socket_strerror(socket_last_error()) . "\n";
    exit;
}

// 서버에 연결
if (!socket_connect($socket, $host, $port)) {
    echo "연결 실패: " . socket_strerror(socket_last_error($socket)) . "\n";
    exit;
}
echo "서버 연결 성공\n";

// 서버로 메시지 전송
$message = "Hello, server!";
socket_write($socket, $message, strlen($message));
echo "메시지 전송 성공\n";

// 서버로부터 응답 수신
$response = socket_read($socket, 1024);
echo "서버로부터 받은 응답: " . $response . "\n";

// 소켓 닫기
socket_close($socket);
?>
