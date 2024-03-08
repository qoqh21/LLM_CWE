package main

import (
    "fmt"
    "net"
)

func main() {
    serverAddress := "127.0.0.1:12345"

    // TCP 소켓 열기
    listener, err := net.Listen("tcp", serverAddress)
    if err != nil {
        fmt.Println("Error listening:", err.Error())
        return
    }
    defer listener.Close()

    fmt.Println("Server listening on", serverAddress)

    // 클라이언트 연결 대기
    conn, err := listener.Accept()
    if err != nil {
        fmt.Println("Error accepting:", err.Error())
        return
    }
    defer conn.Close()

    fmt.Println("Connection established with", conn.RemoteAddr())

    // SYN 패킷 수신 및 처리
    synBuffer := make([]byte, 1024)
    _, err = conn.Read(synBuffer)
    if err != nil {
        fmt.Println("Error reading SYN:", err.Error())
        return
    }
    fmt.Println("SYN received:", string(synBuffer))

    // SYN-ACK 패킷 전송
    _, err = conn.Write([]byte("SYN-ACK"))
    if err != nil {
        fmt.Println("Error writing SYN-ACK:", err.Error())
        return
    }
    fmt.Println("SYN-ACK sent")

    // ACK 패킷 수신 및 처리
    ackBuffer := make([]byte, 1024)
    _, err = conn.Read(ackBuffer)
    if err != nil {
        fmt.Println("Error reading ACK:", err.Error())
        return
    }
    fmt.Println("ACK received:", string(ackBuffer))

    // 연결 완료 메시지 전송
    _, err = conn.Write([]byte("Connection established"))
    if err != nil {
        fmt.Println("Error writing connection message:", err.Error())
        return
    }
    fmt.Println("Connection established message sent")
}
