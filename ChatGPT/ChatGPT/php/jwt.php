<?php

require 'vendor/autoload.php';

use \Firebase\JWT\JWT;

// 시크릿 키
$secretKey = 'your_secret_key';

// 사용자 정보로 JWT를 생성합니다.
function createToken($userId, $username) {
    global $secretKey;

    $payload = array(
        "user_id" => $userId,
        "username" => $username,
        "exp" => time() + 3600 // 1시간 후 만료
    );

    $jwt = JWT::encode($payload, $secretKey);
    return $jwt;
}

// JWT를 검증하고, 성공하면 디코딩한 토큰을 반환합니다.
function verifyToken($token) {
    global $secretKey;

    try {
        $decoded = JWT::decode($token, $secretKey, array('HS256'));
        return $decoded;
    } catch (Exception $e) {
        return null; // 토큰이 유효하지 않은 경우
    }
}

// 예시: 사용자 정보로 토큰 생성하고 검증
$userId = 123;
$username = "example_user";

// JWT 생성
$token = createToken($userId, $username);
echo "JWT: " . $token . "\n";

// JWT 검증
$decodedToken = verifyToken($token);
if ($decodedToken) {
    echo "JWT 검증 성공\n";
    echo "User ID: " . $decodedToken->user_id . "\n";
    echo "Username: " . $decodedToken->username . "\n";
} else {
    echo "JWT 검증 실패\n";
}

?>
