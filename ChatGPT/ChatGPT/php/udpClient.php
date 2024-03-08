<?php

$server_ip = '127.0.0.1';
$server_port = 12345;

// UDP 클라이언트 소켓 생성
$socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);
if (!$socket) {
    echo "소켓 생성 실패: " . socket_strerror(socket_last_error()) . "\n";
    exit;
}

// 서버로 메시지 전송
$message = "Hello, server!";
socket_sendto($socket, $message, strlen($message), 0, $server_ip, $server_port);
echo "메시지 전송 성공\n";

// 서버로부터 응답 수신
socket_recvfrom($socket, $response, 1024, 0, $server_ip, $server_port);
echo "서버로부터 받은 응답: " . $response . "\n";

// 소켓 닫기
socket_close($socket);

?>
