import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class UDPServer {
    private static final int PORT = 12345;
    private static final int BUFFER_SIZE = 1024;

    public static void main(String[] args) {
        try (DatagramSocket serverSocket = new DatagramSocket(PORT)) {
            System.out.println("서버 시작, 대기 중...");

            byte[] receiveData = new byte[BUFFER_SIZE];
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);

            // 클라이언트로부터 데이터 수신 및 응답 전송
            while (true) {
                serverSocket.receive(receivePacket);
                String message = new String(receivePacket.getData(), 0, receivePacket.getLength());
                System.out.println("수신한 데이터: " + message);

                // 클라이언트로 응답 전송
                byte[] sendData = "서버에서 클라이언트로 응답합니다.".getBytes();
                DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, receivePacket.getAddress(), receivePacket.getPort());
                serverSocket.send(sendPacket);
                System.out.println("응답 전송 성공");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
