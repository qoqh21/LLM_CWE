package main

import (
	"fmt"
	"net"
)

const (
	SERVER_IP = "127.0.0.1"
	PORT      = 12345
)

func main() {
	// 서버 주소 설정
	serverAddr, err := net.ResolveUDPAddr("udp", fmt.Sprintf("%s:%d", SERVER_IP, PORT))
	if err != nil {
		fmt.Println("주소 설정 실패:", err)
		return
	}

	// UDP 클라이언트 소켓 생성
	conn, err := net.DialUDP("udp", nil, serverAddr)
	if err != nil {
		fmt.Println("소켓 생성 실패:", err)
		return
	}
	defer conn.Close()

	fmt.Println("서버에 연결되었습니다.")

	// 서버로 메시지 전송
	message := "Hello, server!"
	_, err = conn.Write([]byte(message))
	if err != nil {
		fmt.Println("메시지 전송 실패:", err)
		return
	}
	fmt.Println("메시지 전송 성공")

	// 서버로부터 응답 수신
	buffer := make([]byte, 1024)
	n, _, err := conn.ReadFromUDP(buffer)
	if err != nil {
		fmt.Println("응답 수신 실패:", err)
		return
	}
	response := string(buffer[:n])
	fmt.Println("서버로부터 받은 응답:", response)
}
