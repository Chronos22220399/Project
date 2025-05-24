#include <common/config_utils.h>
#include <common/uni_define.h>
#include <cstdlib>
#include <fmt/format.h>
#include <fstream>
#include <string>


void ConfigManager::init(const std::string& filename) const
{
  readFromFile(filename);
}


void ConfigManager::readFromFile(const std::string& filename) const
{
  std::ifstream ifs(filename);

  if (!ifs.is_open()) {
    LOG("Open file {} failed", filename);
    std::exit(-1);
  }

  config = json::parse(ifs);
}


std::uint16_t ConfigManager::getPort() const
{
  try {
    auto& node = config.at("server");

    if (!node.contains("port")) {
      LOG("Missing server port.");
      exit(-1);
    }

    if (!node[ "port" ].is_number()) {
      LOG("Invalid server port.");
      exit(-1);
    }

    return node.at("port").get<std::uint16_t>();
  }
  catch (const std::exception& e) {
    LOG("Get server port failed, reason: {}", e.what());
    std::exit(-1);
  }
}


std::uint64_t ConfigManager::getThreadNum() const
{
  try {
    auto& node = config.at("server");

    if (!node.contains("thread_num")) {
      LOG("Missing thread num.");
      exit(-1);
    }

    if (!node[ "thread_num" ].is_number()) {
      LOG("Invalid thread num.");
      exit(-1);
    }

    return node.at("thread_num").get<std::uint64_t>();
  }
  catch (const std::exception& e) {
    LOG("Get thread num failed, reason: {}", e.what());
    std::exit(-1);
  }
}


std::string ConfigManager::getDatabasePath() const
{
  try {
    auto& node = config.at("database");

    if (!node.contains("file")) {
      LOG("Missing database file path.");
      exit(-1);
    }

    if (!node[ "file" ].is_string()) {
      LOG("Invalid database file path.");
      exit(-1);
    }

    return node.at("file").get<std::string>();
  }
  catch (const std::exception& e) {
    LOG("Get database path failed, reason: {}", e.what());
    std::exit(-1);
  }
}


int ConfigManager::getVCodeTTL() const
{
  try {
    auto& node = config.at("register");

    if (!node.contains("vcode_ttl_seconds")) {
      LOG("Missing vcode ttl seconds.");
      exit(-1);
    }

    if (!node[ "vcode_ttl_seconds" ].is_number()) {
      LOG("Invalid vcode ttl seconds.");
      exit(-1);
    }

    return node.at("vcode_ttl_seconds").get<int>();
  }
  catch (const std::exception& e) {
    LOG("Get varification code ttl failed, reason: {}", e.what());
    std::exit(-1);
  }
}


// 从配置中的环境变量名称中获取密钥
std::string ConfigManager::getSecret() const
{
  try {
    auto& node = config.at("auth");

    if (!node.contains("secret_key")) {
      LOG("Missing secret key env name.");
      exit(-1);
    }

    if (!node[ "secret_key" ].is_string()) {
      LOG("Invalid secret key env name.");
      exit(-1);
    }

    std::string secret_env = node.at("secret_key").get<std::string>();
    const char* secret_key = std::getenv(secret_env.c_str());

    if (!secret_key) {
      LOG("Environment variable {} not found", secret_env);
      exit(-1);
    }

    return secret_key;
  }
  catch (const std::exception& e) {
    LOG("Get secret key failed, reason: {}", e.what());
    std::exit(-1);
  }
}


int ConfigManager::getTokenExpireMinutes() const
{
  try {
    auto& node = config.at("auth");

    if (!node.contains("token_expire_minutes")) {
      LOG("Missing token expire minutes.");
      exit(-1);
    }

    if (!node[ "token_expire_minutes" ].is_number()) {
      LOG("Invalid token expire minutes.");
      exit(-1);
    }

    return node.at("token_expire_minutes").get<int>();
  }
  catch (const std::exception& e) {
    LOG("Get token expire minutes failed, reason: {}", e.what());
    std::exit(-1);
  }
}
