import java.io.*;
import java.net.*;

public class TCPServer {
    public static void main(String[] args) {
        final int PORT = 12345;

        try {
            // TCP 서버 소켓 생성
            ServerSocket serverSocket = new ServerSocket(PORT);
            System.out.println("서버 시작, 대기 중...");

            // 클라이언트 연결 대기
            Socket clientSocket = serverSocket.accept();
            System.out.println("클라이언트 연결 성공");

            // 클라이언트와 통신
            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            String message = in.readLine();
            System.out.println("수신한 메시지: " + message);

            // 소켓과 스트림 닫기
            in.close();
            clientSocket.close();
            serverSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
