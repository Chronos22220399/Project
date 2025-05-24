#pragma once
#include <nlohmann/json.hpp>


class ConfigManager {
  using json = nlohmann::json;

  public:
  static ConfigManager& getInstance()
  {
    static ConfigManager instance;
    return instance;
  }

  void init(const std::string& filename) const;

  void readFromFile(const std::string& filename) const;

  std::uint16_t getPort() const;

  std::uint64_t getThreadNum() const;

  std::string getDatabasePath() const;

  // vcode
  int getVCodeTTL() const;

  // jwt
  std::string getSecret() const;

  int getTokenExpireMinutes() const;

  private:
  ConfigManager() = default;

  private:
  mutable json config;
};
