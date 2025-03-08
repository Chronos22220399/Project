#pragma once
#include <memory>
#include <string>

namespace Utils {

class RandomGenerator {
  public:
    RandomGenerator();
    ~RandomGenerator();

    std::string
    generate_string(size_t len,
                    const std::string &charset =
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopq"
                        "rstuvwxyz0123456789");

  private:
    struct RGImpl;
    std::unique_ptr<RGImpl> impl;
};

} // namespace Utils
