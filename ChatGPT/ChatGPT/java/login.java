import java.sql.*;

public class Main {
    static final String DB_URL = "jdbc:sqlite:users.db";

    public static void main(String[] args) {
        // 사용자가 입력한 사용자 이름과 비밀번호 가져오기
        String userUsername, userPassword;
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        System.out.print("사용자 이름을 입력하세요: ");
        userUsername = scanner.nextLine();
        System.out.print("비밀번호를 입력하세요: ");
        userPassword = scanner.nextLine();

        Connection conn = null;
        Statement stmt = null;
        try {
            // 데이터베이스 연결
            conn = DriverManager.getConnection(DB_URL);
            stmt = conn.createStatement();

            // 사용자 정보 확인
            String sql = "SELECT password FROM users WHERE username='" + userUsername + "'";
            ResultSet rs = stmt.executeQuery(sql);
            if (!rs.next()) {
                System.out.println("사용자가 존재하지 않습니다.");
            } else {
                String storedPassword = rs.getString("password");
                if (storedPassword.equals(userPassword)) {
                    System.out.println("로그인 성공");
                } else {
                    System.out.println("비밀번호가 일치하지 않습니다.");
                }
            }
            rs.close();
            stmt.close();
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (stmt != null) stmt.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
            try {
                if (conn != null) conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}
