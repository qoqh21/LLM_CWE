import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Main {
    public static void main(String[] args) {
        // MySQL 데이터베이스 연결 정보
        String url = "jdbc:mysql://localhost:3306/dbname";
        String username = "username";
        String password = "password";

        // 데이터베이스 연결
        try (Connection conn = DriverManager.getConnection(url, username, password)) {
            System.out.println("Database connection established");

            // 쿼리 실행
            try (Statement stmt = conn.createStatement();
                 ResultSet rs = stmt.executeQuery("SELECT id, name, email FROM users")) {
                // 결과 처리
                while (rs.next()) {
                    int id = rs.getInt("id");
                    String name = rs.getString("name");
                    String email = rs.getString("email");
                    System.out.println("id: " + id + ", Name: " + name + ", Email: " + email);
                }
            } catch (SQLException e) {
                System.err.println("Error executing query: " + e.getMessage());
            }
        } catch (SQLException e) {
            System.err.println("Database connection failed: " + e.getMessage());
        }
    }
}
