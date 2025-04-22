#include <common/config_utils.h>
#include <common/uni_define.h>
#include <fmt/format.h>
#include <fstream>
#include <string>

namespace utils {

ConfigManager::ConfigManager(const std::string &filename) {
  readFromFile(filename);
}

void ConfigManager::readFromFile(const std::string &filename) const {
  std::ifstream ifs(filename);

  if (!ifs.is_open()) {
    LOG("Open file {} failed", filename);
    std::exit(-1);
  }

  config = json::parse(ifs);
}

std::uint16_t ConfigManager::getPort() const {
  try {
    return config["server"]["port"];
  } catch (const std::exception &e) {
    LOG("Get port failed, reason: {}", e.what());
    std::exit(-1);
  }
}

std::uint64_t ConfigManager::getThreadNum() const {
  try {
    return config["server"]["thread_num"];
  } catch (const std::exception &e) {
    LOG("Get thread num failed, reason: {}", e.what());
    std::exit(-1);
  }
}

std::string ConfigManager::getDatabasePath() const {
  try {
    return config["database"]["file"];
  } catch (const std::exception &e) {
    LOG("Get database path failed, reason: {}", e.what());
    std::exit(-1);
  }
}

} // namespace utils
