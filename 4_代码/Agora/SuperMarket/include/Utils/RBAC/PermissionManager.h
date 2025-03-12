#pragma once
#include <fmt/format.h>
#include <memory>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <unordered_set>
#include <Utils/RBAC/BasicUser.hpp>

namespace Utils {

// TODO: 考虑增加热重载功能, 考虑将 load_data_from_json 和 save_data_to_json
// 放入单独的类中作为单独模块存在
// 当前 Resource 内容仅做测试用，后续需要更改
enum class Resource { User_data, Goods };

enum class Action { Read, Write, Delete };

inline std::string resourceToString(const Resource &resource) {
    if (resource == Resource::User_data)
        return "user_data";
    if (resource == Resource::Goods)
        return "goods";
    throw std::invalid_argument("Unknown resource");
}

// 将字符串转换为 `Action` 枚举
inline Action stringToAction(const std::string &action_str) {
    if (action_str == "Read")
        return Action::Read;
    if (action_str == "Write")
        return Action::Write;
    if (action_str == "Delete")
        return Action::Delete;
    throw std::invalid_argument("Unknown action: " + action_str);
}

inline std::string actionToString(Action action) {
    if (action == Action::Read)
        return "Read";
    if (action == Action::Write)
        return "Write";
    if (action == Action::Delete)
        return "Delete";
    throw std::invalid_argument("Unknown action");
}

struct Permission {
    std::string resource;
    std::unordered_set<Action> actions;

    auto display() const {
        fmt::println("resource: {}", resource);
        fmt::print("actions: ");
        for (auto action : actions) {
            fmt::println(actionToString(action));
        }
    }

    bool operator==(const Permission &other) const {
        return resource == other.resource && actions == other.actions;
    }
};
} // namespace Utils

namespace std {
template <> struct hash<Utils::Permission> {
    size_t operator()(const Utils::Permission &p) const {
        size_t h1 = hash<std::string>{}(p.resource);
        size_t h2 = 0;
        for (const auto &action : p.actions) {
            h2 ^=
                static_cast<size_t>(action) + 0x9e3779b9 + (h2 << 6) + (h2 + 2);
        }
        return h1 ^ (h2 << 1);
    }
};
} // namespace std

namespace Utils {

inline void to_json(nlohmann::json &j, const Permission &p);

inline void from_json(const nlohmann::json &j, Permission &p);


class PermissionManager {
  public:
    PermissionManager();

    ~PermissionManager();

    bool check_access(const std::unique_ptr<BasicUser> &user,
                      const Resource &resource, Action action) const;

    std::unordered_set<Permission>
    get_permission_of(const std::string &role) const;

    bool set_actions_of(const std::string &role, const std::string &resource,
                        const std::unordered_set<Action> &newActions);

    void load_data_from_json();

    void save_data_to_json();

    void display() const;

    class PMImpl;

  private:
    std::unique_ptr<PMImpl> impl;
};
} // namespace Utils
