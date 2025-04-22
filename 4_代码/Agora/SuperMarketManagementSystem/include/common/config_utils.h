#include <nlohmann/json.hpp>

namespace utils {

class ConfigManager {
  using json = nlohmann::json;

public:
  ConfigManager() = default;

  ConfigManager(const std::string &filename);

  void readFromFile(const std::string &filename) const;

  std::uint16_t getPort() const;

  std::uint64_t getThreadNum() const;

  std::string getDatabasePath() const;

private:
  mutable json config;
};
} // namespace utils
