package main

import (
	"fmt"
	"time"

	"github.com/dgrijalva/jwt-go"
)

var secretKey = []byte("your_secret_key")

// 사용자 정보로 JWT를 생성합니다.
func createToken(userID int, username string) (string, error) {
	token := jwt.NewWithClaims(jwt.SigningMethodHS256, jwt.MapClaims{
		"user_id":  userID,
		"username": username,
		"exp":      time.Now().Add(time.Hour).Unix(), // 1시간 후 만료
	})

	tokenString, err := token.SignedString(secretKey)
	if err != nil {
		return "", err
	}

	return tokenString, nil
}

// JWT를 검증하고, 성공하면 디코딩한 토큰을 반환합니다.
func verifyToken(tokenString string) (jwt.MapClaims, error) {
	token, err := jwt.Parse(tokenString, func(token *jwt.Token) (interface{}, error) {
		return secretKey, nil
	})
	if err != nil {
		return nil, err
	}

	if claims, ok := token.Claims.(jwt.MapClaims); ok && token.Valid {
		return claims, nil
	} else {
		return nil, fmt.Errorf("invalid token")
	}
}

func main() {
	// 예시: 사용자 정보로 토큰 생성하고 검증
	userID := 123
	username := "example_user"

	// JWT 생성
	token, err := createToken(userID, username)
	if err != nil {
		fmt.Println("Failed to create token:", err)
		return
	}
	fmt.Println("JWT:", token)

	// JWT 검증
	claims, err := verifyToken(token)
	if err != nil {
		fmt.Println("JWT 검증 실패:", err)
		return
	}
	fmt.Println("JWT 검증 성공")
	fmt.Println("User ID:", claims["user_id"])
	fmt.Println("Username:", claims["username"])
}
