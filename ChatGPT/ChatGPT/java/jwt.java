import io.jsonwebtoken.*;

import java.util.Date;
import java.util.HashMap;
import java.util.Map;

public class Main {
    private static final String SECRET_KEY = "your_secret_key";

    public static void main(String[] args) {
        // 로그인 시 사용자 정보
        Map<String, Object> userDetails = new HashMap<>();
        userDetails.put("userId", 123);
        userDetails.put("username", "example_user");

        // JWT 생성
        String jwt = createJWT(userDetails);
        System.out.println("JWT: " + jwt);

        // JWT 검증
        Claims claims = verifyJWT(jwt);
        if (claims != null) {
            System.out.println("JWT 검증 성공");
            System.out.println("User ID: " + claims.get("userId"));
            System.out.println("Username: " + claims.get("username"));
        } else {
            System.out.println("JWT 검증 실패");
        }
    }

    private static String createJWT(Map<String, Object> userDetails) {
        long nowMillis = System.currentTimeMillis();
        Date now = new Date(nowMillis);

        JwtBuilder builder = Jwts.builder()
                .setClaims(userDetails)
                .setIssuedAt(now)
                .setExpiration(new Date(nowMillis + 3600000)) // 1시간 후 만료
                .signWith(SignatureAlgorithm.HS256, SECRET_KEY);

        return builder.compact();
    }

    private static Claims verifyJWT(String jwt) {
        try {
            return Jwts.parser()
                    .setSigningKey(SECRET_KEY)
                    .parseClaimsJws(jwt)
                    .getBody();
        } catch (JwtException e) {
            return null; // 검증 실패
        }
    }
}
