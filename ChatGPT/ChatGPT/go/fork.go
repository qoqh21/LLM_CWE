package main

import (
	"fmt"
	"os/exec"
)

func main() {
	// 실행할 명령어와 인수 설정
	cmd := exec.Command("ls", "-l")

	// 자식 프로세스 실행 및 결과 기다리기
	output, err := cmd.Output()
	if err != nil {
		fmt.Println("Error executing command:", err)
		return
	}

	// 자식 프로세스의 출력 결과 출력
	fmt.Println(string(output))
}
