#pragma once
#include <Utils/Encrypter.h>

namespace Utils {
class PasswordManager {
  public:
    static std::optional<std::string>
    hash_password(const std::string &password) {
        return Utils::Encrypter::hash_password(password);
    }

    static bool verify_password(const std::string &hashed_password,
                                const std::string &password) {
        return Utils::Encrypter::verify_password(hashed_password, password);
    }
};
} // namespace Utils
