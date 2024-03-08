<?php

// MySQL 서버 연결 정보
$servername = "localhost";
$username = "username";
$password = "password";
$dbname = "dbname";

// MySQL 데이터베이스 연결
$conn = new mysqli($servername, $username, $password, $dbname);

// 연결 확인
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// 쿼리 실행
$sql = "SELECT id, name, email FROM users";
$result = $conn->query($sql);

// 결과 확인 및 출력
if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {
        echo "id: " . $row["id"]. " - Name: " . $row["name"]. " - Email: " . $row["email"]. "<br>";
    }
} else {
    echo "0 results";
}

// 연결 종료
$conn->close();

?>
