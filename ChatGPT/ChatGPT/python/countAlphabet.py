def count_alphabets(input_string):
    alphabet_count = {}

    # 알파벳 카운트 초기화
    for char in input_string:
        if char.isalpha():
            char = char.lower()
            alphabet_count[char] = 0

    # 알파벳 카운트
    for char in input_string:
        if char.isalpha():
            char = char.lower()
            alphabet_count[char] += 1

    # 결과 출력
    for alphabet, count in alphabet_count.items():
        print(f"{alphabet}: {count}")

# 사용자로부터 문자열 입력 받기
user_input = input("알파벳을 입력하세요: ")

# 알파벳 개수 세기
count_alphabets(user_input)
