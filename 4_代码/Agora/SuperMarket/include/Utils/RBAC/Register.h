#pragma
#include <Utils/Jwt.h>
#include <Utils/RBAC/PasswordManager.hpp>
#include <Utils/RBAC/PermissionManager.h>
#include <memory>
#include <regex>

namespace Utils {

class RegDBStrategy {
  public:
    virtual ~RegDBStrategy() = default;
    virtual bool save(std::shared_ptr<BasicUser> user) = 0;
    virtual bool query_name(const std::string &username) = 0;
};

class TokenGetter {
  public:
    static Jwt::SerializeResult get() {
        Jwt::Header header;
        Jwt::Payload payload{};
        return Jwt::instance().serialize(header, payload);
    }
};

// TODO: 添加db策略，实现注册模块，然后进行测试
class BasicRegister {
  public:
    struct RegistResult {
        std::optional<std::string> token;
        std::optional<std::string> err_message;
    };

    virtual ~BasicRegister() = default;
    virtual RegistResult regist(std::shared_ptr<BasicUser> user) const = 0;
    virtual std::optional<std::string>
    check_username(const std::string &username) const = 0;
    virtual std::optional<std::string>
    check_password(const std::string &password) const = 0;
};

class GenericRegister : public BasicRegister {
  public:
    GenericRegister(std::shared_ptr<RegDBStrategy> database)
        : database_(database) {}

    ~GenericRegister() = default;

    RegistResult regist(std::shared_ptr<BasicUser> user) const override {
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
    check_username(const std::string &username) const override {
        if (username.length() < 3 || username.length() > 30) {
            return "Username must be between 3 and 20 characters.";
        }
        if (!std::regex_match(username, std::regex("^[a-zA-Z0-9_.]+$"))) {
            return "Username contains invalid characters.";
        }
        return std::nullopt;
    }

    virtual std::optional<std::string>
    check_password(const std::string &password) const override {
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

} // namespace Utils
