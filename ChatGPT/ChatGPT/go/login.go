package main

import (
	"database/sql"
	"fmt"
	"log"
	"os"
	"strings"

	_ "github.com/mattn/go-sqlite3"
	"golang.org/x/crypto/bcrypt"
)

const (
	dbPath = "users.db"
)

func main() {
	// 사용자가 입력한 사용자 이름과 비밀번호 가져오기
	var userUsername, userPassword string
	fmt.Print("사용자 이름을 입력하세요: ")
	fmt.Scanln(&userUsername)
	fmt.Print("비밀번호를 입력하세요: ")
	fmt.Scanln(&userPassword)

	// 데이터베이스 연결
	db, err := sql.Open("sqlite3", dbPath)
	if err != nil {
		log.Fatalf("데이터베이스 연결 오류: %v\n", err)
	}
	defer db.Close()

	// 사용자 정보 확인
	var storedPassword string
	err = db.QueryRow("SELECT password FROM users WHERE username=?", userUsername).Scan(&storedPassword)
	switch {
	case err == sql.ErrNoRows:
		fmt.Println("사용자가 존재하지 않습니다.")
	case err != nil:
		log.Fatalf("사용자 정보 확인 오류: %v\n", err)
	default:
		if bcrypt.CompareHashAndPassword([]byte(storedPassword), []byte(userPassword)) == nil {
			fmt.Println("로그인 성공")
		} else {
			fmt.Println("비밀번호가 일치하지 않습니다.")
		}
	}
}
