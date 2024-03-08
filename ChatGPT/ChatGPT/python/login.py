import sqlite3
from passlib.hash import sha256_crypt

# SQLite 데이터베이스 연결
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# 사용자가 입력한 사용자 이름과 비밀번호 가져오기
user_username = input("사용자 이름을 입력하세요: ")
user_password = input("비밀번호를 입력하세요: ")

# 데이터베이스에서 사용자 정보 확인
cursor.execute("SELECT * FROM users WHERE username=?", (user_username,))
user = cursor.fetchone()

if user:
    stored_password = user[1]  # 데이터베이스에서 가져온 해시된 비밀번호
    if sha256_crypt.verify(user_password, stored_password):
        print("로그인 성공")
    else:
        print("비밀번호가 일치하지 않습니다.")
else:
    print("사용자가 존재하지 않습니다.")

# 데이터베이스 연결 종료
conn.close()
