//
// Created by 无铭 on 25-2-23.
//

#ifndef UTILS_HPP
#define UTILS_HPP

#include <filesystem>

namespace utils {

inline std::filesystem::path get_project_base_path(std::filesystem::path path,
                                                   std::string root_dir_name) {
    std::string current_path = std::string(path.c_str());
    bool in_root_dir =
        (current_path.find(root_dir_name) + root_dir_name.length() ==
         current_path.length());
    if (!in_root_dir) {
        return get_project_base_path(path.parent_path(), root_dir_name);
    } else {
        return path;
    }
}

} // namespace utils

#endif // UTILS_HPP
