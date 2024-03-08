<?php

$host = "127.0.0.1";
$port = 12345;

// TCP 소켓 생성
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    echo "소켓 생성 실패: " . socket_strerror(socket_last_error()) . "\n";
    exit;
}

// 소켓 바인딩
if (!socket_bind($socket, $host, $port)) {
    echo "바인딩 실패: " . socket_strerror(socket_last_error($socket)) . "\n";
    exit;
}

// 클라이언트 연결 대기
if (!socket_listen($socket, 5)) {
    echo "대기 실패: " . socket_strerror(socket_last_error($socket)) . "\n";
    exit;
}
echo "서버 시작, 대기 중...\n";

// 클라이언트 연결 수락
$clientSocket = socket_accept($socket);
if ($clientSocket === false) {
    echo "연결 수락 실패: " . socket_strerror(socket_last_error($socket)) . "\n";
    exit;
}
echo "클라이언트 연결 성공\n";

// 클라이언트로부터 데이터 수신
$input = socket_read($clientSocket, 1024);
echo "수신한 데이터: " . $input . "\n";

// 클라이언트로 응답 전송
$output = "서버에서 클라이언트로 응답합니다.";
socket_write($clientSocket, $output, strlen($output));

// 소켓 닫기
socket_close($clientSocket);
socket_close($socket);
?>
