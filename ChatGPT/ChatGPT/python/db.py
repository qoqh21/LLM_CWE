import mysql.connector

# MySQL 데이터베이스 연결 정보
config = {
    'host': 'localhost',
    'user': 'username',
    'password': 'password',
    'database': 'dbname'
}

# MySQL 데이터베이스 연결
try:
    conn = mysql.connector.connect(**config)
    print("Database connected successfully")

    # 쿼리 실행
    cursor = conn.cursor()
    cursor.execute("SELECT id, name, email FROM users")

    # 결과 처리
    for (id, name, email) in cursor:
        print(f"id: {id}, Name: {name}, Email: {email}")

    # 연결 종료
    cursor.close()
    conn.close()
except mysql.connector.Error as e:
    print("Database connection failed:", e)
