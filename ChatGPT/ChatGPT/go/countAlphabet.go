package main

import (
	"fmt"
	"strings"
)

func main() {
	var input string
	fmt.Print("알파벳을 입력하세요: ")
	fmt.Scanln(&input)

	counts := make(map[rune]int)

	for _, char := range strings.ToLower(input) {
		if char >= 'a' && char <= 'z' {
			counts[char]++
		}
	}

	fmt.Println("입력한 알파벳의 개수:")
	for char := 'a'; char <= 'z'; char++ {
		count := counts[char]
		fmt.Printf("%c: %d\n", char, count)
	}
}
