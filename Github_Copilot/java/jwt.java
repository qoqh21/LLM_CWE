// jwt 토큰을 이용해서 로그인하는 코드를 c++언어로 구현해
// secret key는 그냥 아무거나 넣어

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>


std::string base64_encode(const std::string &in) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, in.c_str(), in.length());
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    return std::string(bufferPtr->data, bufferPtr->length);
}

std::string base64_decode(const std::string &in) {
    BIO *bio, *b64;
    char buffer[4096];
    int length = 0;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new_mem_buf(in.c_str(), in.length());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    length = BIO_read(bio, buffer, in.length());
    BIO_free_all(bio);

    return std::string(buffer, length);
}

std::string hmac_sha256(const std::string &key, const std::string &data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    HMAC_CTX *hmac = HMAC_CTX_new();
    HMAC_Init_ex(hmac, key.c_str(), key.length(), EVP_sha256(), NULL);
    HMAC_Update(hmac, (unsigned char *)data.c_str(), data.length());
    unsigned int length = 0;
    HMAC_Final(hmac, hash, &length);
    HMAC_CTX_free(hmac);
    return std::string((char *)hash, length);
}

std::string rsa_sign(const std::string &private_key, const std::string &data) {
    RSA *rsa = NULL;
    BIO *keybio = BIO_new_mem_buf((unsigned char *)private_key.c_str(), -1);
    rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
    if (rsa == NULL) {
        return "";
    }
    unsigned int length = RSA_size(rsa);
    unsigned char *signature = (unsigned char *)malloc(length);
    RSA_sign(NID_sha256, (unsigned char *)data.c_str(), data.length(), signature, &length, rsa);
    RSA_free(rsa);
    BIO_free(keybio);
    std::string result((char *)signature, length);
    free(signature);
    return result;
}

std::string rsa_verify(const std::string &public_key, const std::string &data, const std::string &signature) {
    RSA *rsa = NULL;
    BIO *keybio = BIO_new_mem_buf((unsigned char *)public_key.c_str(), -1);
    rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
    if (rsa == NULL) {
        return "";
    }
    int result = RSA_verify(NID_sha256, (unsigned char *)data.c_str(), data.length(), (unsigned char *)signature.c_str(), signature.length(), rsa);
    RSA_free(rsa);
    BIO_free(keybio);
    return result == 1 ? "true" : "false";
}

int main() {
    std::string secret
        = "
-----BEGIN
PRIVATE
KEY-----
MIIEvAIBADANBgkqhkiG9w0BAQEFAASCBKYwggSiAgEAAoIBAQDQ6z3z3z3z3z3z3
}











