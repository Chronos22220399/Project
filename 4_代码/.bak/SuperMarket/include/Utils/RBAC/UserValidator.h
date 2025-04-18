#pragma once
#include "../Jwt/Jwt.h"
#include "PermissionManager.h"
#include <functional>
#include <memory>
#include <regex>

namespace Utils {

class UserValidator {
    struct ValidResult {
        bool isValid;
        std::optional<std::string> reason;
    };

    static ValidResult isValidUsername(const std::string &username) {
        if (username.length() < 3 || username.length() > 30) {
            return {false, "Username must be between 3 and 20 characters."};
        }
        if (!std::regex_match(username, std::regex("^[a-zA-Z0-9_.]+$"))) {
            return {false, "Username contains invalid characters."};
        }
        return {true, std::nullopt};
    }

    static ValidResult isValidPassword(const std::string &password) {
        if (password.length() < 8) {
            return {false, "Password must be at least 8 characters long."};
        }
        if (!std::regex_search(password, std::regex("[A-Z]")) ||
            !std::regex_search(password, std::regex("[a-z]")) ||
            !std::regex_search(password, std::regex("[0-9]")) ||
            !std::regex_search(password, std::regex("[!@#$%^&*]"))) {
            return {false,
                    "Password must contain uppercase, lowercase, number, and "
                    "special character."};
        }
        return {true, std::nullopt};
    }
};

// 定义登录流程的通用实现
// class GenericRegister {
//   public:
//     struct RegistResult {
//         std::optional<std::string> token;
//         std::optional<std::string> err_message;
//     };
//
//
//     ~GenericRegister();
//
//     virtual RegistResult regist(std::shared_ptr<BasicUser> user) const;
//
//     virtual std::optional<std::string>
//     check_username(const std::string &username) const;
//
//     virtual std::optional<std::string>
//     check_password(const std::string &password) const;
//
//   private:
//     struct Impl;
//     std::unique_ptr<Impl> impl;
// };

} // namespace Utils
