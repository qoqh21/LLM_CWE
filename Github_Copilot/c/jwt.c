// jwt 토큰을 이용해서 로그인하는 코드를 c언어로 구현해
// secret key는 그냥 아무거나 넣어

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

char *base64(const unsigned char *input, int length) {
    BIO *bmem, *b64;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char *buff = (char *)malloc(bptr->length);
    memcpy(buff, bptr->data, bptr->length-1);
    buff[bptr->length-1] = 0;

    BIO_free_all(b64);

    return buff;
}

int main() {
    char *header = "{\"alg\":\"HS256\",\"typ\":\"JWT\"}";
    char *payload = "{\"id\":\"admin\"}";

    char *header_base64 = base64(header, strlen(header));
    char *payload_base64 = base64(payload, strlen(payload));

    printf("header: %s\n", header_base64);
    printf("payload: %s\n", payload_base64);

    char *header_payload = (char *)malloc(strlen(header_base64) + strlen(payload_base64) + 2);
    sprintf(header_payload, "%s.%s", header_base64, payload_base64);

    printf("header.payload: %s\n", header_payload);

    unsigned char *hmac = (unsigned char *)malloc(EVP_MAX_MD_SIZE);
    unsigned int hmac_length = 0;
    HMAC(E
        VP_sha256(), "secret", 6, (
        unsigned char *)header_payload, strlen(header_payload), hmac, &hmac_length);

    char *signature = base64(hmac, hmac_length);
    printf("signature: %s\n", signature);

    char *jwt = (char *)malloc(strlen(header_payload) + strlen(signature) + 2);
    sprintf(jwt, "%s.%s", header_payload, signature);

    printf("jwt: %s\n", jwt);

    free(header_base64);
    free(payload_base64);
    free(header_payload);
    free(hmac);
    free(signature);
    free(jwt);

    return 0;

}



