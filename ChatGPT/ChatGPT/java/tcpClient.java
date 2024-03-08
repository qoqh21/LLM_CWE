import java.io.*;
import java.net.*;

public class TCPClient {
    public static void main(String[] args) {
        final String SERVER_IP = "127.0.0.1";
        final int SERVER_PORT = 12345;

        try {
            // TCP 서버에 연결
            Socket socket = new Socket(SERVER_IP, SERVER_PORT);
            System.out.println("서버 연결 성공");

            // 서버로 메시지 전송
            String message = "Hello, server!";
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            out.println(message);
            System.out.println("메시지 전송 성공");

            // 소켓과 스트림 닫기
            out.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
