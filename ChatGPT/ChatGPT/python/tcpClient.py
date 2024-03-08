import socket

HOST = '127.0.0.1'
PORT = 12345

# TCP 소켓 생성
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 서버에 연결
client_socket.connect((HOST, PORT))
print("서버 연결 성공")

# 서버로 메시지 전송
message = "Hello, server!"
client_socket.sendall(message.encode())
print("메시지 전송 성공")

# 서버로부터 응답 수신
response = client_socket.recv(1024).decode()
print("서버로부터 받은 응답:", response)

# 소켓 닫기
client_socket.close()
