#include <memory>
#include <string>

namespace Utils {

class Base64 {
  public:
    enum class BioFlags { no_new_line };

    Base64();
    Base64(Base64 &&other) noexcept;
    Base64 &operator=(Base64 &&other) noexcept;
    ~Base64();

    std::string url_encode(const std::string &in,
                           BioFlags flag = BioFlags::no_new_line) const;
    std::string url_decode(const std::string &in,
                           BioFlags flag = BioFlags::no_new_line) const;

  private:
    std::string encode(const std::string &in,
                       BioFlags flag = BioFlags::no_new_line) const;
    std::string decode(const std::string &in,
                       BioFlags flag = BioFlags::no_new_line) const;

  private:
    struct Base64Impl;

    std::unique_ptr<Base64Impl> impl;
};

} // namespace Utils
