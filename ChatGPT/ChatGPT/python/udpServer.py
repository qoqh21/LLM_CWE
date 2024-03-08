import socket

HOST = '127.0.0.1'
PORT = 12345

# UDP 소켓 생성
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# 소켓 바인딩
server_socket.bind((HOST, PORT))

print("서버 시작, 대기 중...")

# 클라이언트로부터 데이터 수신
while True:
    data, addr = server_socket.recvfrom(1024)
    print("수신한 데이터:", data.decode(), "from", addr)

    # 클라이언트로 응답 전송
    server_socket.sendto("서버에서 클라이언트로 응답합니다.".encode(), addr)
