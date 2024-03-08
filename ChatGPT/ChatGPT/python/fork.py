import subprocess

# ls 명령어를 실행하여 자식 프로세스 생성
process = subprocess.Popen(['ls', '-l'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# 자식 프로세스의 표준 출력과 표준 오류를 읽어와 출력
output, error = process.communicate()
if output:
    print("Output:")
    print(output.decode())
if error:
    print("Error:")
    print(error.decode())

# 자식 프로세스의 종료 코드 출력
print("Exit code:", process.returncode)
