import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) {
        try {
            // 실행할 명령어 및 인수 설정
            ProcessBuilder processBuilder = new ProcessBuilder("ls", "-l");

            // 자식 프로세스 실행
            Process process = processBuilder.start();

            // 자식 프로세스의 출력 스트림을 읽기 위한 BufferedReader 생성
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;

            // 자식 프로세스의 출력 읽어오기
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            // 프로세스의 종료 대기
            int exitCode = process.waitFor();

            // 프로세스 종료 코드 출력
            System.out.println("Process exited with code " + exitCode);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}
