//
// Created by 无铭 on 25-2-23.
//

#ifndef UTILS_HPP
#define UTILS_HPP

#include <Utils/Log.hpp>
#include <algorithm>
#include <filesystem>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/encoder.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>

namespace details {
template <size_t N, size_t... Is>
struct make_even_or_odd_sequence
    : make_even_or_odd_sequence<N - 2, N - 2, Is...> {};

template <size_t... Is> struct make_even_or_odd_sequence<0, Is...> {
    using type = std::index_sequence<Is...>;
};

template <size_t... Is> struct make_even_or_odd_sequence<1, Is...> {
    using type = std::index_sequence<Is...>;
};

template <size_t N, size_t... Is>
auto make_index_sequence_from(std::index_sequence<Is...>) {
    return std::index_sequence<N + Is...>{};
}

} // namespace details
#include <fmt/format.h>
#include <functional>
#include <future>
#include <vector>

namespace Utils {

inline std::filesystem::path get_project_root_path(std::filesystem::path path,
                                                   std::string root_dir_name) {
    std::string current_path = std::string(path.c_str());
    bool in_root_dir =
        (current_path.rfind(root_dir_name) + root_dir_name.length() ==
         current_path.length());
    if (!in_root_dir) {
        return get_project_root_path(path.parent_path(), root_dir_name);
    } else {
        return path;
    }
}

template <size_t LoopNum> struct ForLoop {
    template <typename Function, typename... Args>
    static auto run(Function &&func, Args &&...args) {
        std::vector<std::future<void>> futures;
        futures.reserve(LoopNum);
        for (auto i = 0; i < LoopNum; ++i) {
            futures.emplace_back(
                std::async(std::launch::async, [&func, &args...] {
                    std::invoke(std::forward<Function>(func),
                                std::forward<Args>(args)...);
                }));
        }
        for (auto &future : futures) {
            future.wait();
        }
    }
};

template <size_t N>
using make_even_index_sequence =
    typename details::make_even_or_odd_sequence<N + 2>::type;

template <size_t N, size_t L> auto make_index_sequence_from() {
    return details::make_index_sequence_from<N>(std::make_index_sequence<L>{});
}

inline std::string base64_encode(const std::string &in) {
    try {
        BIO *bio, *b64;
        BUF_MEM *bufferPtr = nullptr;

        // 创建 base64 过滤器并禁用换行符号
        b64 = BIO_new(BIO_f_base64());
        if (!b64) {
            throw std::runtime_error("创建 BIO_f_base64 失败");
        }
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

        // 创建内存 BIO 并链接到 base64 过滤器上
        bio = BIO_new(BIO_s_mem());
        if (!bio) {
            BIO_free_all(b64);
            throw std::runtime_error("创建 BIO_s_mem 失败");
        }
        bio = BIO_push(b64, bio);

        // 写入数据并刷新
        int len = BIO_write(bio, in.data(), static_cast<int>(in.length()));
        if (len <= 0 || static_cast<size_t>(len) != in.length()) {
            BIO_free_all(bio);
            throw std::runtime_error("写入数据到 BIO 失败");
        }
        BIO_flush(bio);

        // 获取内存缓冲区信息
        BIO_get_mem_ptr(bio, &bufferPtr);
        if (!bufferPtr || !bufferPtr->data || bufferPtr->length == 0) {
            BIO_free_all(bio);
            throw std::runtime_error("读取内存缓冲区信息失败");
        }
        std::string result(bufferPtr->data, bufferPtr->length);

        // 释放整个 BIO 链
        BIO_free_all(bio);
        return result;
    } catch (const std::exception &e) {
        LOG(e.what());
        return "";
    }
}

inline std::string base64url_encode(const std::string &in) {
    try {
        std::string base64 = base64_encode(in);

        std::string base64url = base64;
        std::replace(base64url.begin(), base64url.end(), '+', '-');
        std::replace(base64url.begin(), base64url.end(), '/', '_');

        base64url.erase(std::remove(base64url.begin(), base64url.end(), '='),
                        base64url.end());
        return base64url;
    } catch (const std::exception &e) {
        LOG(e.what());
        return "";
    }
}

inline std::string base64url_decode(const std::string &in) {
    try {
        std::string base64 = in;

        std::replace(base64.begin(), base64.end(), '-', '+');
        std::replace(base64.begin(), base64.end(), '_', '/');

        auto padding = (4 - (base64.length() % 4)) % 4;
        base64.append(padding, '=');

        BIO *bio, *b64;
        BUF_MEM *bufferPtr = nullptr;

        bio = BIO_new(BIO_s_mem());
        if (!bio) {
            BIO_free_all(b64);
            throw std::runtime_error("创建 BIO_s_mem 失败");
        }
        bio = BIO_push(b64, bio);

        // 写入数据并刷新
        int len =
            BIO_write(bio, base64.data(), static_cast<int>(base64.length()));
        if (len <= 0 || static_cast<size_t>(len) != base64.length()) {
            BIO_free_all(bio);
            throw std::runtime_error("写入数据到 BIO 失败");
        }
        BIO_flush(bio);

        // 获取内存缓冲区信息
        BIO_get_mem_ptr(bio, &bufferPtr);
        if (!bufferPtr || !bufferPtr->data || bufferPtr->length == 0) {
            BIO_free_all(bio);
            throw std::runtime_error("读取内存缓冲区信息失败");
        }
        std::string result(bufferPtr->data, bufferPtr->length);

        // 释放整个 BIO 链
        BIO_free_all(bio);
        return result;
    } catch (const std::exception &e) {
        LOG(e.what());
        return "";
    }
}
} // namespace Utils

#endif // UTILS_HPP
