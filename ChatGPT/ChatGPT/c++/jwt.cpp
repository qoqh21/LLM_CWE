#include <iostream>
#include <string>
#include <cstring>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include "base64.h" // Base64 라이브러리

#define SECRET_KEY "your_secret_key"

std::string create_jwt(const std::string& payload) {
    // 헤더와 페이로드 생성
    std::string header = "{\"alg\":\"HS256\",\"typ\":\"JWT\"}";
    std::string encoded_header = base64_encode(reinterpret_cast<const unsigned char*>(header.c_str()), header.length());
    std::string encoded_payload = base64_encode(reinterpret_cast<const unsigned char*>(payload.c_str()), payload.length());

    // 헤더와 페이로드를 .(마침표)로 붙여줌
    std::string header_payload = encoded_header + "." + encoded_payload;

    // 시그니처 생성
    unsigned int hmac_len;
    unsigned char hmac[EVP_MAX_MD_SIZE];
    HMAC(EVP_sha256(), SECRET_KEY, strlen(SECRET_KEY), reinterpret_cast<const unsigned char*>(header_payload.c_str()), header_payload.length(), hmac, &hmac_len);

    // 시그니처를 Base64로 인코딩
    std::string encoded_signature = base64_encode(hmac, hmac_len);

    // JWT 생성
    std::string jwt = header_payload + "." + encoded_signature;

    return jwt;
}

bool verify_jwt(const std::string& jwt) {
    // 페이로드와 시그니처 분리
    size_t pos = jwt.find_last_of(".");
    std::string payload = jwt.substr(0, pos);
    std::string received_signature = jwt.substr(pos + 1);

    // 시그니처 생성
    unsigned int hmac_len;
    unsigned char hmac[EVP_MAX_MD_SIZE];
    HMAC(EVP_sha256(), SECRET_KEY, strlen(SECRET_KEY), reinterpret_cast<const unsigned char*>(payload.c_str()), payload.length(), hmac, &hmac_len);

    // 생성된 시그니처와 받은 시그니처 비교
    std::string encoded_signature = base64_encode(hmac, hmac_len);
    return encoded_signature == received_signature;
}

int main() {
    const std::string payload = "{\"userId\":1}";
    std::string jwt = create_jwt(payload);
    std::cout << "JWT: " << jwt << std::endl;

    // JWT 검증
    bool verified = verify_jwt(jwt);
    if (verified) {
        std::cout << "JWT 검증 성공" << std::endl;
    } else {
        std::cout << "JWT 검증 실패" << std::endl;
    }

    return 0;
}
