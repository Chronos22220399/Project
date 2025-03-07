#pragma once
#include <optional>
#include <string>

namespace Utils {

class Encrypter {
  public:
    // 初始化
    static void init();

    // 不可获取原信息的哈希，通过用对 input 哈希后与存储的值对比方式查找
    static std::optional<std::string> crypto_hash(const std::string &input);

    // 哈希加密信息
    static std::optional<std::string>
    hash_password(const std::string &password);

    // 校验哈希加密后的信息
    static bool verify_password(const std::string &hashed_password,
                                const std::string &password);
};
} // namespace Utils
