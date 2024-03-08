import socket

def three_way_handshake(server_ip, server_port):
    # 클라이언트 소켓 생성
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # 서버에 연결 시도
    client_socket.connect((server_ip, server_port))

    # SYN 패킷 전송
    client_socket.send(b'SYN')
    print("SYN 전송")

    # SYN-ACK 패킷 수신
    syn_ack = client_socket.recv(1024)
    print("SYN-ACK 수신:", syn_ack.decode())

    # ACK 패킷 전송
    client_socket.send(b'ACK')
    print("ACK 전송")

    # 연결 완료 메시지 수신
    connection_established = client_socket.recv(1024)
    print("연결 완료:", connection_established.decode())

    # 소켓 연결 종료
    client_socket.close()

if __name__ == "__main__":
    # 서버의 IP 주소와 포트 번호
    server_ip = '127.0.0.1'
    server_port = 12345

    three_way_handshake(server_ip, server_port)
