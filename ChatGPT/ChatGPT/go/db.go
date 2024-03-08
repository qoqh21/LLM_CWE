package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/go-sql-driver/mysql"
)

func main() {
	// MySQL 데이터베이스 연결 정보
	db, err := sql.Open("mysql", "username:password@tcp(127.0.0.1:3306)/dbname")
	if err != nil {
		log.Fatal(err)
	}
	defer db.Close()

	// 데이터베이스 연결 확인
	err = db.Ping()
	if err != nil {
		log.Fatal(err)
	}

	// 쿼리 실행
	rows, err := db.Query("SELECT id, name, email FROM users")
	if err != nil {
		log.Fatal(err)
	}
	defer rows.Close()

	// 결과 처리
	for rows.Next() {
		var id int
		var name, email string
		err := rows.Scan(&id, &name, &email)
		if err != nil {
			log.Fatal(err)
		}
		fmt.Printf("id: %d, Name: %s, Email: %s\n", id, name, email)
	}
	err = rows.Err()
	if err != nil {
		log.Fatal(err)
	}
}
