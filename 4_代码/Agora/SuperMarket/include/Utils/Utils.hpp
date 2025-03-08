//
// Created by 无铭 on 25-2-23.
//

#ifndef UTILS_HPP
#define UTILS_HPP

#include <Utils/Log.hpp>
#include <filesystem>
#include <functional>
#include <future>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/encoder.h>
#include <openssl/evp.h>
#include <vector>

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

template <typename Operation, typename... Args>
void test(const std::string &caseName, Operation &&operation, Args &&...args) {
    fmt::println("\n -------- Test Case: {} Start -------\n", caseName);
    std::invoke(std::forward<Operation>(operation),
                std::forward<Args>(args)...);
    fmt::println("\n -------- Test Case: {} End -------\n", caseName);
}
} // namespace Utils

#endif // UTILS_HPP
