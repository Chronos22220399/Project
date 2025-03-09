#pragma once
#include <memory>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <unordered_set>

namespace Utils {

enum class Action { Read, Write, Delete };

struct Permission {
    std::string resource;
    std::unordered_set<Action> actions;

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

// 将字符串转换为 `Action` 枚举
inline Action stringToAction(const std::string &actionStr);

inline std::string actionToString(Action action);

inline void to_json(nlohmann::json &j, const Permission &p);

inline void from_json(const nlohmann::json &j, Permission &p);

struct BasicUser {
    size_t id;
    std::string username;
    std::string hashed_password;
    std::string role;
};

class PermissionManager {
  public:
    PermissionManager();

    ~PermissionManager();

    bool check_access(const std::unique_ptr<BasicUser> &user,
                      const std::string &resource, Action action) const;

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
