import socket

HOST = '127.0.0.1'
PORT = 12345

# TCP 소켓 생성
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 소켓 바인딩
server_socket.bind((HOST, PORT))

# 클라이언트 연결 대기
server_socket.listen()

print("서버 시작, 대기 중...")

# 클라이언트 연결 수락
client_socket, addr = server_socket.accept()
print(f"클라이언트 연결 성공: {addr}")

# 클라이언트로부터 데이터 수신
data = client_socket.recv(1024).decode()
print("수신한 데이터:", data)

# 클라이언트로 응답 전송
client_socket.sendall("서버에서 클라이언트로 응답합니다.".encode())

# 소켓 닫기
client_socket.close()
server_socket.close()
