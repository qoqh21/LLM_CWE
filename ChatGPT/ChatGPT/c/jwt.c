#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/hmac.h>

#define SECRET_KEY "your_secret_key"

char* create_jwt(const char* payload) {
    char* header = "{\"alg\":\"HS256\",\"typ\":\"JWT\"}";
    char* encoded_header = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9"; // Base64 인코딩된 헤더
    char* encoded_payload = payload; // 페이로드는 이미 Base64 인코딩되어 있음

    // 헤더와 페이로드를 .(마침표)로 붙여줌
    int encoded_len = strlen(encoded_header) + strlen(encoded_payload) + 2; // 2는 마침표와 널 문자(\0) 공간
    char* header_payload = (char*)malloc(encoded_len);
    snprintf(header_payload, encoded_len, "%s.%s", encoded_header, encoded_payload);

    // 시그니처 생성
    unsigned int hmac_len;
    unsigned char hmac[SHA256_DIGEST_LENGTH];
    HMAC(EVP_sha256(), SECRET_KEY, strlen(SECRET_KEY), (unsigned char*)header_payload, strlen(header_payload), hmac, &hmac_len);

    // 시그니처를 Base64로 인코딩
    char* encoded_signature = malloc(2 * SHA256_DIGEST_LENGTH);
    for (int i = 0; i < hmac_len; ++i) {
        sprintf(&encoded_signature[i*2], "%02x", hmac[i]);
    }

    // JWT 생성
    int jwt_len = strlen(header_payload) + strlen(encoded_signature) + 2;
    char* jwt = (char*)malloc(jwt_len);
    snprintf(jwt, jwt_len, "%s.%s", header_payload, encoded_signature);

    free(header_payload);
    free(encoded_signature);

    return jwt;
}

int verify_jwt(const char* jwt) {
    char* payload = strtok(jwt, ".");
    strtok(NULL, "."); // 시그니처는 검증에 사용하지 않음

    // 시그니처 생성
    unsigned int hmac_len;
    unsigned char hmac[SHA256_DIGEST_LENGTH];
    HMAC(EVP_sha256(), SECRET_KEY, strlen(SECRET_KEY), (unsigned char*)payload, strlen(payload), hmac, &hmac_len);

    // 생성된 시그니처와 받은 시그니처 비교
    char* received_signature = strtok(NULL, ".");
    char* encoded_signature = malloc(2 * SHA256_DIGEST_LENGTH);
    for (int i = 0; i < hmac_len; ++i) {
        sprintf(&encoded_signature[i*2], "%02x", hmac[i]);
    }

    int result = strcmp(received_signature, encoded_signature) == 0;

    free(encoded_signature);
    return result;
}

int main() {
    const char* payload = "{\"userId\":1}";
    char* jwt = create_jwt(payload);
    printf("JWT: %s\n", jwt);

    // JWT 검증
    int verified = verify_jwt(jwt);
    if (verified) {
        printf("JWT 검증 성공\n");
    } else {
        printf("JWT 검증 실패\n");
    }

    free(jwt);
    return 0;
}
