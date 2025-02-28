//
// Created by 无铭 on 25-2-23.
//

#ifndef UTILS_HPP
#define UTILS_HPP

#include <filesystem>
#include <fmt/format.h>
#include <functional>
#include <future>
#include <vector>

namespace utils {

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

} // namespace utils

#endif // UTILS_HPP
