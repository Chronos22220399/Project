#pragma once
#include <common/common_utils.hpp>
#include <jwt-cpp/jwt.h>
#include <string>

class JwtManager {
  public:
  static JwtManager& getInstance()
  {
    static JwtManager instance;
    return instance;
  }

  void init(const std::string& secret_key, const int expire_seconds)
  {
    m_secret_key = secret_key;
    m_expire_seconds = expire_seconds;
  }

  // 生成 token
  std::string generateToken(const std::string& user_id) const
  {
    using namespace std::chrono;
    auto now = system_clock::now();

    auto token = jwt::create()
                   .set_issued_at(now)
                   .set_expires_at(now + seconds(m_expire_seconds))
                   .set_payload_claim("uid", jwt::claim(user_id))
                   .sign(jwt::algorithm::hs256{m_secret_key});
    return token;
  }

  // 验证 token
  std::optional<std::string> verifyToken(const std::string& token) const
  {
    try {
      auto decoded = jwt::decode(token);
      // 验证失败会抛出异常
      auto verifier =
        jwt::verify()
          .allow_algorithm(jwt::algorithm::hs256{m_secret_key})
          .with_claim("uid",
                      decoded.get_payload_claim("uid"));  // 确保 uid 存在

      verifier.verify(decoded);
      return decoded.get_payload_claim("uid").as_string();
    }
    catch (const std::exception& e) {
      LOG("Uid doesn't exists.");
      return std::nullopt;
    }
  }

  private:
  JwtManager() = default;

  std::string m_secret_key{};
  int m_expire_seconds{60};
};
