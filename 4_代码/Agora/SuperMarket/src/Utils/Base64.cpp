#include <Utils/Base64.h>
#include <algorithm>
#include <map>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/encoder.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <stdexcept>
using namespace Utils;

std::string hmac_sha256(const std::string &key, const std::string &data) {
    unsigned char *result;
    unsigned int len = SHA256_DIGEST_LENGTH;
    result = HMAC(EVP_sha256(), key.c_str(), key.length(),
                  (unsigned char *)data.c_str(), data.length(), NULL, NULL);
    return std::string(reinterpret_cast<char *>(result), len);
}

class Base64::Base64Impl {
  public:
    Base64Impl() { OpenSSL_add_all_algorithms(); }
    ~Base64Impl() = default;

    int get_bio_flag(BioFlags flag) {
        auto it = bioFlagMap.find(flag);
        if (it == bioFlagMap.end()) {
            throw std::runtime_error("BIO 标志选择错误");
        }
        return it->second;
    }

    // 编码函数
    std::string encode(const std::string &in, BioFlags flag) {
        BIO *b64 = BIO_new(BIO_f_base64());
        if (!b64)
            throw std::runtime_error("创建 BIO_f_base64 失败");

        BIO_set_flags(b64, get_bio_flag(flag));

        BIO *bio_mem = BIO_new(BIO_s_mem());
        if (!bio_mem) {
            BIO_free_all(b64);
            throw std::runtime_error("创建 BIO_s_mem 失败");
        }

        // 正确链式结构：数据先经过 Base64 编码，再写入内存
        BIO *bio_chain = BIO_push(b64, bio_mem);

        // 写入数据
        int written =
            BIO_write(bio_chain, in.data(), static_cast<int>(in.length()));
        if (written <= 0 || static_cast<size_t>(written) != in.length()) {
            BIO_free_all(bio_chain);
            throw std::runtime_error("BIO_write 失败");
        }
        BIO_flush(bio_chain);

        // 获取编码结果
        BUF_MEM *bufferPtr = nullptr;
        BIO_get_mem_ptr(bio_mem, &bufferPtr);
        if (!bufferPtr || bufferPtr->length == 0) {
            BIO_free_all(bio_chain);
            throw std::runtime_error("获取内存缓冲区失败");
        }
        std::string result(bufferPtr->data, bufferPtr->length);

        BIO_free_all(bio_chain); // 释放整个链
        return result;
    }

    std::string decode(const std::string &in, BioFlags flag) {
        std::string base64 = in;
        // 创建反向 BIO 链：内存 -> Base64 解码器
        BIO *bio_mem =
            BIO_new_mem_buf(base64.data(), static_cast<int>(base64.length()));
        BIO *b64 = BIO_new(BIO_f_base64());
        BIO_set_flags(b64, get_bio_flag(flag));

        BIO *bio_chain = BIO_push(b64, bio_mem);

        // 读取解码数据
        char buffer[4096];
        std::string result;
        int len;
        while ((len = BIO_read(bio_chain, buffer, sizeof(buffer))) > 0) {
            result.append(buffer, len);
        }
        if (len < 0) {
            throw std::runtime_error("BIO_read 失败");
        }

        BIO_free_all(bio_chain);
        return result;
    }

    // Base64URL 编码
    std::string url_encode(const std::string &in, BioFlags flag) {
        std::string base64 = encode(in, flag);
        std::replace(base64.begin(), base64.end(), '+', '-');
        std::replace(base64.begin(), base64.end(), '/', '_');
        base64.erase(std::remove(base64.begin(), base64.end(), '='),
                     base64.end());
        return base64;
    }

    // Base64URL 解码
    std::string url_decode(const std::string &in, BioFlags flag) {
        std::string base64 = in;
        std::replace(base64.begin(), base64.end(), '-', '+');
        std::replace(base64.begin(), base64.end(), '_', '/');
        size_t padding = (4 - (base64.length() % 4)) % 4;
        base64.append(padding, '=');

        return decode(base64, flag);
    }

  private:
    static std::map<BioFlags, int> bioFlagMap;
};

std::map<Base64::BioFlags, int> Base64::Base64Impl::bioFlagMap = {
    {Base64::BioFlags::no_new_line, BIO_FLAGS_BASE64_NO_NL}};

Base64::Base64() : impl(std::make_unique<Base64Impl>()) {}

Base64::Base64(Base64 &&other) noexcept = default;

Base64 &Base64::operator=(Base64 &&other) noexcept = default;

Base64::~Base64() = default;

std::string Base64::encode(const std::string &in, BioFlags flag) {
    return impl->encode(in, flag);
}

std::string Base64::decode(const std::string &in, BioFlags flag) {
    return impl->decode(in, flag);
}

std::string Base64::url_encode(const std::string &in, BioFlags flag) {
    return impl->url_encode(in, flag);
}

std::string Base64::url_decode(const std::string &in, BioFlags flag) {
    return impl->url_decode(in, flag);
}
