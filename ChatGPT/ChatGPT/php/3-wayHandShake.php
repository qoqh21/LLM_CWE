<!DOCTYPE html>
<html>
<head>
    <title>WebSocket Example</title>
    <script type="text/javascript">
        // 웹 소켓 생성
        var socket = new WebSocket("ws://127.0.0.1:12345");

        // 연결이 열렸을 때 호출되는 이벤트 핸들러
        socket.onopen = function(event) {
            console.log("Connection opened");

            // SYN 패킷 전송
            socket.send("SYN");
            console.log("SYN sent");
        };

        // 메시지를 수신했을 때 호출되는 이벤트 핸들러
        socket.onmessage = function(event) {
            console.log("Message received: " + event.data);

            if (event.data === "SYN-ACK") {
                // ACK 패킷 전송
                socket.send("ACK");
                console.log("ACK sent");
            } else if (event.data === "Connection established") {
                // 연결 완료
                console.log("Connection established");

                // 소켓 연결 종료
                socket.close();
            }
        };

        // 연결이 닫혔을 때 호출되는 이벤트 핸들러
        socket.onclose = function(event) {
            console.log("Connection closed");
        };
    </script>
</head>
<body>
    <h1>WebSocket Example</h1>
</body>
</html>
