#pragma once

#include <chrono>
#include <mutex>
#include <random>
#include <string>
#include <unordered_map>

// 验证管理
class VCodeManager {
  private:
  // 验证码记录
  struct Entry {
    std::string code;
    std::chrono::steady_clock::time_point expire_timestamp;
  };

  struct VerifyResult {
    bool success;
    std::string error;
  };

  public:
  // 单例模式
  static VCodeManager& getInstance()
  {
    static VCodeManager instance;
    return instance;
  }

  void init(int ttl_seconds)
  {
    m_ttl = ttl_seconds;
  }

  std::string generateCode(const std::string& phone)
  {
    std::string code = randomDigits(m_code_len);
    auto now = std::chrono::steady_clock::now();

    std::lock_guard<std::mutex> lock(m_mtx);
    m_codes[ phone ] = {code, now};
    return code;
  }

  VerifyResult verifyCode(const std::string& phone, const std::string& code)
  {
    std::lock_guard<std::mutex> lock(m_mtx);
    auto it = m_codes.find(phone);
    if (it == m_codes.end())
      return {false, "Can't find code"};

    bool valid = false;
    auto now = std::chrono::steady_clock::now();
    std::string message = "Code expired.";
    if (now - it->second.expire_timestamp <= std::chrono::seconds(m_ttl)) {
      valid = it->second.code == code;
      message = valid ? "" : "Code is not matched.";
    }

    m_codes.erase(phone);

    if (!valid) {
      return {false, message};
    }
    return {true};
  }

  private:
  VCodeManager() = default;


  std::unordered_map<std::string, Entry> m_codes;
  std::mutex m_mtx;
  int m_ttl{300};
  int m_code_len{6};

  // 生成指定位数字符串
  std::string randomDigits(size_t length)
  {
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<int> dist(0, 9);

    std::string result(length, '0');
    std::generate_n(result.begin(), length,
                    [ & ]() { return '0' + dist(rng); });
    return result;
  }
};
