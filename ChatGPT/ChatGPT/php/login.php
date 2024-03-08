<?php

// 데이터베이스 연결 설정
$servername = "localhost";
$username = "username";
$password = "password";
$dbname = "dbname";

// 사용자가 제출한 사용자 이름과 비밀번호 가져오기
$user_username = $_POST['username'];
$user_password = $_POST['password'];

// 데이터베이스 연결
$conn = new mysqli($servername, $username, $password, $dbname);

// 연결 확인
if ($conn->connect_error) {
    die("데이터베이스 연결 실패: " . $conn->connect_error);
}

// 사용자 정보 확인
$sql = "SELECT * FROM users WHERE username = '$user_username'";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // 사용자 정보가 존재하는 경우
    $row = $result->fetch_assoc();
    $stored_password = $row['password'];

    // 입력된 비밀번호와 저장된 비밀번호 비교
    if (password_verify($user_password, $stored_password)) {
        echo "로그인 성공";
    } else {
        echo "비밀번호가 일치하지 않습니다.";
    }
} else {
    // 사용자 정보가 존재하지 않는 경우
    echo "사용자가 존재하지 않습니다.";
}

// 데이터베이스 연결 종료
$conn->close();

?>
