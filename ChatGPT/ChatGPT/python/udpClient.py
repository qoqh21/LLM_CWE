import socket

HOST = '127.0.0.1'
PORT = 12345

# UDP 소켓 생성
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# 서버로 메시지 전송
message = "Hello, server!"
client_socket.sendto(message.encode(), (HOST, PORT))
print("메시지 전송 성공")

# 서버로부터 응답 수신
response, addr = client_socket.recvfrom(1024)
print("서버로부터 받은 응답:", response.decode(), "from", addr)

# 소켓 닫기
client_socket.close()
