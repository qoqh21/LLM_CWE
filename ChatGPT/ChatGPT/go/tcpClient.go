package main

import (
	"fmt"
	"net"
)

const (
	SERVER_ADDR = "127.0.0.1"
	SERVER_PORT = "12345"
)

func main() {
	// TCP 서버에 연결
	conn, err := net.Dial("tcp", SERVER_ADDR+":"+SERVER_PORT)
	if err != nil {
		fmt.Println("서버 연결 실패:", err)
		return
	}
	defer conn.Close()
	fmt.Println("서버 연결 성공")

	// 서버로 메시지 전송
	message := "Hello, server!"
	_, err = conn.Write([]byte(message))
	if err != nil {
		fmt.Println("메시지 전송 실패:", err)
		return
	}
	fmt.Println("메시지 전송 성공")
}
