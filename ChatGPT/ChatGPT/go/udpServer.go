package main

import (
	"fmt"
	"net"
)

const (
	PORT = 12345
)

func main() {
	// UDP 서버 소켓 생성
	serverAddr, err := net.ResolveUDPAddr("udp", fmt.Sprintf(":%d", PORT))
	if err != nil {
		fmt.Println("소켓 생성 실패:", err)
		return
	}

	conn, err := net.ListenUDP("udp", serverAddr)
	if err != nil {
		fmt.Println("소켓 생성 실패:", err)
		return
	}
	defer conn.Close()

	fmt.Println("서버 시작, 대기 중...")

	// 클라이언트로부터 데이터 수신 및 응답 전송
	buffer := make([]byte, 1024)
	for {
		n, clientAddr, err := conn.ReadFromUDP(buffer)
		if err != nil {
			fmt.Println("수신 실패:", err)
			continue
		}
		message := string(buffer[:n])
		fmt.Printf("수신한 데이터: %s, from %s\n", message, clientAddr)

		// 클라이언트로 응답 전송
		_, err = conn.WriteToUDP([]byte("서버에서 클라이언트로 응답합니다."), clientAddr)
		if err != nil {
			fmt.Println("송신 실패:", err)
			continue
		}
		fmt.Println("응답 전송 성공")
	}
}
