//
// Created by 无铭 on 25-3-10.
//
#include "../include/Utils/RBAC/Register.h"

namespace Utils {

class GenericRegister::Impl {
public:
    Impl(std::shared_ptr<RegDBStrategy> database)
        : database_(database) {}

    ~Impl() = default;

    RegistResult regist(std::shared_ptr<BasicUser> user) const {
        if (auto err = check_username(user->username)) {
            return {std::nullopt, err};
        }
        if (auto err = check_password(user->password)) {
            return {std::nullopt, err};
        }
        if (!database_->save(user)) {
            return {std::nullopt, {"username is exists"}};
        }
        auto result = TokenGetter::get();
        return {result.jwt, std::nullopt};
    }

    virtual std::optional<std::string>
    check_username(const std::string &username) const {
        if (username.length() < 3 || username.length() > 30) {
            return "Username must be between 3 and 20 characters.";
        }
        if (!std::regex_match(username, std::regex("^[a-zA-Z0-9_.]+$"))) {
            return "Username contains invalid characters.";
        }
        return std::nullopt;
    }

    virtual std::optional<std::string>
    check_password(const std::string &password) const {
        if (password.length() < 8) {
            return "Password must be at least 8 characters long.";
        }
        if (!std::regex_search(password, std::regex("[A-Z]")) ||
            !std::regex_search(password, std::regex("[a-z]")) ||
            !std::regex_search(password, std::regex("[0-9]")) ||
            !std::regex_search(password, std::regex("[!@#$%^&*]"))) {
            return "Password must contain uppercase, lowercase, number, and "
                   "special character.";
            }
        return std::nullopt;
    }

private:
    std::shared_ptr<RegDBStrategy> database_;
};

GenericRegister::GenericRegister(std::shared_ptr<RegDBStrategy> database)
    : impl(std::make_unique<Impl>(database)) {}

GenericRegister::~GenericRegister() = default;

GenericRegister::RegistResult GenericRegister::regist(std::shared_ptr<BasicUser> user) const {
    return impl->regist(user);
}

std::optional<std::string>
GenericRegister::check_username(const std::string &username) const {
    return impl->check_username(username);
}

 std::optional<std::string>
GenericRegister::check_password(const std::string &password) const  {
     return impl->check_password(password);
}

} // namespace Utils
