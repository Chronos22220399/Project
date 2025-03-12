#pragma
#include <../Jwt/Jwt.h>
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
    static Jwt::SerializeResult get(Jwt::Header &header, std::shared_ptr<BasicUser> user) {
        Jwt::Header header;
        Jwt::Payload payload{};
        return Jwt::instance().serialize(header, payload);
    }
};

// TODO: 添加db策略，实现注册模
// 定义登录流程的接口
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

// 定义登录流程的通用实现
class GenericRegister : public BasicRegister {
  public:
    explicit GenericRegister(std::shared_ptr<RegDBStrategy> database);

    ~GenericRegister();

    RegistResult regist(std::shared_ptr<BasicUser> user) const override;

    virtual std::optional<std::string>
    check_username(const std::string &username) const override;

    virtual std::optional<std::string>
    check_password(const std::string &password) const override;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

} // namespace Utils
