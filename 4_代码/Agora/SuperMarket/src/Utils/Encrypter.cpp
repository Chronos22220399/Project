#include "../include/Utils/Encrypter.h"
#include "../include/Utils/Log.hpp"
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <sodium.h>

namespace Utils {
// 初始化
void Encrypter::init() {
    if (sodium_init() < 0) {
        LOG("Encrypter 初始化失败");
        exit(-1);
    }
}

// 哈希账号
std::optional<std::string> Encrypter::crypto_hash(const std::string &input) {
    unsigned char output[crypto_generichash_BYTES];
    crypto_generichash(output, sizeof(output),
                       reinterpret_cast<const unsigned char *>(input.data()),
                       input.length(), nullptr, 0);
    return {std::string{reinterpret_cast<char *>(output), sizeof(output)}};
}

std::optional<std::string>
Encrypter::hash_password(const std::string &password) {
    unsigned char hashed_password[crypto_pwhash_STRBYTES];
    // crypto_pwhash_str 是对 crypto_pwhash 的简易封装，不用手动加盐
    if (crypto_pwhash_str((char *)hashed_password, password.c_str(),
                          password.length(), crypto_pwhash_OPSLIMIT_INTERACTIVE,
                          crypto_pwhash_MEMLIMIT_INTERACTIVE) < 0) {
        return std::nullopt;
    }
    return std::string{(char *)hashed_password};
}

bool Encrypter::verify_password(const std::string &hashed_password,
                                const std::string &password) {
    return crypto_pwhash_str_verify(hashed_password.c_str(), password.c_str(),
                                    password.length()) == 0;
}

std::string Encrypter::hmac_sha256(const std::string &key,
                                   const std::string &data) {
    unsigned char *result;
    unsigned int len = SHA256_DIGEST_LENGTH;
    result = HMAC(EVP_sha256(), key.c_str(), key.length(),
                  (unsigned char *)data.c_str(), data.length(), NULL, NULL);
    return std::string(reinterpret_cast<char *>(result), len);
}

} // namespace Utils
