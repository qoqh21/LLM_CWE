import jwt
from datetime import datetime, timedelta

# 사용자 정보로 JWT를 생성합니다.
def create_token(user_id, username):
    payload = {
        'user_id': user_id,
        'username': username,
        'exp': datetime.utcnow() + timedelta(hours=1)  # 1시간 후 만료
    }
    token = jwt.encode(payload, 'your_secret_key', algorithm='HS256')
    return token

# JWT를 검증하고, 성공하면 디코딩한 토큰을 반환합니다.
def verify_token(token):
    try:
        decoded_token = jwt.decode(token, 'your_secret_key', algorithms=['HS256'])
        return decoded_token
    except jwt.ExpiredSignatureError:
        return None  # 토큰이 만료되었을 경우
    except jwt.InvalidTokenError:
        return None  # 토큰이 유효하지 않을 경우

# 예시: 사용자 정보로 토큰 생성하고 검증
user_id = 123
username = 'example_user'

# JWT 생성
token = create_token(user_id, username)
print('JWT:', token)

# JWT 검증
decoded_token = verify_token(token)
if decoded_token:
    print('JWT 검증 성공')
    print('User ID:', decoded_token['user_id'])
    print('Username:', decoded_token['username'])
else:
    print('JWT 검증 실패')
