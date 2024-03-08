package main

import (
	"fmt"
	"net"
)

const (
	PORT = ":12345"
)

func handleConnection(conn net.Conn) {
	defer conn.Close()

	// 클라이언트로부터 메시지 수신
	buffer := make([]byte, 1024)
	n, err := conn.Read(buffer)
	if err != nil {
		fmt.Println("수신 실패:", err)
		return
	}
	message := string(buffer[:n])
	fmt.Println("수신한 메시지:", message)
}

func main() {
	// TCP 서버 시작
	listener, err := net.Listen("tcp", PORT)
	if err != nil {
		fmt.Println("서버 시작 실패:", err)
		return
	}
	defer listener.Close()
	fmt.Println("서버 시작, 대기 중...")

	// 클라이언트 연결 대기
	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("연결 수락 실패:", err)
			continue
		}
		fmt.Println("클라이언트 연결 성공")

		// 클라이언트와 통신
		go handleConnection(conn)
	}
}
