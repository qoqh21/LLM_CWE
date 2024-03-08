import java.io.*;
import java.net.*;

public class ThreeWayHandshakeClient {
    public static void main(String[] args) {
        final String serverAddress = "127.0.0.1";
        final int serverPort = 12345;

        try {
            // 소켓 생성
            Socket socket = new Socket(serverAddress, serverPort);

            // 데이터 입력 및 출력 스트림 생성
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

            // SYN 패킷 전송
            out.println("SYN");
            System.out.println("SYN sent");

            // SYN-ACK 패킷 수신
            String response = in.readLine();
            System.out.println("SYN-ACK received: " + response);

            // ACK 패킷 전송
            out.println("ACK");
            System.out.println("ACK sent");

            // 연결 완료 메시지 수신
            response = in.readLine();
            System.out.println("Connection established: " + response);

            // 소켓 및 입출력 스트림 닫기
            socket.close();
            out.close();
            in.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
