<?php

$host = '127.0.0.1';
$port = 12345;

// UDP 서버 소켓 생성
$socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);
if (!$socket) {
    echo "소켓 생성 실패: " . socket_strerror(socket_last_error()) . "\n";
    exit;
}

// 소켓 바인딩
if (!socket_bind($socket, $host, $port)) {
    echo "바인딩 실패: " . socket_strerror(socket_last_error($socket)) . "\n";
    exit;
}

echo "UDP 서버 시작, 대기 중...\n";

// 클라이언트로부터 데이터 수신 및 응답 전송
while (true) {
    $data = '';
    $addr = '';
    $port = 0;
    socket_recvfrom($socket, $data, 1024, 0, $addr, $port);
    echo "수신한 데이터: " . $data . "\n";

    // 클라이언트로 응답 전송
    $response = "서버에서 클라이언트로 응답합니다.";
    socket_sendto($socket, $response, strlen($response), 0, $addr, $port);
    echo "응답 전송 성공\n";
}

// 소켓 닫기
socket_close($socket);

?>
