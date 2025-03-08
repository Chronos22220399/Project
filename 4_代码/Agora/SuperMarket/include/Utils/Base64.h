#include <memory>
#include <string>

namespace Utils {

inline std::string hmac_sha256(const std::string &key, const std::string &data);

class Base64 {
  public:
    enum class BioFlags { no_new_line };

    Base64();
    Base64(Base64 &&other) noexcept;
    Base64 &operator=(Base64 &&other) noexcept;
    ~Base64();
    std::string encode(const std::string &in,
                       BioFlags flag = BioFlags::no_new_line);
    std::string decode(const std::string &in,
                       BioFlags flag = BioFlags::no_new_line);
    std::string url_encode(const std::string &in,
                           BioFlags flag = BioFlags::no_new_line);
    std::string url_decode(const std::string &in,
                           BioFlags flag = BioFlags::no_new_line);

  private:
    struct Base64Impl;

    std::unique_ptr<Base64Impl> impl;
};

} // namespace Utils
